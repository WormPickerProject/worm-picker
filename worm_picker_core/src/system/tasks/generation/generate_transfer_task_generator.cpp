// generate_transfer_task_generator.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include "worm_picker_core/utils/global_node.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_transfer_task_generator.hpp"

GenerateTransferTaskGenerator::GenerateTransferTaskGenerator(
    const std::unordered_map<std::string, HotelData>& hotel_map, TaskType task_type)
  : GenericTaskGenerator(hotel_map), 
    task_type_(task_type), 
    node_(worm_picker::getGlobalNode())
{
    robot_model_ = robot_model_loader::RobotModelLoader(node_).getModel();
    joint_model_group_ = robot_model_->getJointModelGroup(
        *param_utils::getParameter<std::string>(node_, "operation_modes.group"));
}

void GenerateTransferTaskGenerator::generateTasks() 
{
    for (const auto& name : getDataMapKeys()) {
        const auto parsed_name = parseName(name);
        if (parsed_name.second != transfer_config::rooms::TARGET_ROOM) {
            continue;
        }

        auto task_name = generateTaskName(parsed_name);
        auto stages = createStagesForTaskImpl(name, parsed_name);
        auto task_data = TaskData(std::move(stages));
        task_data_map_.emplace(std::move(task_name), std::move(task_data));
    }
}

std::pair<int, int> GenerateTransferTaskGenerator::parseName(const std::string& name) const
{
    int num = std::stoi(name);
    int hotel_number = num / transfer_config::rooms::HOTEL_ROOM_DIVISOR;
    int room_number = num % transfer_config::rooms::HOTEL_ROOM_DIVISOR; 
    return {hotel_number, room_number};
}

std::string 
GenerateTransferTaskGenerator::generateTaskName(const std::pair<int, int>& parsed_name) const
{
    const char* prefix = (task_type_ == TaskType::ToHotel) 
        ? transfer_config::prefix::WORKSTATION_TO_HOTEL
        : transfer_config::prefix::HOTEL_TO_WORKSTATION;
    
    return std::string(prefix) + std::to_string(parsed_name.first);
}

std::vector<std::shared_ptr<StageData>> 
GenerateTransferTaskGenerator::createStagesForTask(const HotelData& data, 
                                                   const std::pair<int, int>& parsed_name) const
{
    (void) parsed_name;
    Coordinate derived_position = calculateDerivedPoint(data.getCoordinate());
    StageSequence stages{ createMoveToPointStage(derived_position) };

    stages.emplace_back(createMoveToJointStage(
        task_type_ == TaskType::ToHotel 
            ? hotelAngle(data.getCoordinate().getOrientation()) * 180.0 / M_PI
            : transfer_config::joint_1::TO_WORKSTATION
    ));
    
    return stages;
}

Coordinate GenerateTransferTaskGenerator::calculateDerivedPoint(const Coordinate& hotel_coord) const
{
    auto calculateOffsetPosition = [this, &hotel_coord]() -> Coordinate {
        const double theta_rad = hotelAngle(hotel_coord.getOrientation());
        const double cos_theta = std::cos(theta_rad);
        const double sin_theta = std::sin(theta_rad);
        const auto offset = transfer_config::offset::POSITION_OFFSET;

        return Coordinate(
            hotel_coord.getPositionX() + (offset.x * cos_theta) + (offset.y * sin_theta),
            hotel_coord.getPositionY() + (offset.x * sin_theta) + (offset.y * cos_theta),
            hotel_coord.getPositionZ() + offset.z,
            hotel_coord.getOrientationX(),
            hotel_coord.getOrientationY(),
            hotel_coord.getOrientationZ(),
            hotel_coord.getOrientationW()
        );
    };

    const auto offset_position = calculateOffsetPosition();

    return (task_type_ == TaskType::ToHotel)
        ? handleToHotelPoint(offset_position)
        : offset_position;
}

Coordinate GenerateTransferTaskGenerator::handleToHotelPoint(const Coordinate& coord) const
{
    geometry_msgs::msg::Pose target_ee_pose;
    target_ee_pose.position.x = coord.getPositionX();
    target_ee_pose.position.y = coord.getPositionY();
    target_ee_pose.position.z = coord.getPositionZ();
    target_ee_pose.orientation.x = coord.getOrientationX();
    target_ee_pose.orientation.y = coord.getOrientationY();
    target_ee_pose.orientation.z = coord.getOrientationZ();
    target_ee_pose.orientation.w = coord.getOrientationW();
    
    auto ee_link = *param_utils::getParameter<std::string>(node_, "end_effectors.current_factor");
    auto flange_link = *param_utils::getParameter<std::string>(node_, "frames.flange_link");
    
    moveit::core::RobotState robot_state(robot_model_);
    robot_state.setToDefaultValues();
    
    const auto calculateFlangePose = [&]() {
        Eigen::Isometry3d flange_to_ee = 
            robot_state.getGlobalLinkTransform(flange_link).inverse() * 
            robot_state.getGlobalLinkTransform(ee_link);
        
        Eigen::Isometry3d target_transform;
        tf2::fromMsg(target_ee_pose, target_transform);
        
        geometry_msgs::msg::Pose flange_pose;
        tf2::convert(target_transform * flange_to_ee.inverse(), flange_pose);
        return flange_pose;
    };
    
    robot_state.setFromIK(joint_model_group_, calculateFlangePose());
    
    std::vector<double> joint_values;
    robot_state.copyJointGroupPositions(joint_model_group_, joint_values);
    joint_values[0] = transfer_config::joint_1::TO_WORKSTATION;
    robot_state.setJointGroupPositions(joint_model_group_, joint_values);
    
    const auto& new_pose = robot_state.getGlobalLinkTransform(ee_link);
    const auto& position = new_pose.translation();
    const Eigen::Quaterniond orientation(new_pose.rotation());
    
    return {
        position.x(), position.y(), position.z(),
        orientation.x(), orientation.y(), orientation.z(), orientation.w()
    };
}

std::shared_ptr<StageData> 
GenerateTransferTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}

std::shared_ptr<StageData> 
GenerateTransferTaskGenerator::createMoveToJointStage(double joint_angle) const
{
    return std::make_shared<MoveToJointData>(
        std::map<std::string, double>{{"joint_1", joint_angle}});
}

double GenerateTransferTaskGenerator::hotelAngle(
    const std::tuple<double, double, double, double>& orientation) const
{
    const auto& [qx, qy, qz, qw] = orientation;
    return std::atan2(2 * (qw * qz + qx * qy), 1 - 2 * (qy * qy + qz * qz));
}