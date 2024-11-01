// base_task_generator.hpp

#ifndef BASE_TASK_GENERATOR_HPP
#define BASE_TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"

class BaseTaskGenerator 
{
public:
    virtual ~BaseTaskGenerator() = default;
    virtual void generateTasks() = 0;
    virtual const std::map<std::string, TaskData>& getTaskDataMap() const = 0;
};

#endif // BASE_TASK_GENERATOR_HPP