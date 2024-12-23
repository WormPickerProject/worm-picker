// fixed_point.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP

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

#endif // FIXED_POINT_HPP
