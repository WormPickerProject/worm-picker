// scoped_timer.hpp
// 
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>
#include "worm_picker_core/utils/execution_timer.hpp"

class ScopedTimer {
public:
    using TimerResults = std::vector<std::pair<std::string, double>>;
    explicit ScopedTimer(const std::string& name, TimerResults& results);
    ~ScopedTimer();

private:
    std::string name_;
    TimerResults& results_;
    ExecutionTimer timer_;
};