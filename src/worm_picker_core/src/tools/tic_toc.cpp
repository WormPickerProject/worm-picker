// tic_toc.cpp 
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

#include "worm_picker_core/tools/tic_toc.hpp"

TicToc::TicToc(const std::string& name) 
    : timer_name_(name), start_time_(std::chrono::steady_clock::now())
{
}

double TicToc::stop() 
{
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time_;
    return elapsed.count();
}

const std::string& TicToc::getName() const
{
    return timer_name_;
}