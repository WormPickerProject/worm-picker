// parameter_utils.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>

namespace param_utils {

template<typename T>
inline std::optional<T> getParameter(const rclcpp::Node::SharedPtr& node, const std::string& name) 
{
    try {
        return node->get_parameter(name).get_value<T>();
    } catch (const rclcpp::exceptions::ParameterNotDeclaredException&) {
        return std::nullopt;
    }
}

template<>
inline std::optional<std::vector<std::string>> getParameter(const rclcpp::Node::SharedPtr& node, 
                                                            const std::string& name) 
{
    try {
        return node->get_parameter(name).get_value<std::vector<std::string>>();
    } catch (const rclcpp::exceptions::ParameterNotDeclaredException&) {
        return std::nullopt;
    }
}

template<typename T>
bool setParameter(const rclcpp::Node::SharedPtr& node, const std::string& name, const T& value) 
{
    try {
        const rclcpp::Parameter param(name, value);
        return node->set_parameter(param).successful;
    } catch (const rclcpp::exceptions::ParameterNotDeclaredException&) {
        return false;
    }
}

} // namespace param_utils