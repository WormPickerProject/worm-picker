// parser_core.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include "worm_picker_core/core/commands/parser/parser_core.hpp"

namespace worm_picker { 
namespace parser {

//=======================================
// ParserInput Implementation
//=======================================

ParserInput::ParserInput(std::string_view text, size_t position, size_t column)
    : text(text), position(position), column(column) {}

bool ParserInput::atEnd() const { 
    return position >= text.length(); 
}

char ParserInput::current() const {
    return atEnd() ? '\0' : text[position];
}

ParserInput ParserInput::advance(size_t n) const {
    if (atEnd()) return *this;
    
    size_t newPosition = std::min(position + n, text.length());
    size_t newColumn = column;
    
    // Update column information
    for (size_t i = position; i < newPosition; ++i) {
        newColumn++;
    }
    
    return ParserInput{text, newPosition, newColumn};
}

std::string_view ParserInput::remainder() const {
    return atEnd() ? std::string_view{} : text.substr(position);
}

ParserInput ParserInput::skipTo(size_t new_position) const {
    if (new_position <= position) return *this;
    
    size_t newColumn = column;
    
    // Update column information
    newColumn += (new_position - position);
    
    return ParserInput{text, std::min(new_position, text.length()), newColumn};
}

std::string ParserInput::positionInfo() const {
    return "column " + std::to_string(column) + 
           " (position " + std::to_string(position) + ")";
}

//=======================================
// Non-template Parser Functions
//=======================================

Parser<char> character(char expected) {
    return satisfy([expected](char c) { return c == expected; }, 
                  std::string("'") + expected + "'");
}

Parser<std::string> literal(const std::string& expected) {
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

Parser<std::string> token(char delimiter) {
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

} // namespace parser
} // namespace worm_picker