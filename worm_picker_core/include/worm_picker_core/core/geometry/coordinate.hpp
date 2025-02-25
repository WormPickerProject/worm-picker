// coordinate.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

class Coordinate {
public:
    Coordinate() = default;
    constexpr Coordinate(
        double px, double py, double pz, 
        double ox, double oy, double oz, double ow)
        : position_x_(px), position_y_(py), position_z_(pz), 
          orientation_x_(ox), orientation_y_(oy), orientation_z_(oz), orientation_w_(ow) {}

    constexpr double getPositionX() const { return position_x_; }
    constexpr double getPositionY() const { return position_y_; }
    constexpr double getPositionZ() const { return position_z_; }
    constexpr double getOrientationX() const { return orientation_x_; }
    constexpr double getOrientationY() const { return orientation_y_; }
    constexpr double getOrientationZ() const { return orientation_z_; }
    constexpr double getOrientationW() const { return orientation_w_; }

    constexpr std::tuple<double, double, double> getPosition() const { 
        return {position_x_, position_y_, position_z_}; 
    }
    constexpr std::tuple<double, double, double, double> getOrientation() const { 
        return {orientation_x_, orientation_y_, orientation_z_, orientation_w_}; 
    }

    constexpr void setPositionX(double x) { position_x_ = x; }
    constexpr void setPositionY(double y) { position_y_ = y; }
    constexpr void setPositionZ(double z) { position_z_ = z; }
    constexpr void setOrientationX(double x) { orientation_x_ = x; }
    constexpr void setOrientationY(double y) { orientation_y_ = y; }
    constexpr void setOrientationZ(double z) { orientation_z_ = z; }
    constexpr void setOrientationW(double w) { orientation_w_ = w; }

private:
    double position_x_{};
    double position_y_{}; 
    double position_z_{};
    double orientation_x_{}; 
    double orientation_y_{}; 
    double orientation_z_{}; 
    double orientation_w_{};
};