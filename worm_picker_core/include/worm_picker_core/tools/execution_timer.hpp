// execution_timer.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef EXECUTION_TIMER_HPP
#define EXECUTION_TIMER_HPP

#include <string>
#include <chrono>
#include <stdexcept>
#include <utility>

class ExecutionTimer
{
public:
    ExecutionTimer(const std::string& name);

    double stop();

    const std::string& getName() const; 

private:
    std::string timer_name_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};

#endif // EXECUTION_TIMER_HPP

