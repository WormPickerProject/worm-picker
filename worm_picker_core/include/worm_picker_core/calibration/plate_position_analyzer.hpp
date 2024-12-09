// plate_position_analyzer.hpp
#ifndef PLATE_POSITION_ANALYZER_HPP
#define PLATE_POSITION_ANALYZER_HPP

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <map>
#include <string>
#include <vector>

struct FixedPoint {
    std::string name;
    double x;
    double y;
};

struct WorkstationGeometry {
    double ray_separation_angle;
    std::vector<FixedPoint> fixed_points;
};

class PlatePositionAnalyzer {
public:
    using Pose = geometry_msgs::msg::PoseStamped;
    using PoseMap = std::map<std::string, Pose>;
    using NormalizedPoseSet = std::map<std::string, PoseMap>;

    explicit PlatePositionAnalyzer(const PoseMap& recorded_positions);
    NormalizedPoseSet normalizeAllPoints() const;

private:
    static constexpr double MM_TO_M = 0.001;
    
    void initializeFixedPoints();

    PoseMap recorded_positions_; 
    WorkstationGeometry workstation_geometry_;
    std::vector<FixedPoint> fixed_points_;
};

#endif // PLATE_POSITION_ANALYZER_HPP
