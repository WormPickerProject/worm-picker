// plate_position_analyzer.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <filesystem>
#include <iostream>
#include "worm_picker_core/system/calibration/plate_position_analyzer.hpp"
#include "worm_picker_core/infrastructure/parsers/workstation_geometry_parser.hpp"

PlatePositionAnalyzer::PlatePositionAnalyzer(const PoseMap& recorded_positions)
    : recorded_positions_(recorded_positions)
{
    const auto current_path = std::filesystem::current_path().string();
    const auto config_path = 
        "/worm-picker/worm_picker_core/config/parameters/workstation_geometry.json";

    workstation_geometry_ = [](auto geometry) -> decltype(auto) {
        std::ranges::for_each(geometry.getFixedPoints(), [](auto& point) { 
            point.setY(point.getY() * -1.0);  
        });
        return geometry;
    }(WorkstationGeometryParser(current_path + config_path).getGeometry());

    std::tie(transformation_matrix_, offset_vector_) = calculateAffineTransformation();
    normalized_poses_ = normalizeAllPoints();
    averageNormalizedPoints();
}

PlatePositionAnalyzer::TranformationMatrix PlatePositionAnalyzer::calculateAffineTransformation() 
{
    Eigen::MatrixXd A(6, 6);
    Eigen::VectorXd B(6);

    int row = 0;
    for (const auto& [recorded_ref_name, recorded_pose] : recorded_positions_) {
        const auto fixed_point_iter = std::ranges::find_if(workstation_geometry_.getFixedPoints(),
            [&recorded_ref_name](const auto& fp) { return fp.getName() == recorded_ref_name; }
        );
        if (fixed_point_iter == workstation_geometry_.getFixedPoints().end()) {
            continue;
        }

        const auto ref_positions = std::pair{
            Point{fixed_point_iter->getX(), fixed_point_iter->getY()},
            Point{recorded_pose.pose.position.x, recorded_pose.pose.position.y}
        };

        A.row(row) << 
            ref_positions.first.x * 0.001, ref_positions.first.y * 0.001, 1.0, 0.0, 0.0, 0.0;
        B(row++) = ref_positions.second.x;
        A.row(row) << 
            0.0, 0.0, 0.0, ref_positions.first.x * 0.001, ref_positions.first.y * 0.001, 1.0;
        B(row++) = ref_positions.second.y;

        if (row == 6) break; 
    }

    Eigen::VectorXd params = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(B);

    Matrix2x2 transformation_matrix;
    Vector2 offset_vector;

    transformation_matrix << params(0), params(1), params(3), params(4);
    offset_vector << params(2), params(5);

    return {transformation_matrix, offset_vector};
}

PlatePositionAnalyzer::NormalizedPoseMap PlatePositionAnalyzer::normalizeAllPoints() 
{
    NormalizedPoseMap normalized_poses;

    for (const auto& [name, recorded_pose] : recorded_positions_) {
        const auto reference_name = getRowLetter(name);
        const auto reference_quaternion = Quaternion(recorded_pose.pose.orientation);
        auto quaternion_map = transformQuaternions(reference_name, reference_quaternion);

        for (const auto& geometry_point : workstation_geometry_.getFixedPoints()) {
            Pose transformed_pose = transformPoseUsingAffine(
                recorded_pose, 
                geometry_point, 
                quaternion_map
            );
            normalized_poses[name].emplace(geometry_point.getName(), std::move(transformed_pose));
        }
    }

    return normalized_poses;
}

void PlatePositionAnalyzer::averageNormalizedPoints() 
{
    std::unordered_map<std::string, std::vector<Pose>> point_poses_map;

    for (const auto& [_, pose_map] : normalized_poses_) {
        for (const auto& [geom_name, pose] : pose_map) {
            point_poses_map[geom_name].push_back(pose);
        }
    }

    for (const auto& [geom_name, poses] : point_poses_map) {
        const double count = static_cast<double>(poses.size());
        
        double sum_z = 0.0, sum_qx = 0.0, sum_qy = 0.0, sum_qz = 0.0, sum_qw = 0.0;

        for (const auto& pose_stamped : poses) {
            sum_z  += pose_stamped.pose.position.z;
            sum_qx += pose_stamped.pose.orientation.x;
            sum_qy += pose_stamped.pose.orientation.y;
            sum_qz += pose_stamped.pose.orientation.z;
            sum_qw += pose_stamped.pose.orientation.w;
        }

        const double magnitude = std::sqrt(
            (sum_qx * sum_qx + sum_qy * sum_qy + 
             sum_qz * sum_qz + sum_qw * sum_qw) / (count * count)
        );

        Pose averaged_pose;
        averaged_pose.pose.position.z = sum_z / count;
        averaged_pose.pose.orientation.x = (sum_qx / count) / magnitude;
        averaged_pose.pose.orientation.y = (sum_qy / count) / magnitude;
        averaged_pose.pose.orientation.z = (sum_qz / count) / magnitude;
        averaged_pose.pose.orientation.w = (sum_qw / count) / magnitude;

        averaged_poses_.emplace(geom_name, std::move(averaged_pose));
    }
}

Quaternion PlatePositionAnalyzer::normalizeQuaternion(const Quaternion& quat) const 
{
    double magnitude = std::sqrt(
        quat.x * quat.x + quat.y * quat.y + 
        quat.z * quat.z + quat.w * quat.w
    );
    return Quaternion{
        quat.x / magnitude,
        quat.y / magnitude,
        quat.z / magnitude,
        quat.w / magnitude
    };
}

PlatePositionAnalyzer::QuaternionMap
PlatePositionAnalyzer::transformQuaternions(const std::string& ref_key, 
                                            const Quaternion& ref_quat) const 
{
    static constexpr char ROW_START = 'A';
    static constexpr char BASE_ROW = 'G';
    static constexpr char ROW_END = 'M';

    QuaternionMap base_quaternions;
    base_quaternions.reserve(ROW_END - ROW_START + 1);

    const double angle_step = workstation_geometry_.getRaySeparationAngle() * M_PI / 360.0;

    for (char row = ROW_START; row <= ROW_END; ++row) {
        const double half_angle = (row - BASE_ROW) * angle_step;
        base_quaternions.try_emplace(
            std::string(1, row),
            std::sin(half_angle), 0.0, 0.0, std::cos(half_angle)
        );
    }

    const auto& reference_quat = base_quaternions.at(ref_key);
    const auto source_to_ref = ref_quat * reference_quat.inverse();

    QuaternionMap result;
    result.reserve(base_quaternions.size());
    
    for (const auto& [row, base_quat] : base_quaternions) {
        result.try_emplace(row, source_to_ref * base_quat);
    }

    return result;
}

PlatePositionAnalyzer::Pose 
PlatePositionAnalyzer::transformPoseUsingAffine(const Pose& pose, 
                                                const FixedPoint& geometry_point,
                                                const QuaternionMap& quaternions) const 
{
    Pose transformed_pose = pose;

    // Matrix2x2 transformation_matrix;
    // transformation_matrix << 0.92639976, -0.0101191, 
    //                         0.93426879, -0.4788462; 
    // transformation_matrix << 2.1667, -0.0101191, 
    //                          -0.1667, 0.9365; 
    // Vector2 offset_vector;
    // offset_vector << -0.6298, 0.0858;

    Eigen::Vector2d cad_position(geometry_point.getX() * 0.001, geometry_point.getY() * 0.001);

    // std::cout << "transformation_matrix: " << transformation_matrix.transpose() << std::endl;
    // std::cout << "offset_vector: " << offset_vector.transpose() << std::endl;
    //std::cout << "cad_position: " << cad_position.transpose() << std::endl;

    // Eigen::Vector2d robot_position = transformation_matrix_ * cad_position + offset_vector_;
    // std::cout << transformation_matrix_ << std::endl;
    // std::cout << offset_vector_ << std::endl;
    Eigen::Vector2d robot_position = transformation_matrix_ * cad_position + offset_vector_;

    // std::cout << "robot_position: " << robot_position.transpose() << std::endl;

    transformed_pose.pose.position.x = robot_position.x();
    transformed_pose.pose.position.y = robot_position.y();

    const auto& quat = quaternions.at(getRowLetter(geometry_point.getName()));
    auto normalized_quat = normalizeQuaternion(quat);

    transformed_pose.pose.orientation.x = normalized_quat.x;
    transformed_pose.pose.orientation.y = normalized_quat.y;
    transformed_pose.pose.orientation.z = normalized_quat.z;
    transformed_pose.pose.orientation.w = normalized_quat.w;

    return transformed_pose;
}