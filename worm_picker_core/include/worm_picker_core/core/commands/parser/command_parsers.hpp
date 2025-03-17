#pragma once

#include <string>
#include <vector>
#include <optional>
#include <utility>
#include "worm_picker_core/core/commands/parser/parser_types.hpp"
#include "worm_picker_core/core/commands/parser/basic_parsers.hpp"

namespace worm_picker {
namespace parser {

struct VariableArgResult {
    int multiplier;
    std::vector<std::string> remainingArgs;
};

struct SpeedOverride {
    double velocity;
    double acceleration;
};

// Parse base command (everything before first colon)
Parser<std::string> baseCommandParser();

// Parse colon-separated arguments
Parser<std::vector<std::string>> argumentsParser();

// Parse "N=X" variable argument pattern
Parser<VariableArgResult> variableArgParser();

// Parse optional speed override parameters
Parser<std::optional<SpeedOverride>> speedOverrideParser(size_t baseArgCount);

// Parse command with fixed number of arguments
Parser<std::pair<std::vector<std::string>, std::optional<SpeedOverride>>>
parseFixedCommand(const std::string& baseCommand, size_t baseArgCount);

// Parse command with variable number of arguments
Parser<std::pair<std::pair<std::vector<std::string>, size_t>, std::optional<SpeedOverride>>>
parseVariableCommand(const std::string& baseCommand, size_t baseArgPerGroup);

}} // namespace worm_picker::parser