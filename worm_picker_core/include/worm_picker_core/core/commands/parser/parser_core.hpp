// parser_core.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>
#include <functional>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <tuple>
#include <utility>
#include "worm_picker_core/core/result.hpp"

namespace worm_picker { 
namespace parser {

//=======================================
// Parser Types
//=======================================

// Parser input type (tracks current position in string with column info)
struct ParserInput {
    std::string_view text;
    std::size_t position;
    std::size_t column;
    
    ParserInput(std::string_view text, std::size_t position = 0, std::size_t column = 1);
    
    bool atEnd() const;
    char current() const;
    ParserInput advance(std::size_t n = 1) const;
    std::string_view remainder() const;
    ParserInput skipTo(std::size_t new_position) const;
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
Parser<char> satisfy(Pred&& predicate, const std::string& description);

// Match a specific character
Parser<char> character(char expected);

// Match a literal string
Parser<std::string> literal(const std::string& expected);

// Match a token until a delimiter or end
Parser<std::string> token(char delimiter = ':');

//=======================================
// Parser Combinators
//=======================================

// Run two parsers in sequence and combine their results
template <typename T, typename U, typename Combiner>
Parser<typename std::invoke_result<Combiner, T, U>::type> 
combine(Parser<T> first, Parser<U> second, Combiner combiner);

// Try the first parser, and if it fails, try the second parser
template <typename T>
Parser<T> orElse(Parser<T> first, Parser<T> second);

// Try multiple parsers in order until one succeeds
template <typename T>
Parser<T> choice(const std::vector<Parser<T>>& parsers);

// Delimiter-separated list of items
template <typename T, typename U>
Parser<std::vector<T>> sepBy(Parser<T> parser, Parser<U> separator);

} // namespace parser
} // namespace worm_picker

// Include template implementations
#include "worm_picker_core/core/commands/parser/parser_core_impl.hpp"