// generic_task_generator.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/system/tasks/generation/base_task_generator.hpp"

template <typename DataType, typename ParsedNameType>
class GenericTaskGenerator : public BaseTaskGenerator {
public:
    explicit GenericTaskGenerator(const std::unordered_map<std::string, DataType>& data_map)
        : data_map_(data_map) {}

    void generateTasks() override {
        for (const auto& name : getDataMapKeys()) {
            auto parsed_name = parseName(name);
            std::string task_name = generateTaskName(parsed_name);
            auto stages = createStagesForTaskImpl(name, parsed_name);
            auto task_data = TaskData(std::move(stages));
            task_data_map_.emplace(std::move(task_name), std::move(task_data));
        }
    }

protected:
    using StageSequence = std::vector<std::shared_ptr<StageData>>;

    StageSequence createStagesForTaskImpl(const std::string& name, 
                                          const ParsedNameType& parsed_name) const {
        auto it = data_map_.find(name);
        if (it != data_map_.end()) {
            return createStagesForTask(it->second, parsed_name);
        }
        return {};
    }

    std::vector<std::string> getDataMapKeys() const {
        std::vector<std::string> keys;
        keys.reserve(data_map_.size());
        for (const auto& [key, _] : data_map_) {
            keys.push_back(key);
        }
        return keys;
    }

    virtual ParsedNameType parseName(const std::string& name) const = 0;
    virtual std::string generateTaskName(const ParsedNameType& parsed_name) const = 0;
    virtual StageSequence createStagesForTask(const DataType& data, 
                                              const ParsedNameType& parsed_name) const = 0;

    const std::unordered_map<std::string, DataType>& data_map_;
};