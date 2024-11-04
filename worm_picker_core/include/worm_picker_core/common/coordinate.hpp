// coordinate.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef COORDINATE_HPP
#define COORDINATE_HPP

/**
 * @class Coordinate
 * @brief Represents the coordinate data information of a workstation or hotel.
 */
class Coordinate 
{
public:
    /**
     * @brief Default constructor.
     */
    Coordinate() = default;

    /**
     * @brief Constructs a Coordinate with the given position and orientation.
     * @param px Position x-coordinate.
     * @param py Position y-coordinate.
     * @param pz Position z-coordinate.
     * @param ox Orientation quaternion x-component.
     * @param oy Orientation quaternion y-component.
     * @param oz Orientation quaternion z-component.
     * @param ow Orientation quaternion w-component.
     */
    Coordinate(double px, double py, double pz,
               double ox, double oy, double oz, double ow);

    double getPositionX() const;
    double getPositionY() const;
    double getPositionZ() const;
    double getOrientationX() const;
    double getOrientationY() const;
    double getOrientationZ() const;
    double getOrientationW() const;

private:
    double position_x_; ///< X position of the workstation.
    double position_y_; ///< Y position of the workstation.
    double position_z_; ///< Z position of the workstation.
    double orientation_x_; ///< X component of orientation quaternion.
    double orientation_y_; ///< Y component of orientation quaternion.
    double orientation_z_; ///< Z component of orientation quaternion.
    double orientation_w_; ///< W component of orientation quaternion.
};

/**
 * @class WorkstationData
 * @brief Contains coordinate data for the workstation.
 */
class WorkstationData {
public:
    /**
     * @brief Default constructor.
     */
    WorkstationData() = default;

    /**
     * @brief Constructs WorkstationData with a coordinate.
     * @param coordinate Coordinate data of the workstation.
     */
    explicit WorkstationData(const Coordinate& coordinate);

    const Coordinate& getCoordinate() const;

private:
    Coordinate coordinate_;
};

/**
 * @class HotelData
 * @brief Contains coordinate data for the hotels.
 */
class HotelData {
public:
    /**
     * @brief Default constructor.
     */
    HotelData() = default;

    /**
     * @brief Constructs HotelData with a coordinate.
     * @param coordinate Coordinate data of the hotel.
     */
    explicit HotelData(const Coordinate& coordinate);

    const Coordinate& getCoordinate() const;

private:
    Coordinate coordinate_;
};

#endif // COORDINATE_HPP
