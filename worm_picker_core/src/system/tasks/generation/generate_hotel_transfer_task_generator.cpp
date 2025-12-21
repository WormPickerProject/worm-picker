// generate_hotel_transfer_task_generator.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include <numbers>
#include <tf2_eigen/tf2_eigen.hpp>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include "worm_picker_core/utils/global_node.hpp"
#include "worm_picker_core/utils/parameter_utils.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_point_data.hpp"
#include "worm_picker_core/core/tasks/stages/move_to_joint_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_hotel_transfer_task_generator.hpp"

GenerateHotelTransferTaskGenerator::GenerateHotelTransferTaskGenerator(
    const std::unordered_map<std::string, HotelData>& hotel_map)
  : GenericTaskGenerator(hotel_map),
    node_(worm_picker::getGlobalNode())
{
    robot_model_ = robot_model_loader::RobotModelLoader(node_).getModel();
    joint_model_group_ = robot_model_->getJointModelGroup(
        *param_utils::getParameter<std::string>(node_, "operation_modes.group"));
    
    for (const auto& name : getDataMapKeys()) {
        const auto [hotel_id, room] = parseName(name);
        
        if (room == transfer_config::rooms::TARGET_ROOM) {
            target_rooms_by_hotel_[hotel_id] = this->data_map_.at(name);
        }
    }

    constexpr size_t min_required_hotels = 2;
    if (target_rooms_by_hotel_.size() < min_required_hotels) {
        throw std::runtime_error(
            fmt::format("Insufficient hotels with target room: need {}, found {}",
                        min_required_hotels, target_rooms_by_hotel_.size()));
    }
}

void GenerateHotelTransferTaskGenerator::generateTasks()
{
    for (const auto& [source_hotel, _] : target_rooms_by_hotel_) {
        for (const auto& [destination_hotel, destination_data] : target_rooms_by_hotel_) {
            if (source_hotel != destination_hotel) {
                const std::pair<int, int> hotel_pair{source_hotel, destination_hotel};
                
                task_data_map_.emplace(
                    generateTaskName(hotel_pair),
                    TaskData(createStagesForTask(destination_data, hotel_pair))
                );
            }
        }
    }
}

std::pair<int, int> GenerateHotelTransferTaskGenerator::parseName(const std::string& name) const
{
    const int num = std::stoi(name);
    const int hotel_number = num / transfer_config::rooms::HOTEL_ROOM_DIVISOR;
    const int room_number  = num % transfer_config::rooms::HOTEL_ROOM_DIVISOR;
    return {hotel_number, room_number};
}

std::string
GenerateHotelTransferTaskGenerator::generateTaskName(const std::pair<int, int>& parsed_name) const
{
    return std::string(transfer_config::prefix::HOTEL_TO_HOTEL)
        + std::to_string(parsed_name.first) + ":"
        + std::to_string(parsed_name.second);
}

GenerateHotelTransferTaskGenerator::StageSequence
GenerateHotelTransferTaskGenerator::createStagesForTask(const HotelData& destination_data,
                                                        const std::pair<int, int>& hotel_pair) const
{
    const auto& source_coordinate = 
        target_rooms_by_hotel_.at(hotel_pair.first).getCoordinate();
    const auto& destination_coordinate = 
        destination_data.getCoordinate();

    const double source_angle_radians = 
        hotelAngle(source_coordinate.getOrientation());
    const auto derived_source_point = 
        calculateDerivedPoint(destination_coordinate, source_angle_radians);

    constexpr double radians_to_degrees = 180.0 / std::numbers::pi;
    const double destination_angle_degrees = 
        hotelAngle(destination_coordinate.getOrientation()) * radians_to_degrees;

    return StageSequence{
        createMoveToPointStage(derived_source_point),
        createMoveToJointStage(destination_angle_degrees)
    };
}

Coordinate GenerateHotelTransferTaskGenerator::calculateDerivedPoint(const Coordinate& hotel_coord,
                                                                     double desired_joint1_rad) const
{
    const double theta_rad = hotelAngle(hotel_coord.getOrientation());
    const double cos_theta = std::cos(theta_rad);
    const double sin_theta = std::sin(theta_rad);
    const auto offset = transfer_config::offset::POSITION_OFFSET;

    const Coordinate offset_position(
    hotel_coord.getPositionX() + (offset.x * cos_theta) + (offset.y * sin_theta),
    hotel_coord.getPositionY() + (offset.x * sin_theta) + (offset.y * cos_theta),
    hotel_coord.getPositionZ() + offset.z,
    hotel_coord.getOrientationX(),
    hotel_coord.getOrientationY(),
    hotel_coord.getOrientationZ(),
    hotel_coord.getOrientationW());

    return handleToHotelPoint(offset_position, desired_joint1_rad);
}

Coordinate GenerateHotelTransferTaskGenerator::handleToHotelPoint(const Coordinate& coord,
                                                                  double desired_joint1_rad) const
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
    joint_values[0] = desired_joint1_rad;
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
GenerateHotelTransferTaskGenerator::createMoveToPointStage(const Coordinate& coord) const
{
    return std::make_shared<MoveToPointData>(
        coord.getPositionX(), coord.getPositionY(), coord.getPositionZ(),
        coord.getOrientationX(), coord.getOrientationY(),
        coord.getOrientationZ(), coord.getOrientationW());
}

std::shared_ptr<StageData>
GenerateHotelTransferTaskGenerator::createMoveToJointStage(double joint_angle_deg) const
{
    return std::make_shared<MoveToJointData>(
        std::map<std::string, double>{{"joint_1", joint_angle_deg}});
}

double GenerateHotelTransferTaskGenerator::hotelAngle(
    const std::tuple<double, double, double, double>& orientation) const
{
    const auto& [qx, qy, qz, qw] = orientation;
    return std::atan2(2 * (qw * qz + qx * qy), 1 - 2 * (qy * qy + qz * qz));
}
