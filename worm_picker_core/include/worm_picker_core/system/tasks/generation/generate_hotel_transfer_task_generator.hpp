// generate_hotel_transfer_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/model/hotel_data.hpp"
#include "worm_picker_core/system/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/system/tasks/generation/transfer_task_config.hpp"

class GenerateHotelTransferTaskGenerator 
    : public GenericTaskGenerator<HotelData, std::pair<int, int>> {
public:
    GenerateHotelTransferTaskGenerator(const std::unordered_map<std::string, HotelData>& hotel_map);
    void generateTasks() override;

protected:
    std::pair<int, int> parseName(const std::string& name) const override;
    std::string generateTaskName(const std::pair<int, int>& parsed_name) const override;
    StageSequence createStagesForTask(const HotelData& target_data, 
                                      const std::pair<int, int>& parsed_name) const override;

private:
    Coordinate calculateDerivedPoint(const Coordinate& hotel_coord, double desired_joint1_rad) const;
    Coordinate handleToHotelPoint(const Coordinate& coord, double desired_joint1_rad) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;
    std::shared_ptr<StageData> createMoveToJointStage(double joint_angle_deg) const;
    double hotelAngle(const std::tuple<double, double, double, double>& orientation) const;

private:
    std::unordered_map<int, HotelData> target_rooms_by_hotel_{};
    rclcpp::Node::SharedPtr node_;
    moveit::core::RobotModelPtr robot_model_;
    const moveit::core::JointModelGroup* joint_model_group_{nullptr};
};