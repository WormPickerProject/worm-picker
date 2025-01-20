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
    static Result success(T value) {
        return Result(std::move(value));
    }

    static Result error(E errorValue) {
        return Result(std::move(errorValue));
    }

    bool isSuccess() const noexcept {
        return std::holds_alternative<T>(value_);
    }

    explicit operator bool() const noexcept {
        return isSuccess();
    }

    const T& value() const & {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::get<T>(value_);
    }

    T& value() & {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::get<T>(value_);
    }

    T&& value() && {
        if (!isSuccess()) {
            throwBadAccess("Attempted to access value of a failed Result");
        }
        return std::move(std::get<T>(value_));
    }

    const E& error() const & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::get<E>(value_);
    }

    E& error() & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::get<E>(value_);
    }

    E&& error() && {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful Result");
        }
        return std::move(std::get<E>(value_));
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
        return Result<U, E>::error(std::get<E>(value_));
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
        return Result<U, E>::error(std::get<E>(value_));
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
        return ResultType::error(std::get<E>(value_));
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
        return ResultType::error(std::get<E>(value_));
    }

    template <typename Func>
    auto mapError(Func&& func) const 
        -> Result<T, std::invoke_result_t<Func, const E&>>
    {
        using E2 = std::invoke_result_t<Func, const E&>;
        if (isSuccess()) {
            return Result<T, E2>::success(std::get<T>(value_));
        }
        return Result<T, E2>::error(std::invoke(std::forward<Func>(func), std::get<E>(value_)));
    }

    template <typename SuccessFunc, typename ErrorFunc>
    auto match(SuccessFunc&& onSuccess, ErrorFunc&& onError) const
        -> std::invoke_result_t<SuccessFunc, const T&>
    {
        using ReturnType = std::invoke_result_t<SuccessFunc, const T&>;
        static_assert(
            std::same_as<ReturnType, std::invoke_result_t<ErrorFunc, const E&>>,
            "match callbacks must return the same type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<SuccessFunc>(onSuccess), value());
        }
        return std::invoke(std::forward<ErrorFunc>(onError), std::get<E>(value_));
    }

    T valueOr(const T& defaultValue) const {
        if (isSuccess()) {
            return std::get<T>(value_);
        }
        return defaultValue;
    }

    template <typename Func>
    Result orElse(Func&& f) const {
        if (isSuccess()) {
            return *this;
        }
        return std::invoke(std::forward<Func>(f), std::get<E>(value_));
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
    std::variant<T, E> value_;

    explicit Result(T value) : value_(std::move(value)) {}
    explicit Result(E errorValue) : value_(std::move(errorValue)) {}
};

template <typename E>
class Result<void, E> {
public:
    static Result success() {
        return Result(true);
    }

    static Result error(E errorValue) {
        return Result(std::move(errorValue));
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
        return errorValue_;
    }

    E& error() & {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful void Result");
        }
        return errorValue_;
    }

    E&& error() && {
        if (isSuccess()) {
            throwBadAccess("Attempted to access error of a successful void Result");
        }
        return std::move(errorValue_);
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
        return Result<U, E>::error(errorValue_);
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
        return Result<U, E>::error(errorValue_);
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
        return ResultType::error(errorValue_);
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
        return ResultType::error(errorValue_);
    }

    template <typename SuccessFunc, typename ErrorFunc>
    auto match(SuccessFunc&& onSuccess, ErrorFunc&& onError) const
        -> std::invoke_result_t<SuccessFunc>
    {
        using ReturnType = std::invoke_result_t<SuccessFunc>;
        static_assert(
            std::same_as<ReturnType, std::invoke_result_t<ErrorFunc, const E&>>,
            "match callbacks must return the same type"
        );

        if (isSuccess()) {
            return std::invoke(std::forward<SuccessFunc>(onSuccess));
        }
        return std::invoke(std::forward<ErrorFunc>(onError), errorValue_);
    }

    template <typename Func>
    Result orElse(Func&& f) const {
        if (isSuccess()) {
            return *this;
        }
        return std::invoke(std::forward<Func>(f), errorValue_);
    }

    friend std::ostream& operator<<(std::ostream& os, const Result& r) {
        if (r.isSuccess()) {
            os << "Success(void)";
        } else {
            os << "Error(" << r.errorValue_ << ")";
        }
        return os;
    }

    using ValueType = void;
    using ErrorType = E;

private:
    bool success_ = false;
    E errorValue_{};

    explicit Result(bool success) : success_(success) {}
    explicit Result(E errorValue) : success_(false), errorValue_(std::move(errorValue)) {}
};