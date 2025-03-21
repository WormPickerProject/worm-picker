// parser_core.hpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>
#include "worm_picker_core/core/result.hpp"

namespace worm_picker { 
namespace parser {

//=======================================
// Parser Types
//=======================================

/**
 * @brief Parser input type that tracks current position in string with column info
 */
struct ParserInput {
    std::string_view text;
    std::size_t position;
    std::size_t column;
    
    /**
     * @brief Construct a new parser input object
     * @param text The input text to parse
     * @param position Current position in the text
     * @param column Current column number (for error reporting)
     */
    ParserInput(std::string_view text, std::size_t position = 0, std::size_t column = 1);
    
    /**
     * @brief Check if the parser has reached the end of input
     * @return true if at end of input, false otherwise
     */
    bool atEnd() const;
    
    /**
     * @brief Get the current character
     * @return The current character, or '\0' if at end
     */
    char current() const;
    
    /**
     * @brief Create a new input advanced by n characters
     * @param n Number of characters to advance
     * @return A new ParserInput advanced by n characters
     */
    ParserInput advance(std::size_t n = 1) const;
    
    /**
     * @brief Get the remaining text from the current position
     * @return String view of the remaining text
     */
    std::string_view remainder() const;
    
    /**
     * @brief Create a new input skipped to a specific position
     * @param new_position The position to skip to
     * @return A new ParserInput at the specified position
     */
    ParserInput skipTo(std::size_t new_position) const;
    
    /**
     * @brief Get a string describing the current position
     * @return Position information string
     */
    std::string positionInfo() const;
};

/**
 * @brief Parser result type that contains either a success value or an error
 * @tparam T The type of value on success
 */
template <typename T>
using ParserResult = Result<std::pair<T, ParserInput>, std::string>;

/**
 * @brief Generic parser function type
 * @tparam T The type of value the parser produces
 */
template <typename T>
using Parser = std::function<ParserResult<T>(ParserInput)>;

//=======================================
// Basic Parsers
//=======================================

/**
 * @brief Match a single character satisfying a predicate
 * @tparam Pred Predicate function type
 * @param predicate Function that determines if a character matches
 * @param description Description of the expected character (for error messages)
 * @return Parser that extracts a matching character
 */
template <typename Pred>
Parser<char> satisfy(Pred&& predicate, const std::string& description);

/**
 * @brief Match a specific character
 * @param expected The expected character
 * @return Parser that extracts the expected character
 */
Parser<char> character(char expected);

/**
 * @brief Match a literal string
 * @param expected The expected string
 * @return Parser that extracts the expected string
 */
Parser<std::string> literal(const std::string& expected);

/**
 * @brief Match a token until a delimiter or end
 * @param delimiter The delimiter character
 * @return Parser that extracts a token
 */
Parser<std::string> token(char delimiter = ':');

//=======================================
// Parser Combinators
//=======================================

/**
 * @brief Run two parsers in sequence and combine their results
 * @tparam T Type of the first parser's result
 * @tparam U Type of the second parser's result
 * @tparam Combiner Type of the combiner function
 * @param first The first parser to run
 * @param second The second parser to run
 * @param combiner Function to combine the results
 * @return Parser that runs both parsers and combines their results
 */
template <typename T, typename U, typename Combiner>
Parser<typename std::invoke_result<Combiner, T, U>::type> 
combine(Parser<T> first, Parser<U> second, Combiner combiner);

/**
 * @brief Try the first parser, and if it fails, try the second parser
 * @tparam T The type of value both parsers produce
 * @param first The first parser to try
 * @param second The fallback parser
 * @return Parser that tries both options
 */
template <typename T>
Parser<T> orElse(Parser<T> first, Parser<T> second);

/**
 * @brief Try multiple parsers in order until one succeeds
 * @tparam T The type of value all parsers produce
 * @param parsers Vector of parsers to try
 * @return Parser that tries all options
 */
template <typename T>
Parser<T> choice(const std::vector<Parser<T>>& parsers);

/**
 * @brief Parse a delimiter-separated list of items
 * @tparam T The type of value the item parser produces
 * @tparam U The type of value the separator parser produces
 * @param parser The parser for individual items
 * @param separator The parser for the separator
 * @return Parser that extracts a vector of items
 */
template <typename T, typename U>
Parser<std::vector<T>> sepBy(Parser<T> parser, Parser<U> separator);

} // namespace parser
} // namespace worm_picker

#include "worm_picker_core/core/commands/parser/parser_core_impl.hpp"