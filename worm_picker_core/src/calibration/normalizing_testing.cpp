#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct Point {
    std::string name;
    double x;
    double y;
};

std::vector<Point> normalizeToPointWithOffset(const std::vector<Point>& points,
                                              const std::string& referencePointName,
                                              double offsetX,
                                              double offsetY) 
{
    auto refPoint = std::find_if(points.begin(), points.end(),
        [&](const Point& p) { return p.name == referencePointName; });

    std::vector<Point> normalizedPoints;
    normalizedPoints.reserve(points.size());

    for (const auto& point : points) {
        normalizedPoints.push_back({
            point.name,
            point.x - refPoint->x + offsetX,
            point.y - refPoint->y + offsetY
        });
    }

    return normalizedPoints;
}

void printPoints(const std::vector<Point>& points) 
{
    std::cout << std::fixed; 
    std::cout.precision(3); 
    
    std::cout << "Point     X          Y     \n";
    std::cout << "---------------------------\n";
    
    for (const auto& point : points) {
        std::cout << std::left << std::setw(5) << point.name 
                  << std::right << std::setw(11) << point.x 
                  << std::setw(11) << point.y << '\n';
    }
}

int main() 
{
    const std::vector<Point> points = {
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

    const std::string referencePoint = "G3";
    const double recordedX = 596.523;
    const double recordedY = 0.004;

    auto normalizedPoints = normalizeToPointWithOffset(points, referencePoint, recordedX, recordedY);
    std::cout << "Normalized Points with Offset (relative to " << referencePoint << "):\n";
    printPoints(normalizedPoints);

    return 0;
}