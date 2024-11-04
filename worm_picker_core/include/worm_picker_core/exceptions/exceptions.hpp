// exceptions.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

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

class NullNodeException : public std::runtime_error
{
public:
    explicit NullNodeException(const std::string& message)
        : std::runtime_error(message) {}
};

class TaskCommandNotFoundException : public std::out_of_range
{
public:
    explicit TaskCommandNotFoundException(const std::string& message)
        : std::out_of_range(message) {}
};

class UnknownStageTypeException : public std::invalid_argument
{
public:
    explicit UnknownStageTypeException(const std::string& message)
        : std::invalid_argument(message) {}
};

class StageCreationFailedException : public std::runtime_error
{
public:
    explicit StageCreationFailedException(const std::string& message)
        : std::runtime_error(message) {}
};

class StageNotFoundException : public std::invalid_argument
{
public:
    explicit StageNotFoundException(const std::string& message)
        : std::invalid_argument(message) {}
};

#endif // EXCEPTIONS_HPP
