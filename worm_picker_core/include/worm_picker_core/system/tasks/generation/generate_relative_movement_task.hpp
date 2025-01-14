// generate_relative_movement_task.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_RELATIVE_MOVEMENT_TASK_HPP
#define GENERATE_RELATIVE_MOVEMENT_TASK_HPP

#include "worm_picker_core/core/tasks/task_data.hpp"

class GenerateRelativeMovementTask {
public:
    static TaskData parseCommand(const std::vector<std::string>& args);

private:
    using CoordinateTuple = std::tuple<double, double, double>;
    
    static CoordinateTuple extractCoordinates(const std::vector<std::string>& args);
    static double parseDouble(const std::string& value);
};

#endif // GENERATE_RELATIVE_MOVEMENT_TASK_HPP
