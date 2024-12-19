// coordinate.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate {
public:
    Coordinate() = default;
    Coordinate(double px, double py, double pz, double ox, double oy, double oz, double ow);
    double getPositionX() const;
    double getPositionY() const;
    double getPositionZ() const;
    double getOrientationX() const;
    double getOrientationY() const;
    double getOrientationZ() const;
    double getOrientationW() const;

private:
    double position_x_;
    double position_y_; 
    double position_z_;
    double orientation_x_; 
    double orientation_y_; 
    double orientation_z_; 
    double orientation_w_;
};

#endif // COORDINATE_HPP
