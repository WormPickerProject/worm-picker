// parser_core.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <tuple>
#include <utility>
#include "worm_picker_core/core/result.hpp"

namespace worm_picker::parser {

//=======================================
// Parser Types
//=======================================

// Parser input type (tracks current position in string with column info)
struct ParserInput {
    std::string_view text;
    size_t position;
    size_t column;
    
    ParserInput(std::string_view text, size_t position = 0, size_t column = 1)
        : text(text), position(position), column(column) {}
    
    bool atEnd() const { return position >= text.length(); }
    
    char current() const {
        return atEnd() ? '\0' : text[position];
    }
    
    ParserInput advance(size_t n = 1) const {
        if (atEnd()) return *this;
        
        size_t newPosition = std::min(position + n, text.length());
        size_t newColumn = column;
        
        // Update column information
        for (size_t i = position; i < newPosition; ++i) {
            newColumn++;
        }
        
        return ParserInput{text, newPosition, newColumn};
    }
    
    std::string_view remainder() const {
        return atEnd() ? std::string_view{} : text.substr(position);
    }

    ParserInput skipTo(size_t new_position) const {
        if (new_position <= position) return *this;
        
        size_t newColumn = column;
        
        // Update column information
        newColumn += (new_position - position);
        
        return ParserInput{text, std::min(new_position, text.length()), newColumn};
    }
    
    std::string positionInfo() const {
        return "column " + std::to_string(column) + 
               " (position " + std::to_string(position) + ")";
    }
};

// Parser result type
template <typename T>
using ParserResult = Result<std::pair<T, ParserInput>, std::string>;

// Generic parser function type
template <typename T>
using Parser = std::function<ParserResult<T>(ParserInput)>;

//=======================================
// Basic Parsers
//=======================================

// Match a single character satisfying a predicate
template <typename Pred>
Parser<char> satisfy(Pred predicate, const std::string& description) {
    return [=](ParserInput input) -> ParserResult<char> {
        if (input.atEnd()) {
            return ParserResult<char>::error("At " + input.positionInfo() + 
                ": Unexpected end of input, expected " + description);
        }
        
        char c = input.current();
        if (predicate(c)) {
            return ParserResult<char>::success({c, input.advance()});
        } else {
            return ParserResult<char>::error(
                "At " + input.positionInfo() + ": Unexpected character '" + 
                std::string(1, c) + "', expected " + description);
        }
    };
}

// Match a specific character
inline Parser<char> character(char expected) {
    return satisfy([expected](char c) { return c == expected; }, 
                   std::string("'") + expected + "'");
}

// Match a literal string
inline Parser<std::string> literal(const std::string& expected) {
    return [=](ParserInput input) -> ParserResult<std::string> {
        if (input.remainder().size() < expected.size()) {
            return ParserResult<std::string>::error(
                "At " + input.positionInfo() + ": Expected '" + expected + 
                "', but input is too short");
        }
        
        std::string_view prefix = input.remainder().substr(0, expected.size());
        if (prefix == expected) {
            return ParserResult<std::string>::success(
                {std::string(expected), input.advance(expected.size())});
        } else {
            return ParserResult<std::string>::error(
                "At " + input.positionInfo() + ": Expected '" + expected + 
                "', got '" + std::string(prefix) + "'");
        }
    };
}

// Match a token until a delimiter or end
inline Parser<std::string> token(char delimiter = ':') {
    return [=](ParserInput input) -> ParserResult<std::string> {
        size_t start = input.position;
        size_t end = input.text.find(delimiter, start);
        
        if (end == std::string::npos) {
            end = input.text.length();
        }
        
        std::string result(input.text.substr(start, end - start));
        ParserInput newInput = input.skipTo(end);
        
        if (result.empty() && start == input.text.length()) {
            return ParserResult<std::string>::error(
                "At " + input.positionInfo() + ": Unexpected end of input, expected token");
        }
        
        return ParserResult<std::string>::success({result, newInput});
    };
}

// Always succeed with a value without consuming input
template <typename T>
Parser<T> pure(T value) {
    return [=](ParserInput input) -> ParserResult<T> {
        return ParserResult<T>::success({value, input});
    };
}

// Always fail with a message
template <typename T>
Parser<T> fail(const std::string& message) {
    return [=](ParserInput input) -> ParserResult<T> {
        return ParserResult<T>::error("At " + input.positionInfo() + ": " + message);
    };
}

//=======================================
// Parser Combinators
//=======================================

// Run two parsers in sequence and combine their results
template <typename T, typename U, typename Combiner>
Parser<typename std::invoke_result<Combiner, T, U>::type> 
combine(Parser<T> first, Parser<U> second, Combiner combiner) {
    using R = typename std::invoke_result<Combiner, T, U>::type;
    
    return [=](ParserInput input) -> ParserResult<R> {
        auto firstResult = first(input);
        if (!firstResult.isSuccess()) {
            return ParserResult<R>::error(firstResult.error());
        }
        
        auto [firstValue, firstRest] = firstResult.value();
        
        auto secondResult = second(firstRest);
        if (!secondResult.isSuccess()) {
            return ParserResult<R>::error(secondResult.error());
        }
        
        auto [secondValue, secondRest] = secondResult.value();
        
        return ParserResult<R>::success({
            combiner(firstValue, secondValue), 
            secondRest
        });
    };
}

// Run two parsers in sequence and keep the second result
template <typename T, typename U>
Parser<U> right(Parser<T> first, Parser<U> second) {
    return combine(first, second, [](T, U b) { return b; });
}

// Try multiple parsers in order until one succeeds
template <typename T>
Parser<T> choice(std::vector<Parser<T>> parsers) {
    return [=](ParserInput input) -> ParserResult<T> {
        std::vector<std::string> errors;
        
        for (const auto& parser : parsers) {
            auto result = parser(input);
            if (result.isSuccess()) {
                return result;
            }
            errors.push_back(result.error());
        }
        
        return ParserResult<T>::error("At " + input.positionInfo() + 
            ": None of the parsers succeeded: " + 
            [&errors]() {
                std::string combined;
                for (size_t i = 0; i < errors.size(); ++i) {
                    if (i > 0) combined += ", ";
                    combined += errors[i];
                }
                return combined;
            }());
    };
}

// Apply a parser zero or more times
template <typename T>
Parser<std::vector<T>> many(Parser<T> parser) {
    return [=](ParserInput input) -> ParserResult<std::vector<T>> {
        std::vector<T> results;
        ParserInput currentInput = input;
        
        while (true) {
            auto result = parser(currentInput);
            if (!result.isSuccess()) {
                break;
            }
            
            auto [value, nextInput] = result.value();
            results.push_back(value);
            
            // Ensure we're making progress
            if (nextInput.position == currentInput.position) {
                break;
            }
            
            currentInput = nextInput;
        }
        
        return ParserResult<std::vector<T>>::success({results, currentInput});
    };
}

// Apply a parser one or more times
template <typename T>
Parser<std::vector<T>> many1(Parser<T> parser) {
    return [=](ParserInput input) -> ParserResult<std::vector<T>> {
        auto result = many(parser)(input);
        if (!result.isSuccess()) {
            return result;
        }
        
        auto [values, nextInput] = result.value();
        if (values.empty()) {
            return ParserResult<std::vector<T>>::error(
                "At " + input.positionInfo() + ": Expected at least one match");
        }
        
        return ParserResult<std::vector<T>>::success({values, nextInput});
    };
}

// Delimiter-separated list of items
template <typename T, typename U>
Parser<std::vector<T>> sepBy(Parser<T> parser, Parser<U> separator) {
    return [=](ParserInput input) -> ParserResult<std::vector<T>> {
        std::vector<T> results;
        
        // Try to parse the first item
        auto firstResult = parser(input);
        if (!firstResult.isSuccess()) {
            // Empty list is OK
            return ParserResult<std::vector<T>>::success({results, input});
        }
        
        auto [firstValue, rest] = firstResult.value();
        results.push_back(firstValue);
        ParserInput currentInput = rest;
        
        while (true) {
            // Try to parse a separator followed by an item
            auto sepResult = separator(currentInput);
            if (!sepResult.isSuccess()) {
                break;
            }
            
            auto [_, afterSep] = sepResult.value();
            
            auto itemResult = parser(afterSep);
            if (!itemResult.isSuccess()) {
                break;
            }
            
            auto [itemValue, afterItem] = itemResult.value();
            results.push_back(itemValue);
            currentInput = afterItem;
        }
        
        return ParserResult<std::vector<T>>::success({results, currentInput});
    };
}

} // namespace worm_picker::parser