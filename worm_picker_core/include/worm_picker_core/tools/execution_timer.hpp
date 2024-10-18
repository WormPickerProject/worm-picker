// execution_timer.hpp
//
// Copyright (c) 2024 Logan Kaising
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

