// movement_data_base.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#ifndef MOVEMENT_DATA_BASE_HPP
#define MOVEMENT_DATA_BASE_HPP

#include "worm_picker_core/core/tasks/stage_data.hpp"

class MovementDataBase : public StageData {
public:
    virtual ~MovementDataBase() = default;
    MovementDataBase(double vel_scaling = 0.1, double acc_scaling = 0.1);

    StagePtr createStage(const std::string& name, const NodePtr& node) const final;
    virtual std::unique_ptr<StageData> clone() const override = 0;
    
    void setVelocityScalingFactor(double v);
    void setAccelerationScalingFactor(double a);
    double getVelocityScalingFactor() const;
    double getAccelerationScalingFactor() const;

protected:
    virtual StagePtr createStageInstanceImpl(const std::string& name, 
                                             std::shared_ptr<void> planner) const = 0;
    virtual void configureStageImpl(Stage& stage, const NodePtr& node) const = 0;
    void setCommonInfo(Stage& stage, const NodePtr& node) const;

private:
    std::shared_ptr<void> createPlannerImpl(const NodePtr& node, 
                                            double vel_scaling, 
                                            double acc_scaling) const;
    void setCommonExecutionInfo(Stage& stage) const;

    double velocity_scaling_;
    double acceleration_scaling_;
};

#endif // MOVEMENT_DATA_BASE_HPP