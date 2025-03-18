// parser_core_impl.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

// #pragma once

namespace worm_picker::parser {

//=======================================
// Template Parser Implementations
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

// Try the first parser, and if it fails, try the second parser
template <typename T>
Parser<T> orElse(Parser<T> first, Parser<T> second) {
    return [first, second](ParserInput input) -> ParserResult<T> {
        auto result = first(input);
        if (result.isSuccess()) {
            return result;
        }
        return second(input);
    };
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