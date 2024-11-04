// coordinate.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/common/coordinate.hpp"

Coordinate::Coordinate(double px, double py, double pz,
                       double ox, double oy, double oz, double ow)
    : position_x_(px), position_y_(py), position_z_(pz),
      orientation_x_(ox), orientation_y_(oy), orientation_z_(oz), orientation_w_(ow)
{
}

double Coordinate::getPositionX() const 
{
    return position_x_;
}

double Coordinate::getPositionY() const 
{
    return position_y_;
}

double Coordinate::getPositionZ() const 
{
    return position_z_;
}

double Coordinate::getOrientationX() const 
{
    return orientation_x_;
}

double Coordinate::getOrientationY() const 
{
    return orientation_y_;
}

double Coordinate::getOrientationZ() const 
{
    return orientation_z_;
}

double Coordinate::getOrientationW() const 
{
    return orientation_w_;
}

WorkstationData::WorkstationData(const Coordinate& coordinate)
    : coordinate_(coordinate)
{
}

const Coordinate& WorkstationData::getCoordinate() const 
{
    return coordinate_;
}

HotelData::HotelData(const Coordinate& coordinate)
    : coordinate_(coordinate)
{
}

const Coordinate& HotelData::getCoordinate() const 
{
    return coordinate_;
}
