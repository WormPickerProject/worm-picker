#include "worm_picker_core/core/commands/parser/command_info_builder.hpp"

namespace worm_picker {
namespace parser {

CommandInfo CommandInfoBuilder::build(
    const std::string& baseCommand,
    const std::vector<std::string>& args,
    size_t baseArgAmount,
    const std::optional<SpeedOverride>& speedOverride) {
    
    CommandInfo info;
    
    info.setBaseCommand(baseCommand);
    info.setArgs(args);
    info.setBaseArgsAmount(baseArgAmount);
    
    if (speedOverride) {
        info.setSpeedOverride(std::make_pair(speedOverride->velocity, speedOverride->acceleration));
    }
    
    return info;
}

}} // namespace worm_picker::parser