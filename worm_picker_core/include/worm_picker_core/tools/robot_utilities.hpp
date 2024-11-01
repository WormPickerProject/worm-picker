// robot_utilities.hpp

#ifndef ROBOT_UTILITIES_HPP
#define ROBOT_UTILITIES_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"
#include <cmath>

// Robot at position check
bool isAtPosition(const StageData& current_position, const StageData& target_position, double tolerance = 0.001);

#endif // ROBOT_UTILITIES_HPP