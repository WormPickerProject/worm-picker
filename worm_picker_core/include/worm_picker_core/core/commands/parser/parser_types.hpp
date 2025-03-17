#pragma once

#include <string>
#include <string_view>
#include <functional>
#include <vector>
#include "worm_picker_core/core/result.hpp"

// namespace worm_picker {
// namespace parser {

// struct ParserInput {
//     std::string_view text;
//     size_t position;
    
//     ParserInput(std::string_view text, size_t position = 0)
//         : text(text), position(position) {}
    
//     bool atEnd() const { 
//         return position >= text.length(); 
//     }
    
//     char current() const {
//         return atEnd() ? '\0' : text[position];
//     }
    
//     ParserInput advance(size_t n = 1) const {
//         return ParserInput{text, std::min(position + n, text.length())};
//     }
    
//     std::string_view remainder() const {
//         return atEnd() ? std::string_view{} : text.substr(position);
//     }
    
//     ParserInput advanceTo(size_t newPosition) const {
//         return ParserInput{text, std::min(newPosition, text.length())};
//     }
// };

// template <typename T>
// using Parser = std::function<Result<T, std::string>(ParserInput)>;

// }} // namespace worm_picker::parser