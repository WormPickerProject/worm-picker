// base_task_generator.hpp

#ifndef BASE_TASK_GENERATOR_HPP
#define BASE_TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data.hpp"
#include "worm_picker_core/stages/move_relative_data.hpp"
#include "worm_picker_core/stages/move_to_joint_data.hpp"
#include "worm_picker_core/stages/move_to_point_data.hpp"

class BaseTaskGenerator 
{
public:
    virtual ~BaseTaskGenerator() = default;
    virtual void generateTasks() = 0;
    virtual const std::map<std::string, TaskData>& getTaskDataMap() const = 0;
};

#endif // BASE_TASK_GENERATOR_HPP