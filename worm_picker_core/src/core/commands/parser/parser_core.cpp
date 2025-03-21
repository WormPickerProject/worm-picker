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

ParserInput::ParserInput(std::string_view text, std::size_t position, std::size_t column)
    : text(text), position(position), column(column) {}

bool ParserInput::atEnd() const 
{ 
    return position >= text.length(); 
}

char ParserInput::current() const 
{
    return atEnd() ? '\0' : text[position];
}

ParserInput ParserInput::advance(std::size_t n) const 
{
    if (atEnd()) return *this;
    
    std::size_t newPosition = std::min(position + n, text.length());
    std::size_t newColumn = column + (newPosition - position);
    
    return ParserInput{text, newPosition, newColumn};
}

std::string_view ParserInput::remainder() const 
{
    return atEnd() ? std::string_view{} : text.substr(position);
}

ParserInput ParserInput::skipTo(std::size_t new_position) const 
{
    if (new_position <= position) return *this;
    return advance(new_position - position);
}

std::string ParserInput::positionInfo() const 
{
    std::ostringstream oss;
    oss << "column " << column << " (position " << position << ")";
    return oss.str();
}

//=======================================
// Non-template Parser Functions
//=======================================

Parser<char> character(char expected) 
{
    std::ostringstream oss;
    oss << "'" << expected << "'";
    return satisfy([expected](char c) { return c == expected; }, oss.str());
}

Parser<std::string> literal(const std::string& expected) 
{
    return [expected](ParserInput input) -> ParserResult<std::string> {
        if (input.remainder().size() < expected.size()) {
            std::ostringstream oss;
            oss << "At " << input.positionInfo() << ": Expected '" << expected 
                << "', but input is too short";
            return ParserResult<std::string>::error(oss.str());
        }
        
        std::string_view prefix = input.remainder().substr(0, expected.size());
        if (prefix != expected) {
            std::ostringstream oss;
            oss << "At " << input.positionInfo() << ": Expected '" << expected 
                << "', got '" << prefix << "'";
            return ParserResult<std::string>::error(oss.str());
        } 
        return ParserResult<std::string>::success({expected, input.advance(expected.size())});
    };
}

Parser<std::string> token(char delimiter) 
{
    return [delimiter](ParserInput input) -> ParserResult<std::string> {
        if (input.atEnd()) {
            std::ostringstream oss;
            oss << "At " << input.positionInfo() << ": Unexpected end of input, expected token";
            return ParserResult<std::string>::error(oss.str());
        }
        
        std::size_t start = input.position;
        std::size_t end = input.text.find(delimiter, start);
        
        if (end == std::string::npos) {
            end = input.text.length();
        }
        
        std::string result(input.text.substr(start, end - start));
        ParserInput newInput = input.skipTo(end);
        
        return ParserResult<std::string>::success({result, newInput});
    };
}

} // namespace parser
} // namespace worm_picker