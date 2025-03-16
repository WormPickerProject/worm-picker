// execution_timer.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <chrono>
#include <stdexcept>
#include <utility>

class ExecutionTimer {
public:
    ExecutionTimer(const std::string& name);

    double stop();

    const std::string& getName() const; 

private:
    std::string timer_name_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};