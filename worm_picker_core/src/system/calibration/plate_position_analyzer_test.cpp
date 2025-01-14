// plate_position_analyzer_test.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/system/calibration/plate_position_analyzer.hpp"
#include "worm_picker_core/system/calibration/workstation_json_generator.hpp"

class PlatePositionAnalyzerTest : public rclcpp::Node {
public:
    PlatePositionAnalyzerTest() : Node("plate_position_analyzer_test") {
        PlatePositionAnalyzer::PoseMap recorded_positions;
        
        // G3 recorded position
        geometry_msgs::msg::PoseStamped g3;
        g3.pose.position.x = 0.48638;
        g3.pose.position.y = 0.00001;
        g3.pose.position.z = 0.32628;
        g3.pose.orientation.x = 0.70737;
        g3.pose.orientation.y = -0.00005;
        g3.pose.orientation.z = 0.70737;
        g3.pose.orientation.w = -0.00001;
        recorded_positions["G3"] = g3;

        // D3 recorded position
        geometry_msgs::msg::PoseStamped d3;
        d3.pose.position.x = 0.49524;
        d3.pose.position.y = -0.22873;
        d3.pose.position.z = 0.32744;
        d3.pose.orientation.x = 0.68821;
        d3.pose.orientation.y = -0.15015;
        d3.pose.orientation.z = 0.69352;
        d3.pose.orientation.w = 0.15116;
        recorded_positions["D3"] = d3;

        // J3 recorded position
        geometry_msgs::msg::PoseStamped j3;
        j3.pose.position.x = 0.49029;
        j3.pose.position.y = 0.22829;
        j3.pose.position.z = 0.32897;
        j3.pose.orientation.x = 0.68835;
        j3.pose.orientation.y = 0.14968;
        j3.pose.orientation.z = 0.69357;
        j3.pose.orientation.w = -0.15078;
        recorded_positions["J3"] = j3;

        PlatePositionAnalyzer analyzer(recorded_positions);
        auto normalized_sets = analyzer.getNormalizedPoses();
        auto averaged_poses = analyzer.getAveragedPoses();
        
        printNormalizedPoses(normalized_sets);
        printAveragedPoses(averaged_poses);

        WorkstationJsonGenerator json_generator(averaged_poses);
        json_generator.generateJson(
            "/home/logan/worm-picker/worm_picker_core/config/workstation_data.json");

    }

private:
    void printNormalizedPoses(const PlatePositionAnalyzer::NormalizedPoseMap& normalized_sets) const {
        for (const auto& [ref_name, normalized_points] : normalized_sets) {
            std::cout << "\nNormalized Points (relative to " << ref_name << "):" << std::endl;
            printTableHeader();
            
            for (const auto& [point_name, pose] : normalized_points) {
                printPoseData(point_name, pose);
            }
        }
    }

    void printAveragedPoses(const PlatePositionAnalyzer::PoseMap& averaged_poses) const {
        std::cout << "\nAveraged Points:" << std::endl;
        printTableHeader();

        for (const auto& [point_name, pose] : averaged_poses) {
            printPoseData(point_name, pose);
        }
    }

    void printTableHeader() const {
        std::cout << std::left << std::setw(8) << "Point"
                  << std::right 
                  << std::setw(10) << "X"
                  << std::setw(10) << "Y"
                  << std::setw(10) << "Z"
                  << std::setw(10) << "OX"
                  << std::setw(10) << "OY"
                  << std::setw(10) << "OZ"
                  << std::setw(10) << "OW" << std::endl;
        std::cout << std::string(78, '-') << std::endl;
    }

    void printPoseData(const std::string& point_name, 
                       const geometry_msgs::msg::PoseStamped& pose) const {
        std::cout << std::left << std::setw(8) << point_name
                  << std::fixed << std::setprecision(5)
                  << std::right
                  << std::setw(10) << pose.pose.position.x
                  << std::setw(10) << pose.pose.position.y
                  << std::setw(10) << pose.pose.position.z
                  << std::setw(10) << pose.pose.orientation.x
                  << std::setw(10) << pose.pose.orientation.y
                  << std::setw(10) << pose.pose.orientation.z
                  << std::setw(10) << pose.pose.orientation.w
                  << std::endl;
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PlatePositionAnalyzerTest>());
    rclcpp::shutdown();
    return 0;
}