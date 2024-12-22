// parameter_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef PARAMETER_MANAGER_HPP
#define PARAMETER_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>
#include <yaml-cpp/yaml.h>

class ParameterManager {
public:
    using NodePtr = rclcpp::Node::SharedPtr;

    ParameterManager(const NodePtr& node, const std::string& yaml_file);

private:
    void processNode(const YAML::Node& node, const std::string& prefix);

    template<typename T>
    bool tryDeclareParam(const std::string& name, const YAML::Node& value);
    
    NodePtr node_;
};

template<typename T>
bool ParameterManager::tryDeclareParam(const std::string& name, const YAML::Node& value) 
{
    try {
        node_->declare_parameter(name, value.as<T>());
        return true;
    } catch (...) {
        return false;
    }
}

#endif // PARAMETER_MANAGER_HPP
