// generate_relative_movement_task.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/result.hpp"
#include "worm_picker_core/core/tasks/task_data.hpp"

class GenerateRelativeMovementTask {
public:
    static Result<TaskData> parseCommand(const std::vector<std::string>& args);

private:
    using CoordinateTuple = std::tuple<double, double, double>;
    
    static Result<CoordinateTuple> extractCoordinates(const std::vector<std::string>& args);
    static Result<double> parseDouble(const std::string& value);
};