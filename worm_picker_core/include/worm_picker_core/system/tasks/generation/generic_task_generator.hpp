// generic_task_generator.hpp
//
// Copyright (c)
// SPDX-License-Identifier: Apache-2.0

#ifndef GENERIC_TASK_GENERATOR_HPP
#define GENERIC_TASK_GENERATOR_HPP

#include "worm_picker_core/system/tasks/generation/base_task_generator.hpp"

template <typename DataType>
class GenericTaskGenerator : public BaseTaskGenerator {
public:
    explicit GenericTaskGenerator(const std::unordered_map<std::string, DataType>& data_map)
        : data_map_(data_map) {}

protected:
    StageSequence createStagesForTaskImpl(const std::string& name, char row_letter) const override 
    {
        auto it = data_map_.find(name);
        if (it != data_map_.end()) {
            return createStagesForTask(it->second, row_letter);
        }
        return {};
    }

    std::vector<std::string> getDataMapKeys() const override 
    {
        std::vector<std::string> keys;
        keys.reserve(data_map_.size());
        for (const auto& [key, _] : data_map_) {
            keys.push_back(key);
        }
        return keys;
    }

    virtual StageSequence createStagesForTask(const DataType& data, char row_letter) const = 0;

    const std::unordered_map<std::string, DataType>& data_map_;
};

#endif // GENERIC_TASK_GENERATOR_HPP
