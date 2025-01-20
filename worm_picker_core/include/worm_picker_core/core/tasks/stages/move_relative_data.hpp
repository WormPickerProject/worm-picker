// move_relative_data.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "worm_picker_core/core/tasks/stages/movement_data_base.hpp"

class MoveRelativeData : public MovementDataBase {
public:
    MoveRelativeData();
    MoveRelativeData(double dx, double dy, double dz,
                     double vel_scaling = 0.1, double acc_scaling = 0.1);

    std::unique_ptr<StageData> clone() const override;
    StageType getType() const override;
    double getDX() const;
    double getDY() const;
    double getDZ() const;

protected:
    StagePtr createStageInstanceImpl(const std::string& name, 
                                     std::shared_ptr<void> planner) const override;
    void configureStageImpl(Stage& stage, const NodePtr& node) const override;

private:
    double dx_{};
    double dy_{};
    double dz_{};
};