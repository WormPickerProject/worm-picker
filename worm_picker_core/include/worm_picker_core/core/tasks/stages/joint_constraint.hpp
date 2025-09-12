// joint_constraint.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <vector>
#include <optional>

struct JointConstraint {
    std::string joint_name;
    double min_position;         // in radians
    double max_position;         // in radians
    double tolerance_above{0.0}; // tolerance outside bounds
    double tolerance_below{0.0}; // tolerance outside bounds  
    double weight{1.0};          // importance (0-1)
    
    JointConstraint(const std::string& name, double min, double max)
        : joint_name(name), min_position(min), max_position(max) {}
    
    JointConstraint(const std::string& name, double min, double max, double weight)
        : joint_name(name), min_position(min), max_position(max), weight(weight) {}
};

namespace JointNames {
    constexpr const char* JOINT_1 = "joint_1";
    constexpr const char* JOINT_2 = "joint_2";
    constexpr const char* JOINT_3 = "joint_3";
    constexpr const char* JOINT_4 = "joint_4";
    constexpr const char* JOINT_5 = "joint_5";
    constexpr const char* JOINT_6 = "joint_6";
}

constexpr double deg2rad(double degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
}
