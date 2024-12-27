// generate_relative_movement_task.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/core/tasks/stages/move_relative_data.hpp"
#include "worm_picker_core/system/tasks/generation/generate_relative_movement_task.hpp"

TaskData GenerateRelativeMovementTask::parseCommand(const std::vector<std::string>& args) 
{
    auto [x, y, z] = extractCoordinates(args);
    return TaskData{
        std::vector<std::shared_ptr<StageData>>{
            std::make_shared<MoveRelativeData>(x, y, z)
        }
    };
}

GenerateRelativeMovementTask::CoordinateTuple
GenerateRelativeMovementTask::extractCoordinates(const std::vector<std::string>& args) 
{
    if (args.size() < 3) {
        throw std::invalid_argument("Insufficient coordinates for relative movement");
    }

    return {parseDouble(args[0]), parseDouble(args[1]), parseDouble(args[2])};
}

double GenerateRelativeMovementTask::parseDouble(const std::string& value) 
{
    try {
        return std::stod(std::string(value));
    } catch (const std::exception&) {
        throw std::invalid_argument(fmt::format("Invalid numeric value: {}", value));
    }
}
