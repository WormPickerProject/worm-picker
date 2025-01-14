// parameter_manager.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/system/management/parameter_manager.hpp"

ParameterManager::ParameterManager(const NodePtr& node, const std::string& yaml_file)
    : node_{node}
{
    YAML::Node config = YAML::LoadFile(yaml_file);
    auto params = config["parameters"];
    processNode(params, "");
}

void ParameterManager::processNode(const YAML::Node& node, const std::string& prefix) 
{
    for (const auto& it : node) {
        const auto key = it.first.as<std::string>();
        const auto& value = it.second;
        
        const auto paramName = prefix.empty() ? key : prefix + "." + key;

        if (value.IsMap()) {
            processNode(value, paramName);
            continue;
        }

        const auto supportedTypes = {
            &ParameterManager::tryDeclareParam<bool>,
            &ParameterManager::tryDeclareParam<int>,
            &ParameterManager::tryDeclareParam<double>,
            &ParameterManager::tryDeclareParam<std::string>,
            &ParameterManager::tryDeclareParam<std::vector<std::string>>
        };

        bool declared = false;
        for (const auto& tryDeclare : supportedTypes) {
            if ((this->*tryDeclare)(paramName, value)) {
                declared = true;
                break;
            }
        }

        if (!declared) {
            RCLCPP_WARN(
                node_->get_logger(),
                "Failed to determine type for parameter: %s",
                paramName.c_str()
            );
        }
    }
}