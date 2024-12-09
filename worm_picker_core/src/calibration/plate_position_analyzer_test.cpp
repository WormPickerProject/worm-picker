// plate_position_analyzer_test.cpp
#include "worm_picker_core/calibration/plate_position_analyzer.hpp"
#include <rclcpp/rclcpp.hpp>

class PlatePositionAnalyzerTest : public rclcpp::Node {
public:
    PlatePositionAnalyzerTest() : Node("plate_position_analyzer_test") {
        PlatePositionAnalyzer::PoseMap recorded_positions;
        
        // G4 recorded position
        geometry_msgs::msg::PoseStamped g4;
        g4.pose.position.x = 0.596523;
        g4.pose.position.y = 0.000004;
        g4.pose.position.z = 0.330944;
        g4.pose.orientation.x = 0.704379;
        g4.pose.orientation.y = -0.000080;
        g4.pose.orientation.z = 0.709824;
        g4.pose.orientation.w = -0.000014;
        recorded_positions["G4"] = g4;
        
        // D3 recorded position
        geometry_msgs::msg::PoseStamped d3;
        d3.pose.position.x = 0.499746;
        d3.pose.position.y = -0.228676;
        d3.pose.position.z = 0.330502;
        d3.pose.orientation.x = 0.688323;
        d3.pose.orientation.y = -0.150132;
        d3.pose.orientation.z = 0.693422;
        d3.pose.orientation.w = 0.151120;
        recorded_positions["D3"] = d3;
        
        // J3 recorded position
        geometry_msgs::msg::PoseStamped j3;
        j3.pose.position.x = 0.498889;
        j3.pose.position.y = 0.230619;
        j3.pose.position.z = 0.330567;
        j3.pose.orientation.x = 0.688025;
        j3.pose.orientation.y = 0.151204;
        j3.pose.orientation.z = 0.693191;
        j3.pose.orientation.w = -0.152463;
        recorded_positions["J3"] = j3;

        PlatePositionAnalyzer analyzer(recorded_positions);
        auto normalized_sets = analyzer.normalizeAllPoints();
        
        for (const auto& [ref_name, normalized_points] : normalized_sets) {
            RCLCPP_INFO(get_logger(), "\nNormalized Points (relative to %s):", ref_name.c_str());
            RCLCPP_INFO(get_logger(), "Point     X          Y          Z");
            RCLCPP_INFO(get_logger(), "--------------------------------");
            
            for (const auto& [point_name, pose] : normalized_points) {
                RCLCPP_INFO(get_logger(), "%-8s %9.3f %9.3f %9.3f",
                    point_name.c_str(),
                    pose.pose.position.x,
                    pose.pose.position.y,
                    pose.pose.position.z);
            }
        }
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PlatePositionAnalyzerTest>());
    rclcpp::shutdown();
    return 0;
}