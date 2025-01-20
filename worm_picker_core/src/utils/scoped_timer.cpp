// scoped_timer.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/utils/scoped_timer.hpp"

ScopedTimer::ScopedTimer(const std::string& name, TimerResults& results)
    : name_(name), 
      results_(results), 
      timer_(name) 
{
}

ScopedTimer::~ScopedTimer() 
{
    results_.emplace_back(name_, timer_.stop());
}