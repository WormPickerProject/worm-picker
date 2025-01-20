// move_to_joint_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

class MoveToJointData : public MovementDataBase {
public:
    MoveToJointData();
    MoveToJointData(double joint_1, double joint_2, double joint_3,
                    double joint_4, double joint_5, double joint_6,
                    double vel_scaling = 0.1, double acc_scaling = 0.1);
    MoveToJointData(const std::map<std::string, double>& joint_targets,
                    double vel_scaling = 0.1, double acc_scaling = 0.1);
    
    std::unique_ptr<StageData> clone() const override;
    StageType getType() const override;
    const std::map<std::string, double>& getJointPositions() const;

protected:
    StagePtr createStageInstanceImpl(const std::string& name, 
                                    std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    static constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;
    std::map<std::string, double> joint_positions_{};
};