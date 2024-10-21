// exceptions.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class ActionServerUnavailableException : public std::runtime_error
{
public:
    explicit ActionServerUnavailableException(const std::string& message)
        : std::runtime_error(message) {}
};

class TaskPlanningFailedException : public std::runtime_error
{
public:
    explicit TaskPlanningFailedException(const std::string& message)
        : std::runtime_error(message) {}
};

class TaskExecutionFailedException : public std::runtime_error
{
public:
    explicit TaskExecutionFailedException(const std::string& message, int error_code)
        : std::runtime_error(message), error_code_(error_code) {}

    int getErrorCode() const { return error_code_; }

private:
    int error_code_;
};

#endif // EXCEPTIONS_HPP
