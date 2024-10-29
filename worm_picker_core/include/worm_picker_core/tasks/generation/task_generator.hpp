#ifndef TASK_GENERATOR_HPP
#define TASK_GENERATOR_HPP

#include "worm_picker_core/tasks/task_data_structure.hpp"

class TaskGenerator 
{
public:
    TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_data_map,
                  const std::unordered_map<std::string, HotelData>& hotel_data_map) {};
    virtual ~TaskGenerator() = default;

private:

};

#endif // TASK_GENERATOR_HPP
