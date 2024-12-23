// stage_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef STAGE_DATA_HPP
#define STAGE_DATA_HPP

#include <moveit/task_constructor/stage.h>
#include <rclcpp/rclcpp.hpp>

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
};

#endif // STAGE_DATA_HPP
