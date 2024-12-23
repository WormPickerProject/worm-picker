// generate_relative_movement_task.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERATE_RELATIVE_MOVEMENT_TASK_HPP
#define GENERATE_RELATIVE_MOVEMENT_TASK_HPP

#include "worm_picker_core/core/tasks/task_data.hpp"

class GenerateRelativeMovementTask {
public:
    static TaskData parseCommand(std::string_view command);

private:
    using String = std::string_view;
    static constexpr String COMMAND_PREFIX = "moveRelative:";
    static std::tuple<double, double, double> extractCoordinates(String command);
    static double parseDouble(String value);
};

#endif // GENERATE_RELATIVE_MOVEMENT_TASK_HPP
