// plate_position_analyzer.cpp
#include "worm_picker_core/calibration/plate_position_analyzer.hpp"

PlatePositionAnalyzer::PlatePositionAnalyzer(const PoseMap& recorded_positions)
    : recorded_positions_(recorded_positions)
{
    initializeFixedPoints();
}

void PlatePositionAnalyzer::initializeFixedPoints() 
{
    fixed_points_ = {
        {"A1", 188.755, 229.505}, {"A2", 257.791, 313.445},
        {"B1", 263.494, 238.395}, {"B2", 344.086, 311.312},
        {"C1", 247.191, 164.916}, {"C2", 337.600, 225.234},
        {"C3", 428.009, 285.552}, {"D1", 321.297, 151.755},
        {"D2", 419.570, 198.171}, {"D3", 517.842, 244.587},
        {"E1", 284.389, 86.159},  {"E2", 117.672, 117.672},
        {"E3", 492.418, 149.184}, {"E4", 596.432, 180.697},
        {"F1", 351.496, 52.076},  {"F2", 459.005, 68.005},
        {"F3", 566.515, 83.933},  {"G1", 297.154, 0.000},
        {"G2", 405.837, 0.000},   {"G3", 514.520, 0.000},
        {"G4", 623.203, 0.000},   {"H1", 351.496, -52.076},
        {"H2", 459.005, -68.005}, {"H3", 566.515, -83.933},
        {"I1", 284.389, -86.159}, {"I2", 117.672, -117.672},
        {"I3", 492.418, -149.184},{"I4", 596.432, -180.697},
        {"J1", 321.297, -151.755},{"J2", 419.570, -198.171},
        {"J3", 517.842, -244.587},{"K1", 247.191, -164.916},
        {"K2", 337.600, -225.234},{"K3", 428.009, -285.552},
        {"L1", 263.494, -238.395},{"L2", 344.086, -311.312},
        {"M1", 188.755, -229.505},{"M2", 257.791, -313.445}
    };
}

PlatePositionAnalyzer::NormalizedPoseSet PlatePositionAnalyzer::normalizeAllPoints() const {
    NormalizedPoseSet result;

    for (const auto& [ref_name, recorded_pose] : recorded_positions_) {
        const auto fixed_ref = std::ranges::find_if(fixed_points_, 
            [&ref_name](const auto& point) { return point.name == ref_name; });

        const auto& ref_x = fixed_ref->x;
        const auto& ref_y = fixed_ref->y;
        const auto& recorded_x = recorded_pose.pose.position.x;
        const auto& recorded_y = recorded_pose.pose.position.y;

        auto& normalized_points = result[ref_name];
        for (const auto& point : fixed_points_) {
            auto normalized = recorded_pose; 
            auto& pos = normalized.pose.position;
            
            pos.x = (point.x - ref_x) * MM_TO_M + recorded_x;
            pos.y = (point.y - ref_y) * MM_TO_M + recorded_y;
            
            normalized_points[point.name] = normalized;
        }
    }

    return result;
}
