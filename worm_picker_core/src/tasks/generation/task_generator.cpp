// task_generator.cpp

#include <rclcpp/rclcpp.hpp>
#include "worm_picker_core/tasks/generation/task_generator.hpp"

TaskGenerator::TaskGenerator(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                             const std::unordered_map<std::string, HotelData>& hotel_map)
{
    auto generators = initializeGenerators(workstation_map, hotel_map);
    generateAndAggregateTasks(generators);
}

const std::map<std::string, TaskData>& TaskGenerator::getGeneratedTaskPlans() const
{
    logDataMap();
    return task_data_map_;
}

std::vector<std::unique_ptr<BaseTaskGenerator>> TaskGenerator::initializeGenerators(const std::unordered_map<std::string, WorkstationData>& workstation_map,
                                                                                    const std::unordered_map<std::string, HotelData>& hotel_map) 
{
    std::vector<std::unique_ptr<BaseTaskGenerator>> generators;
    generators.emplace_back(std::make_unique<GenerateWorkstationPickPlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateWorkstationPlacePlateTask>(workstation_map));
    generators.emplace_back(std::make_unique<GenerateHotelPickPlateTask>(hotel_map));
    generators.emplace_back(std::make_unique<GenerateHotelPlacePlateTask>(hotel_map));
    return generators;
}

void TaskGenerator::generateAndAggregateTasks(const std::vector<std::unique_ptr<BaseTaskGenerator>>& generators) 
{
    for (const auto& generator : generators) {
        generator->generateTasks();
        const auto& generated_tasks = generator->getTaskDataMap();
        task_data_map_.insert(generated_tasks.begin(), generated_tasks.end());
    }
}

// Temporary Functions:
void TaskGenerator::logDataMap() const
{
    auto logger = rclcpp::get_logger("TaskGenerator");

    RCLCPP_INFO(logger, "\n");
    RCLCPP_INFO(logger, "********************************************************");
    RCLCPP_INFO(logger, "* Logging task_data_map_ contents:");

    for (const auto& task_entry : task_data_map_) {
        const std::string& task_name = task_entry.first;
        const TaskData& task_data = task_entry.second;

        RCLCPP_INFO(logger, "* Task Name: %s", task_name.c_str());

        int stage_number = 1;
        for (const auto& stage_ptr : task_data.getStages()) {
            StageType stage_type = stage_ptr->getType();
            std::string stage_type_str;

            switch (stage_type) {
                case StageType::MOVE_TO_POINT:
                    stage_type_str = "MOVE_TO_POINT";
                    break;
                case StageType::MOVE_TO_JOINT:
                    stage_type_str = "MOVE_TO_JOINT";
                    break;
                case StageType::MOVE_RELATIVE:
                    stage_type_str = "MOVE_RELATIVE";
                    break;
                default:
                    stage_type_str = "UNKNOWN";
                    break;
            }

            RCLCPP_INFO(logger, "*   Stage %d: Type: %s", stage_number, stage_type_str.c_str());

            if (stage_type == StageType::MOVE_TO_POINT) {
                auto move_to_point_data = std::dynamic_pointer_cast<MoveToPointData>(stage_ptr);
                if (move_to_point_data) {
                    RCLCPP_INFO(logger, "*     Position: (%f, %f, %f)", move_to_point_data->getX(), move_to_point_data->getY(), move_to_point_data->getZ());
                    RCLCPP_INFO(logger, "*     Orientation: (%f, %f, %f, %f)", move_to_point_data->getQX(), move_to_point_data->getQY(), move_to_point_data->getQZ(), move_to_point_data->getQW());
                    RCLCPP_INFO(logger, "*     Velocity Scaling: %f", move_to_point_data->getVelocityScalingFactor());
                    RCLCPP_INFO(logger, "*     Acceleration Scaling: %f", move_to_point_data->getAccelerationScalingFactor());
                }
            } else if (stage_type == StageType::MOVE_TO_JOINT) {
                auto move_to_joint_data = std::dynamic_pointer_cast<MoveToJointData>(stage_ptr);
                if (move_to_joint_data) {
                    RCLCPP_INFO(logger, "*     Joint Positions:");
                    for (const auto& joint_entry : move_to_joint_data->getJointPositions()) {
                        RCLCPP_INFO(logger, "*       %s: %f", joint_entry.first.c_str(), joint_entry.second);
                    }
                    RCLCPP_INFO(logger, "*     Velocity Scaling: %f", move_to_joint_data->getVelocityScalingFactor());
                    RCLCPP_INFO(logger, "*     Acceleration Scaling: %f", move_to_joint_data->getAccelerationScalingFactor());
                }
            } else if (stage_type == StageType::MOVE_RELATIVE) {
                auto move_relative_data = std::dynamic_pointer_cast<MoveRelativeData>(stage_ptr);
                if (move_relative_data) {
                    RCLCPP_INFO(logger, "*     Delta Position: (%f, %f, %f)", move_relative_data->getDX(), move_relative_data->getDY(), move_relative_data->getDZ());
                    RCLCPP_INFO(logger, "*     Velocity Scaling: %f", move_relative_data->getVelocityScalingFactor());
                    RCLCPP_INFO(logger, "*     Acceleration Scaling: %f", move_relative_data->getAccelerationScalingFactor());
                }
            }

            stage_number++;
        }
    }

    RCLCPP_INFO(logger, "********************************************************\n");
}