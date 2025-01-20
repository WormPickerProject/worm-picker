// fixed_point.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

class FixedPoint {
public:
    FixedPoint() = default; 
    
    FixedPoint(const std::string& name, double x, double y)
        : name_(name), x_(x), y_(y) {}
    
    const std::string& getName() const { return name_; }
    double getX() const { return x_; }
    double getY() const { return y_; }

    void setName(const std::string& name) { name_ = name; }
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

private:
    std::string name_{};
    double x_{};
    double y_{};
};