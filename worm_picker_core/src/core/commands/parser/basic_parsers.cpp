#include "worm_picker_core/core/commands/parser/basic_parsers.hpp"

namespace worm_picker {
namespace parser {

Parser<std::string> token(char delimiter) {
    return [=](ParserInput input) -> Result<std::string, std::string> {
        if (input.atEnd()) {
            return Result<std::string>::error("Unexpected end of input, expected token");
        }
        
        size_t start = input.position;
        size_t end = input.text.find(delimiter, start);
        
        if (end == std::string::npos) {
            end = input.text.length();
        }
        
        std::string result(input.text.substr(start, end - start));
        return Result<std::string>::success(result);
    };
}

}} // namespace worm_picker::parser