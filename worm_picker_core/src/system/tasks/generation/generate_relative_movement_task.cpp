// generate_relative_movement_task.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include <fmt/format.h>
#include "worm_picker_core/system/tasks/generation/generate_relative_movement_task.hpp"

TaskData GenerateRelativeMovementTask::parseCommand(std::string_view command) 
{
    auto [x, y, z] = extractCoordinates(command);
    
    return TaskData{
        std::vector<std::shared_ptr<StageData>>{
            std::make_shared<MoveRelativeData>(x, y, z)
        }
    };
}

std::tuple<double, double, double> GenerateRelativeMovementTask::extractCoordinates(String command) 
{
    command.remove_prefix(COMMAND_PREFIX.length());
    
    auto getValue = [&command](size_t pos) -> std::pair<String, size_t> {
        const size_t next = command.find(':', pos);
        size_t next_pos = next + 1;
        
        if (next == String::npos) {
            next_pos = command.length();
        }
        
        return {command.substr(pos, next - pos), next_pos};
    };
    
    auto [x_val, pos1] = getValue(0);
    auto [y_val, pos2] = getValue(pos1);
    auto [z_val, _] = getValue(pos2);
    
    return {parseDouble(x_val), parseDouble(y_val), parseDouble(z_val)};
}

double GenerateRelativeMovementTask::parseDouble(String value) 
{
    try {
        return std::stod(std::string(value));
    } catch (const std::exception&) {
        throw std::invalid_argument(fmt::format("Invalid numeric value: {}", value));
    }
}
