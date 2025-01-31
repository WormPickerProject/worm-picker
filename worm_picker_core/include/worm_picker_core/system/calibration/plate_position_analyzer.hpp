// plate_position_analyzer.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <map>
// #include <string>
// #include <vector>
#include <Eigen/Dense>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "worm_picker_core/core/geometry/fixed_point.hpp"
#include "worm_picker_core/core/geometry/workstation_geometry.hpp"

struct Point;
struct Quaternion;

class PlatePositionAnalyzer {
public:
    using Pose = geometry_msgs::msg::PoseStamped;
    using PoseMap = std::map<std::string, Pose>;
    using NormalizedPoseMap = std::map<std::string, PoseMap>;

    explicit PlatePositionAnalyzer(const PoseMap& recorded_positions);

    const NormalizedPoseMap& getNormalizedPoses() const { return normalized_poses_; }
    const PoseMap& getAveragedPoses() const { return averaged_poses_; }

private:
    using Matrix2x2 = Eigen::Matrix2d;
    using Vector2 = Eigen::Vector2d;
    using QuaternionMap = std::unordered_map<std::string, Quaternion>; 
    using TranformationMatrix = std::pair<Matrix2x2, Vector2>;

    TranformationMatrix calculateAffineTransformation();
    NormalizedPoseMap normalizeAllPoints();
    void averageNormalizedPoints();
    Quaternion normalizeQuaternion(const Quaternion& quat) const;
    QuaternionMap transformQuaternions(const std::string& ref_key, 
                                       const Quaternion& ref_quat) const;
    Pose transformPoseUsingAffine(const Pose& pose, 
                                  const FixedPoint& geometry_point,
                                  const QuaternionMap& quaternions) const;
    static std::string getRowLetter(const std::string& point_name) {
        return std::string(1, point_name[0]);
    }

    PoseMap recorded_positions_;
    WorkstationGeometry workstation_geometry_;
    Matrix2x2 transformation_matrix_;
    Vector2 offset_vector_;
    NormalizedPoseMap normalized_poses_;
    PoseMap averaged_poses_;
};

struct Point {
    double x;
    double y;
};

struct Quaternion {
    double x{0.0}, y{0.0}, z{0.0}, w{1.0};

    Quaternion(double x_, double y_, double z_, double w_) 
        : x(x_), y(y_), z(z_), w(w_) {}
    
    Quaternion(const geometry_msgs::msg::Quaternion& msg_quat)
        : x(msg_quat.x), y(msg_quat.y), z(msg_quat.z), w(msg_quat.w) {}

    Quaternion operator*(const Quaternion& other) const {
        return Quaternion{
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        };
    }

    Quaternion inverse() const {
        return Quaternion{-x, -y, -z, w};
    }
};