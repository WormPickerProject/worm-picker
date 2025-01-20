// generate_relative_movement_task.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_relative_movement_task.hpp"

Result<TaskData> GenerateRelativeMovementTask::parseCommand(const std::vector<std::string>& args) 
{
    auto createMovementData = [](const CoordinateTuple& values) -> std::shared_ptr<StageData> {
        auto [x, y, z] = values;
        return std::make_shared<MoveRelativeData>(x, y, z);
    };
    auto createTaskData = [](std::shared_ptr<StageData> movement_stage) -> TaskData {
        return TaskData{std::vector<std::shared_ptr<StageData>>{movement_stage}};
    };

    return extractCoordinates(args)
        .map(createMovementData)
        .map(createTaskData);
}

Result<GenerateRelativeMovementTask::CoordinateTuple>
GenerateRelativeMovementTask::extractCoordinates(const std::vector<std::string>& args) 
{
    if (args.size() < 3) {
        return Result<CoordinateTuple>::error("Insufficient coordinates for relative movement");
    }

    auto handleParseError = [](const std::string& value, const std::string& coordinateName) {
        auto msg = fmt::format("Failed to parse {} coordinate: {}", coordinateName, value);
        return Result<CoordinateTuple>::error(msg);
    };

    auto x_result = parseDouble(args[0]);
    if (!x_result) return handleParseError(args[0], "X");

    auto y_result = parseDouble(args[1]);
    if (!y_result) return handleParseError(args[1], "Y");

    auto z_result = parseDouble(args[2]);
    if (!z_result) return handleParseError(args[2], "Z");

    return Result<CoordinateTuple>::success(
        std::make_tuple(x_result.value(), y_result.value(), z_result.value())
    );
}

Result<double> GenerateRelativeMovementTask::parseDouble(const std::string& value) 
{
    try {
        return Result<double>::success(std::stod(std::string(value)));
    } catch (const std::exception&) {
        return Result<double>::error(fmt::format("Invalid numeric value: {}", value));
    }
}
