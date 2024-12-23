// plate_position_analyzer.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <filesystem>
#include "worm_picker_core/system/calibration/plate_position_analyzer.hpp"
#include "worm_picker_core/infrastructure/parsers/workstation_geometry_parser.hpp"

PlatePositionAnalyzer::PlatePositionAnalyzer(const PoseMap& recorded_positions)
    : recorded_positions_(recorded_positions)
{
    const auto current_path = std::filesystem::current_path().string();
    const auto config_path = "/worm-picker/worm_picker_core/config/workstation_geometry.json";

    workstation_geometry_ = [](auto geometry) -> decltype(auto) {
        std::ranges::for_each(geometry.fixed_points, [](auto& point) { 
            point.y *= -1.0; 
        });
        return geometry;
    }(WorkstationGeometryParser(current_path + config_path).getGeometry());

    normalized_poses_ = normalizeAllPoints();
    averageNormalizedPoints(normalized_poses_);
}

PlatePositionAnalyzer::NormalizedPoseMap PlatePositionAnalyzer::normalizeAllPoints() const
{
    NormalizedPoseMap normalized_poses;
    for (const auto& [recorded_ref_name, recorded_pose] : recorded_positions_) {
        const auto ref_point_iter = std::ranges::find_if(workstation_geometry_.fixed_points, 
            [&recorded_ref_name](const auto& fp) { 
                return fp.name == recorded_ref_name; 
            });

        const auto ref_positions = std::pair{
            Point{ref_point_iter->x, ref_point_iter->y},
            Point{recorded_pose.pose.position.x, recorded_pose.pose.position.y}
        };

        const auto quaternion_map = transformQuaternions(
            getRowLetter(ref_point_iter->name), 
            Quaternion(recorded_pose.pose.orientation)
        );

        auto& normalized_points = normalized_poses[recorded_ref_name];
        for (const auto& geometry_point : workstation_geometry_.fixed_points) {
            auto normalized_pose = recorded_pose;
            transformPoint(normalized_pose, geometry_point, ref_positions, quaternion_map);
            normalized_points.try_emplace(geometry_point.name, std::move(normalized_pose));
        }
    }
    return normalized_poses;
}

void PlatePositionAnalyzer::transformPoint(
    Pose& pose,
    const FixedPoint& geometry_point,
    const std::pair<Point, Point>& ref_positions,
    const std::unordered_map<std::string, Quaternion>& quaternions) const 
{
    const auto& [ref_pos, recorded_pos] = ref_positions;
    
    auto& position = pose.pose.position;
    position.x = (geometry_point.x - ref_pos.x) * MM_TO_M + recorded_pos.x;
    position.y = (geometry_point.y - ref_pos.y) * MM_TO_M + recorded_pos.y;

    const auto& quat = quaternions.at(getRowLetter(geometry_point.name));
    auto& orientation = pose.pose.orientation;
    orientation.x = quat.x;
    orientation.y = quat.y;
    orientation.z = quat.z;
    orientation.w = quat.w;
}

std::unordered_map<std::string, Quaternion>
PlatePositionAnalyzer::transformQuaternions(const std::string& ref_key, 
                                            const Quaternion& ref_quat) const 
{
    std::unordered_map<std::string, Quaternion> base_quaternions;
    base_quaternions.reserve(ROW_END - ROW_START + 1);

    const double angle_step = workstation_geometry_.ray_separation_angle * PI / 360.0;

    for (char row = ROW_START; row <= ROW_END; ++row) {
        const double half_angle = (row - BASE_ROW) * angle_step;
        base_quaternions.try_emplace(
            std::string(1, row),
            std::sin(half_angle), 0.0, 0.0, std::cos(half_angle)
        );
    }

    const auto& reference_quat = base_quaternions.at(ref_key);
    const auto source_to_ref = ref_quat * reference_quat.inverse();

    std::unordered_map<std::string, Quaternion> result;
    result.reserve(base_quaternions.size());
    
    for (const auto& [row, base_quat] : base_quaternions) {
        result.try_emplace(row, source_to_ref * base_quat);
    }

    return result;
}

void PlatePositionAnalyzer::averageNormalizedPoints(const NormalizedPoseMap& normalized_poses) 
{
    std::unordered_map<std::string, std::vector<Pose>> point_poses_map;

    for (const auto& [_, pose_map] : normalized_poses) {
        for (const auto& [geom_name, pose] : pose_map) {
            point_poses_map[geom_name].push_back(pose);
        }
    }

    for (const auto& [geom_name, poses] : point_poses_map) {
        const double count = static_cast<double>(poses.size());
        
        double sum_x = 0.0, sum_y = 0.0, sum_z = 0.0;
        double sum_qx = 0.0, sum_qy = 0.0, sum_qz = 0.0, sum_qw = 0.0;

        for (const auto& pose_stamped : poses) {
            sum_x  += pose_stamped.pose.position.x;
            sum_y  += pose_stamped.pose.position.y;
            sum_z  += pose_stamped.pose.position.z;

            sum_qx += pose_stamped.pose.orientation.x;
            sum_qy += pose_stamped.pose.orientation.y;
            sum_qz += pose_stamped.pose.orientation.z;
            sum_qw += pose_stamped.pose.orientation.w;
        }

        double avg_x  = sum_x / count;
        double avg_y  = sum_y / count;
        double avg_z  = sum_z / count;

        double avg_qx = sum_qx / count;
        double avg_qy = sum_qy / count;
        double avg_qz = sum_qz / count;
        double avg_qw = sum_qw / count;

        const double magnitude = std::sqrt(
            avg_qx * avg_qx + avg_qy * avg_qy + avg_qz * avg_qz + avg_qw * avg_qw
        );

        avg_qx /= magnitude;
        avg_qy /= magnitude;
        avg_qz /= magnitude;
        avg_qw /= magnitude;

        Pose averaged_pose;
        averaged_pose.pose.position.x = avg_x;
        averaged_pose.pose.position.y = avg_y;
        averaged_pose.pose.position.z = avg_z;
        averaged_pose.pose.orientation.x = avg_qx;
        averaged_pose.pose.orientation.y = avg_qy;
        averaged_pose.pose.orientation.z = avg_qz;
        averaged_pose.pose.orientation.w = avg_qw;

        averaged_poses_.emplace(geom_name, std::move(averaged_pose));
    }
}