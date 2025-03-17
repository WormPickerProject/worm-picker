#pragma once

#include <string>
#include "worm_picker_core/core/commands/parser/parser_types.hpp"

namespace worm_picker {
namespace parser {

// Parse token until delimiter
Parser<std::string> token(char delimiter = ':');

}} // namespace worm_picker::parser