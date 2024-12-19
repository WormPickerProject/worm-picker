// parameter_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef PARAMETER_MANAGER_HPP
#define PARAMETER_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>

/**
 * @class ParameterManager
 * @brief Manages ROS2 parameter declaration and access
 * 
 * @details
 * Handles the declaration and management of ROS2 parameters with default values
 * and type safety. Parameters are declared during construction and can be accessed
 * through typed getter methods.
 */
class ParameterManager {
public:
    // Public Type Aliases
    using NodePtr = rclcpp::Node::SharedPtr;

    /**
     * @brief Constructs a ParameterManager
     * 
     * @param node ROS2 node to manage parameters for
     */
    explicit ParameterManager(const NodePtr& node);

private:
    /**
     * @brief Declares all parameters with their default values
     */
    void declareParameters();

    /**
     * @brief Helper struct to define parameter metadata
     */
    struct ParameterDefinition {
        const std::string name;           ///< The name of the parameter
        rclcpp::ParameterValue value;     ///< The value assigned to the parameter
        const std::string description;    ///< The description of the parameter
    };

    /**
     * @brief Static definitions of all parameters
     * 
     * Centralized location for all parameter definitions with their metadata
     */
    static const std::array<ParameterDefinition, 15> PARAMETER_DEFINITIONS;

    // ROS 2 Components
    NodePtr node_;    ///< ROS2 node handle
};

#endif // PARAMETER_MANAGER_HPP
