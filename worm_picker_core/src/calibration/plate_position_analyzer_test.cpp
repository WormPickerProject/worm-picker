// plate_position_analyzer_test.cpp
#include "worm_picker_core/calibration/plate_position_analyzer.hpp"
#include <rclcpp/rclcpp.hpp>

class PlatePositionAnalyzerTest : public rclcpp::Node {
public:
    PlatePositionAnalyzerTest() : Node("plate_position_analyzer_test") {
        PlatePositionAnalyzer::PoseMap recorded_positions;
        
        // G2 recorded position
        geometry_msgs::msg::PoseStamped g2;
        g2.pose.position.x = 0.37756;
        g2.pose.position.y = 0.00000;
        g2.pose.position.z = 0.32738;
        g2.pose.orientation.x = 0.70732;
        g2.pose.orientation.y = 0.00000;
        g2.pose.orientation.z = 0.70690;
        g2.pose.orientation.w = 0.00000;
        recorded_positions["G2"] = g2;
        
        // G3 recorded position
        geometry_msgs::msg::PoseStamped g3;
        g3.pose.position.x = 0.48750;
        g3.pose.position.y = 0.00000;
        g3.pose.position.z = 0.32604;
        g3.pose.orientation.x = 0.70726;
        g3.pose.orientation.y = 0.00000;
        g3.pose.orientation.z = 0.70695;
        g3.pose.orientation.w = 0.00000;
        recorded_positions["G3"] = g3;
        
        // J3 recorded position
        geometry_msgs::msg::PoseStamped j2;
        j2.pose.position.x = 0.39383;
        j2.pose.position.y = 0.18084;
        j2.pose.position.z = 0.32797;
        j2.pose.orientation.x = 0.69078;
        j2.pose.orientation.y = 0.15102;
        j2.pose.orientation.z = 0.69080;
        j2.pose.orientation.w = -0.15102;
        recorded_positions["J2"] = j2;

        PlatePositionAnalyzer analyzer(recorded_positions);
        auto normalized_sets = analyzer.getNormalizedPoses();
        auto averaged_poses = analyzer.getAveragedPoses();
        
        printNormalizedPoses(normalized_sets);
        printAveragedPoses(averaged_poses);
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
                  << std::fixed << std::setprecision(3)
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