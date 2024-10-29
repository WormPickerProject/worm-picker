// generate_pick_plate_task.hpp

#ifndef GENERATE_PICK_PLATE_TASK_HPP
#define GENERATE_PICK_PLATE_TASK_HPP

#include "worm_picker_core/tasks/generation/task_generator.hpp"

class GeneratePickPlateTask : public TaskGenerator 
{
public:
    GeneratePickPlateTask() = default; 
    ~GeneratePickPlateTask() override = default; 
};

#endif // GENERATE_PICK_PLATE_TASK_HPP
