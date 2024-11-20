#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stage.h>
#include <moveit/task_constructor/properties.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <string>
#include <vector>

namespace task_output {

class TaskAnalyzer {
public:
    explicit TaskAnalyzer(const std::shared_ptr<rclcpp::Node>& node)
        : node_(node),
          logger_(node->get_logger()) {}

    void analyzeTask(const moveit::task_constructor::Task& task) {
        RCLCPP_INFO(logger_, "Analyzing Task");
        
        // Get solution if available
        if (!task.solutions().empty()) {
            const auto& solution = task.solutions().front();
            if (solution) {
                analyzeSolution(*solution);
            }
        }
        
        // Analyze all stages starting from the root container
        if (const auto* container = task.stages()) {
            analyzeContainer(container, 0);
        }
    }

private:
    std::shared_ptr<rclcpp::Node> node_;
    rclcpp::Logger logger_;

    void analyzeSolution(const moveit::task_constructor::SolutionBase& solution) {
        RCLCPP_INFO(logger_, "Solution cost: %.3f", solution.cost());
        RCLCPP_INFO(logger_, "Solution comment: %s", solution.comment().c_str());
    }

    void analyzeContainer(const moveit::task_constructor::ContainerBase* container, int depth) {
        if (!container) return;

        std::string indent(depth * 2, ' ');
        
        // Log container information
        RCLCPP_INFO(logger_, "%sContainer Stage: %s", 
                    indent.c_str(), 
                    container->name().c_str());

        // Log properties
        for (const auto& [key, value] : container->properties()) {
            RCLCPP_INFO(logger_, "%s  Property %s: %s",
                       indent.c_str(),
                       key.c_str(),
                       value.serialize().c_str());
        }

        // Iterate through child stages
        for (size_t i = 0; i < container->numChildren(); ++i) {
            const auto* stage = (*container)[i];
            if (const auto* child_container = dynamic_cast<const moveit::task_constructor::ContainerBase*>(stage)) {
                analyzeContainer(child_container, depth + 1);
            } else {
                analyzeStage(*stage, depth + 1);
            }
        }
    }

    void analyzeStage(const moveit::task_constructor::Stage& stage, int depth) {
        std::string indent(depth * 2, ' ');
        
        // Log stage information
        RCLCPP_INFO(logger_, "%sStage: %s", 
                    indent.c_str(),
                    stage.name().c_str());

        // Log properties
        for (const auto& [key, value] : stage.properties()) {
            RCLCPP_INFO(logger_, "%s  Property %s: %s",
                       indent.c_str(),
                       key.c_str(),
                       value.serialize().c_str());
        }
    }
};

// Helper function to create and use the analyzer
inline void outputTaskDetails(const moveit::task_constructor::Task& task,
                            const std::shared_ptr<rclcpp::Node>& node) {
    TaskAnalyzer analyzer(node);
    analyzer.analyzeTask(task);
}

} // namespace task_output