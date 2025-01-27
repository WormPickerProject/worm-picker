// generate_relative_movement_task.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_relative_movement_task.hpp"

Result<TaskData> GenerateRelativeMovementTask::parseCommand(const std::vector<std::string>& args) 
{
    auto createMovementData = [](const CoordinateVector& all_coords) -> TaskData {
        std::vector<std::shared_ptr<StageData>> stages;
        stages.reserve(all_coords.size());

        for (const auto& coords : all_coords) {
            auto [x, y, z] = coords;
            stages.push_back(std::make_shared<MoveRelativeData>(x, y, z));
        }

        return TaskData{std::move(stages)};
    };

    return extractCoordinates(args)
        .map(createMovementData);
}

Result<GenerateRelativeMovementTask::CoordinateVector>
GenerateRelativeMovementTask::extractCoordinates(const std::vector<std::string>& args) 
{
    if (args.size() < 3) {
        return Result<CoordinateVector>::error("Insufficient coordinates for relative movement");
    }

    auto handleParseError = [](const std::string& value, const std::string& coordinateName) {
        auto msg = fmt::format("Failed to parse {} coordinate: {}", coordinateName, value);
        return Result<CoordinateVector>::error(msg);
    };
    
    std::vector<CoordinateTuple> coordinates;
    coordinates.reserve(args.size() / 3);

    for (std::size_t i = 0; i < args.size() / 3; ++i) {
        auto x_result = parseDouble(args[i * 3]);
        if (!x_result) return handleParseError(args[i * 3], "X");

        auto y_result = parseDouble(args[i * 3 + 1]);
        if (!y_result) return handleParseError(args[i * 3 + 1], "Y");

        auto z_result = parseDouble(args[i * 3 + 2]);
        if (!z_result) return handleParseError(args[i * 3 + 2], "Z");

        coordinates.emplace_back(x_result.value(), y_result.value(), z_result.value());
    }

    return Result<CoordinateVector>::success(std::move(coordinates));
}

Result<double> GenerateRelativeMovementTask::parseDouble(const std::string& value) 
{
    try {
        return Result<double>::success(std::stod(std::string(value)));
    } catch (const std::exception&) {
        return Result<double>::error(fmt::format("Invalid numeric value: {}", value));
    }
}
