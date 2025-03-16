// result.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <concepts>
#include <variant>
#include <string>
#include <stdexcept>
#include <utility>
#include <type_traits>
#include <iostream>
#include <functional>

struct BadResultAccess : public std::logic_error {
    explicit BadResultAccess(const std::string& msg)
        : std::logic_error(msg) {}
};

inline void throwBadAccess(const char* msg) {
    throw BadResultAccess(msg);
}

template <typename T, typename E = std::string>
class Result {
public:
    struct Success { T value; };
    struct Error { E value; };

    static Result success(T value) {
        return Result(Success{std::move(value)});
    }

    static Result error(E error_value) {
        return Result(Error{std::move(error_value)});
    }

    bool isSuccess() const noexcept {
        return std::holds_alternative<Success>(value_);
    }

    explicit operator bool() const noexcept {
        return isSuccess();
    }

    const T& value() const & {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::get<Success>(value_).value;
    }

    T& value() & {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::get<Success>(value_).value;
    }

    T&& value() && {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::move(std::get<Success>(value_).value);
    }

    const E& error() const & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::get<Error>(value_).value;
    }

    E& error() & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::get<Error>(value_).value;
    }

    E&& error() && {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::move(std::get<Error>(value_).value);
    }

    template <typename Func>
    auto map(Func&& func) const 
        -> Result<std::invoke_result_t<Func, const T&>, E>
    {
        using U = std::invoke_result_t<Func, const T&>;
        if (isSuccess()) {
            if constexpr (std::is_void_v<U>) {
                std::invoke(std::forward<Func>(func), value());
                return Result<U, E>::success();
            } else {
                return Result<U, E>::success(std::invoke(std::forward<Func>(func), value()));
            }
        }
        return Result<U, E>::error(error());
    }

    template <typename Func>
    auto map(Func&& func)
        -> Result<std::invoke_result_t<Func, T&>, E>
    {
        using U = std::invoke_result_t<Func, T&>;
        if (isSuccess()) {
            if constexpr (std::is_void_v<U>) {
                std::invoke(std::forward<Func>(func), value());
                return Result<U, E>::success();
            } else {
                return Result<U, E>::success(std::invoke(std::forward<Func>(func), value()));
            }
        }
        return Result<U, E>::error(error());
    }

    template <typename Func>
    auto flatMap(Func&& func) const 
        -> std::invoke_result_t<Func, const T&>
    {
        using ResultType = std::invoke_result_t<Func, const T&>;
        static_assert(
            std::same_as<std::decay_t<ResultType>, 
            Result<typename ResultType::ValueType, typename ResultType::ErrorType>>,
            "flatMap must return a Result-compatible type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<Func>(func), value());
        }
        return ResultType::error(error());
    }

    template <typename Func>
    auto flatMap(Func&& func) 
        -> std::invoke_result_t<Func, T&>
    {
        using ResultType = std::invoke_result_t<Func, T&>;
        static_assert(
            std::same_as<std::decay_t<ResultType>, 
            Result<typename ResultType::ValueType, typename ResultType::ErrorType>>,
            "flatMap must return a Result-compatible type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<Func>(func), value());
        }
        return ResultType::error(error());
    }

    template <typename Func>
    auto mapError(Func&& func) const 
        -> Result<T, std::invoke_result_t<Func, const E&>>
    {
        using E2 = std::invoke_result_t<Func, const E&>;
        if (isSuccess()) {
            return Result<T, E2>::success(value());
        }
        return Result<T, E2>::error(std::invoke(std::forward<Func>(func), error()));
    }

    template <typename SuccessFunc, typename ErrorFunc>
    auto match(SuccessFunc&& on_success, ErrorFunc&& on_error) const
        -> std::invoke_result_t<SuccessFunc, const T&>
    {
        using ReturnType = std::invoke_result_t<SuccessFunc, const T&>;
        static_assert(
            std::same_as<ReturnType, std::invoke_result_t<ErrorFunc, const E&>>,
            "match callbacks must return the same type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<SuccessFunc>(on_success), value());
        }
        return std::invoke(std::forward<ErrorFunc>(on_error), error());
    }

    T valueOr(const T& default_value) const {
        if (isSuccess()) {
            return value();
        }
        return default_value;
    }

    template <typename Func>
    Result orElse(Func&& f) const {
        if (isSuccess()) {
            return *this;
        }
        return std::invoke(std::forward<Func>(f), error());
    }

    friend std::ostream& operator<<(std::ostream& os, const Result& r) {
        if (r.isSuccess()) {
            os << "Success(" << r.value() << ")";
        } else {
            os << "Error(" << r.error() << ")";
        }
        return os;
    }

    using ValueType = T;
    using ErrorType = E;

private:
    std::variant<Success, Error> value_;

    explicit Result(Success success) : value_(std::move(success)) {}
    explicit Result(Error error) : value_(std::move(error)) {}
};

template <typename E>
class Result<void, E> {
public:
    static Result success() {
        return Result(true);
    }

    static Result error(E error_value) {
        return Result(std::move(error_value));
    }

    bool isSuccess() const noexcept {
        return success_;
    }

    explicit operator bool() const noexcept {
        return isSuccess();
    }

    const E& error() const & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful void Result");
        }
        return error_value_;
    }

    E& error() & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful void Result");
        }
        return error_value_;
    }

    E&& error() && {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful void Result");
        }
        return std::move(error_value_);
    }

    template <typename Func>
    auto map(Func&& func)
        -> Result<std::invoke_result_t<Func>, E>
    {
        using U = std::invoke_result_t<Func>;
        if (isSuccess()) {
            if constexpr (std::is_void_v<U>) {
                std::invoke(std::forward<Func>(func));
                return Result<U, E>::success();
            } else {
                return Result<U, E>::success(std::invoke(std::forward<Func>(func)));
            }
        }
        return Result<U, E>::error(error_value_);
    }

    template <typename Func>
    auto map(Func&& func) const 
        -> Result<std::invoke_result_t<Func>, E>
    {
        using U = std::invoke_result_t<Func>;
        if (isSuccess()) {
            if constexpr (std::is_void_v<U>) {
                std::invoke(std::forward<Func>(func));
                return Result<U, E>::success();
            } else {
                return Result<U, E>::success(std::invoke(std::forward<Func>(func)));
            }
        }
        return Result<U, E>::error(error_value_);
    }

    template <typename Func>
    auto flatMap(Func&& func) const
        -> std::invoke_result_t<Func>
    {
        using ResultType = std::invoke_result_t<Func>;
        static_assert(
            std::same_as<std::decay_t<ResultType>,
            Result<typename ResultType::ValueType, typename ResultType::ErrorType>>,
            "flatMap must return a Result-compatible type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<Func>(func));
        }
        return ResultType::error(error_value_);
    }

    template <typename Func>
    auto flatMap(Func&& func)
        -> std::invoke_result_t<Func>
    {
        using ResultType = std::invoke_result_t<Func>;
        static_assert(
            std::same_as<std::decay_t<ResultType>,
            Result<typename ResultType::ValueType, typename ResultType::ErrorType>>,
            "flatMap must return a Result-compatible type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<Func>(func));
        }
        return ResultType::error(error_value_);
    }

    template <typename SuccessFunc, typename ErrorFunc>
    auto match(SuccessFunc&& on_success, ErrorFunc&& on_error) const
        -> std::invoke_result_t<SuccessFunc>
    {
        using ReturnType = std::invoke_result_t<SuccessFunc>;
        static_assert(
            std::same_as<ReturnType, std::invoke_result_t<ErrorFunc, const E&>>,
            "match callbacks must return the same type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<SuccessFunc>(on_success));
        }
        return std::invoke(std::forward<ErrorFunc>(on_error), error_value_);
    }

    template <typename Func>
    Result orElse(Func&& f) const {
        if (isSuccess()) {
            return *this;
        }
        return std::invoke(std::forward<Func>(f), error_value_);
    }

    friend std::ostream& operator<<(std::ostream& os, const Result& r) {
        if (r.isSuccess()) {
            os << "Success(void)";
        } else {
            os << "Error(" << r.error_value_ << ")";
        }
        return os;
    }

    using ValueType = void;
    using ErrorType = E;

private:
    bool success_ = false;
    E error_value_{};

    explicit Result(bool success) : success_(success) {}
    explicit Result(E error_value) : success_(false), error_value_(std::move(error_value)) {}
};