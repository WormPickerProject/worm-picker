// generate_transfer_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/model/hotel_data.hpp"
#include "worm_picker_core/system/tasks/generation/generic_task_generator.hpp"
#include "worm_picker_core/system/tasks/generation/transfer_task_config.hpp"

class GenerateTransferTaskGenerator : public GenericTaskGenerator<HotelData, std::pair<int, int>> {
public:
    using TaskType = transfer_config::TaskType;
    GenerateTransferTaskGenerator(const std::unordered_map<std::string, HotelData>& hotel_map,
                                  TaskType task_type);
    void generateTasks() override;

protected:
    std::pair<int, int> parseName(const std::string& name) const override;
    std::string generateTaskName(const std::pair<int, int>& parsed_name) const override;
    StageSequence createStagesForTask(const HotelData& data, 
                                      const std::pair<int, int>& parsed_name) const override;

private:
    Coordinate calculateDerivedPoint(const Coordinate& hotel_coord) const;
    Coordinate handleToHotelPoint(const Coordinate& coord) const;
    std::shared_ptr<StageData> createMoveToPointStage(const Coordinate& coord) const;
    std::shared_ptr<StageData> createMoveToJointStage(double joint_angle) const;
    double hotelAngle(const std::tuple<double, double, double, double>& orientation) const;

    TaskType task_type_;
    rclcpp::Node::SharedPtr node_;
    moveit::core::RobotModelPtr robot_model_;
    const moveit::core::JointModelGroup* joint_model_group_;
};