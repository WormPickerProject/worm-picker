// execution_timer.cpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/tools/timing/execution_timer.hpp"

ExecutionTimer::ExecutionTimer(const std::string& name) 
    : timer_name_(name), start_time_(std::chrono::steady_clock::now())
{
}

double ExecutionTimer::stop() 
{
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time_;
    return elapsed.count();
}

const std::string& ExecutionTimer::getName() const
{
    return timer_name_;
}
