#pragma once

#include <string>
#include <vector>
#include <optional>
#include <utility>
#include "worm_picker_core/core/commands/command_info.hpp"
#include "worm_picker_core/core/commands/parser/command_parsers.hpp"

namespace worm_picker {
namespace parser {

class CommandInfoBuilder {
public:
    // Build a CommandInfo from parsing results
    static CommandInfo build(
        const std::string& baseCommand,
        const std::vector<std::string>& args,
        size_t baseArgAmount,
        const std::optional<SpeedOverride>& speedOverride);
};

}} // namespace worm_picker::parser