// stage_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef STAGE_DATA_HPP
#define STAGE_DATA_HPP

#include <moveit/task_constructor/stage.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>

/**
 * @enum StageType
 * @brief Enumerates the types of stages available.
 */
enum class StageType { MOVE_TO_POINT, MOVE_TO_JOINT, MOVE_RELATIVE };

/**
 * @class StageData
 * @brief Abstract base class for different types of stage data.
 */
class StageData 
{
public:
    virtual ~StageData() = default;

    /**
     * @brief Retrieves the type of the stage.
     * @return StageType The type of the stage.
     */
    virtual StageType getType() const noexcept = 0;

    /**
     * @brief Creates a MoveIt stage based on the data.
     * @param name The name of the stage.
     * @param node Shared pointer to the ROS2 node.
     * @return A unique pointer to the created stage.
     */
    virtual std::unique_ptr<moveit::task_constructor::Stage> createStage(const std::string& name,
                                                                         const rclcpp::Node::SharedPtr& node) const = 0;
};

#endif // STAGE_DATA_HPP
