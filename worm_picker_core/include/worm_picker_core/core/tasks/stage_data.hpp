// stage_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/stage.h>

enum class StageType { 
    MOVE_TO_POINT, 
    MOVE_TO_JOINT, 
    MOVE_RELATIVE 
};

class StageData {
public:
    using Stage = moveit::task_constructor::Stage;
    using StagePtr = std::unique_ptr<Stage>;
    using NodePtr = rclcpp::Node::SharedPtr;

    virtual ~StageData() = default;
    virtual StageType getType() const = 0;
    virtual StagePtr createStage(const std::string& name, const NodePtr& node) const = 0;
    virtual std::unique_ptr<StageData> clone() const = 0;

protected:
    static const std::unordered_map<StageType, std::string> type_map_;
};

inline const std::unordered_map<StageType, std::string> StageData::type_map_ = {
    {StageType::MOVE_TO_POINT, "move_to_point"},
    {StageType::MOVE_TO_JOINT, "move_to_joint"},
    {StageType::MOVE_RELATIVE, "move_relative"}
};