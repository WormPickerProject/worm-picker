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
    
    ParserInput(std::string_view text, size_t position = 0, size_t column = 1);
    
    bool atEnd() const;
    char current() const;
    ParserInput advance(size_t n = 1) const;
    std::string_view remainder() const;
    ParserInput skipTo(size_t new_position) const;
    std::string positionInfo() const;
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
Parser<char> satisfy(Pred predicate, const std::string& description);

// Match a specific character
Parser<char> character(char expected);

// Match a literal string
Parser<std::string> literal(const std::string& expected);

// Match a token until a delimiter or end
Parser<std::string> token(char delimiter = ':');

// Always succeed with a value without consuming input
template <typename T>
Parser<T> pure(T value);

// Always fail with a message
template <typename T>
Parser<T> fail(const std::string& message);

//=======================================
// Parser Combinators
//=======================================

// Run two parsers in sequence and combine their results
template <typename T, typename U, typename Combiner>
Parser<typename std::invoke_result<Combiner, T, U>::type> 
combine(Parser<T> first, Parser<U> second, Combiner combiner);

// Run two parsers in sequence and keep the second result
template <typename T, typename U>
Parser<U> right(Parser<T> first, Parser<U> second);

// Try the first parser, and if it fails, try the second parser
template <typename T>
Parser<T> orElse(Parser<T> first, Parser<T> second);

// Try multiple parsers in order until one succeeds
template <typename T>
Parser<T> choice(std::vector<Parser<T>> parsers);

// Apply a parser zero or more times
template <typename T>
Parser<std::vector<T>> many(Parser<T> parser);

// Apply a parser one or more times
template <typename T>
Parser<std::vector<T>> many1(Parser<T> parser);

// Delimiter-separated list of items
template <typename T, typename U>
Parser<std::vector<T>> sepBy(Parser<T> parser, Parser<U> separator);

} // namespace worm_picker::parser

// Include template implementations
#include "worm_picker_core/core/commands/parser/parser_core_impl.hpp"