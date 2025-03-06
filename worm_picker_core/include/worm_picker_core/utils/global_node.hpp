// global_node.hpp
// 
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <rclcpp/rclcpp.hpp>

namespace worm_picker {

inline rclcpp::Node::SharedPtr g_node = nullptr;

inline void setGlobalNode(const rclcpp::Node::SharedPtr & node) {
    g_node = node;
}

inline rclcpp::Node::SharedPtr getGlobalNode() {
    return g_node;
}

}  // namespace worm_picker