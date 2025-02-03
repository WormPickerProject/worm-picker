// core_command_interface.cpp
//
// Copyright (c) 2025
// SPDX-License-Identifier: Apache-2.0

#include <random>
#include "worm_picker_core/infrastructure/interface/cli/core_command_interface.hpp"

namespace worm_picker {

namespace {
    constexpr const char* SERVICE_NAME = "/task_command";

    const std::vector<std::string> VALID_POINTS = {
        "A1", "A2", 
        "B1", "B2",
        "C1", "C2", "C3",
        "D1", "D2", "D3",
        "E1", "E2", "E3", "E4",
        "F1", "F2", "F3",
        "G1", "G2", "G3", "G4",
        "H1", "H2", "H3",
        "I1", "I2", "I3", "I4",
        "J1", "J2", "J3",
        "K1", "K2", "K3",
        "L1", "L2",
        "M1", "M2"
    };

    std::vector<std::string> splitCommand(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream iss(str);
        std::string token;
        while (std::getline(iss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
}

//------------------- PointIdentifier ----------------------------------

PointIdentifier::PointIdentifier(std::string value)
    : value_(std::move(value)) 
{
    if (!isValid(value_)) {
        throw std::invalid_argument("Invalid point identifier: " + value_);
    }
}

bool PointIdentifier::isValid(const std::string& value) 
{
    return std::find(VALID_POINTS.begin(), VALID_POINTS.end(), value) != VALID_POINTS.end();
}

//------------------- CoreCommandInterface::Implementation -----------------

class CoreCommandInterface::Implementation {
public:
    explicit Implementation(rclcpp::Node::SharedPtr node)
        : node_(std::move(node)), 
          points_(VALID_POINTS)
    {
        initializeClient();
    }

    void initializeClient();
    Result<void> sendCommand(const std::string& command);
    std::string formatCommand(const std::string& base_command) const; 
    bool parseVelAcc(const std::string& value, double& result) const;
    Result<void> sendCommandsInOrder(const std::vector<std::string>& commands);

    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<TaskCommand>::SharedPtr client_;
    std::vector<std::string> points_;
    std::optional<double> current_vel_;
    std::optional<double> current_acc_;
};

void CoreCommandInterface::Implementation::initializeClient() 
{
    client_ = node_->create_client<TaskCommand>(SERVICE_NAME);
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node_->get_logger(), "Interrupted while waiting. Shutting down...");
            rclcpp::shutdown();
            std::exit(EXIT_FAILURE);
        }
    }
}

Result<void> CoreCommandInterface::Implementation::sendCommand(const std::string& command)
{
    auto request = std::make_shared<TaskCommand::Request>();
    request->command = command;

    auto future = client_->async_send_request(request);
    const auto status = rclcpp::spin_until_future_complete(node_, future);
    
    if (status != rclcpp::FutureReturnCode::SUCCESS) {
        return Result<void>::error("Failed to call service: " + std::string(SERVICE_NAME));
    }

    auto response = future.get();
    if (!response->success) {
        return Result<void>::error("Task execution failed for command: " + command + 
                                   "\nFeedback: " + response->feedback);
    }
    
    // RCLCPP_INFO(node_->get_logger(), "Command feedback: %s", response->feedback.c_str());
    return Result<void>::success();
}

std::string CoreCommandInterface::Implementation::formatCommand(const std::string& base_cmd) const 
{
    if (!current_vel_ && !current_acc_) {
        return base_cmd;
    }
    
    std::string formatted = base_cmd;
    if (current_vel_) {
        formatted += ":" + std::to_string(*current_vel_);
    }
    if (current_acc_) {
        formatted += ":" + std::to_string(*current_acc_);
    }
    return formatted;
}

bool CoreCommandInterface::Implementation::parseVelAcc(const std::string& value, 
                                                       double& result) const 
{
    try {
        result = std::stod(value);
        return (result >= 0.0 && result <= 1.0);
    } catch (...) {
        return false;
    }
}

Result<void> CoreCommandInterface::Implementation::sendCommandsInOrder(
    const std::vector<std::string>& commands)
{
    for (const auto& cmd : commands) {
        auto result = sendCommand(formatCommand(cmd));
        if (!result.isSuccess()) {
            return result;
        }
    }
    return Result<void>::success();
}

//------------------- CoreCommandInterface -------------------------------

CoreCommandInterface::CoreCommandInterface(rclcpp::Node::SharedPtr node)
    : impl_(std::make_unique<Implementation>(std::move(node)))
{}

CoreCommandInterface::~CoreCommandInterface() = default;

void CoreCommandInterface::runCommandLoop()
{
    std::string command;
    while (rclcpp::ok()) {
        std::cout << "Enter command (or 'quit'/'q'): ";
        if (!std::getline(std::cin >> std::ws, command)) {
            break;
        }
        if (command == "quit" || command == "q") {
            break;
        }

        auto result = processUserCommand(command);
        if (!result.isSuccess()) {
            RCLCPP_ERROR(impl_->node_->get_logger(), "%s", result.error().c_str());
        }
    }
}

Result<void> CoreCommandInterface::processUserCommand(const std::string& full_command)
{
    impl_->current_vel_ = std::nullopt;
    impl_->current_acc_ = std::nullopt;

    std::vector<std::string> parts = splitCommand(full_command, ':');
    if (parts.empty()) {
        return Result<void>::error("Empty command received");
    }

    if (parts.size() >= 3) {
        double vel, acc;
        if (impl_->parseVelAcc(parts[parts.size() - 2], vel) &&
            impl_->parseVelAcc(parts[parts.size() - 1], acc)) {
            impl_->current_vel_ = vel;
            impl_->current_acc_ = acc;
            parts.resize(parts.size() - 2);
        }
    }

    static const std::unordered_map<std::string, 
        std::function<Result<void>(CoreCommandInterface*, const std::vector<std::string>&)>>
        dispatch {
        {"moveAllPoints", [](auto self, auto){ 
            return self->handleMoveAllPoints(); 
        }},
        {"moveAllPlates", [](auto self, auto){ 
            return self->handleMoveAllPlates(); 
        }},
        {"moveAllPlatesRandom", [](auto self, auto){ 
            return self->handleMoveAllPlatesRandom(); 
        }},
        {"moveRowPoints", [](auto self, auto parts){ 
            if (parts.size() < 2) return Result<void>::error("Row argument missing");
            return self->handleMoveRowPoints(parts[1]);
        }},
        {"moveRowPlates", [](auto self, auto parts){ 
            if (parts.size() < 2) return Result<void>::error("Row argument missing");
            return self->handleMoveRowPlates(parts[1]);
        }},
    };

    const std::string& base_command = parts[0];
    if (auto it = dispatch.find(base_command); it != dispatch.end()) {
        return it->second(this, parts);
    }
    return impl_->sendCommand(full_command);
}

//------------------- High-level movement handlers ----------------------

Result<void> CoreCommandInterface::handleMoveAllPoints()
{
    std::vector<PointIdentifier> points;
    points.reserve(impl_->points_.size());
    
    for (const auto& point : impl_->points_) {
        points.emplace_back(point);
    }

    return executeMovementSequence(points);
}

Result<void> CoreCommandInterface::handleMoveRowPoints(const std::string& row)
{
    if (!isValidRow(row)) {
        return Result<void>::error("Invalid row letter: " + row);
    }
    
    auto points = getRowPoints(static_cast<char>(std::toupper(row[0])));
    return executeMovementSequence(points);
}

Result<void> CoreCommandInterface::handleMoveAllPlates() 
{
    std::vector<std::string> initialMoves = {
        "pickPlateWorkStation:G1",
        "placePlateWorkStation:A1",
        "pickPlateWorkStation:A1",
        "placePlateWorkStation:B1",
        "pickPlateWorkStation:B1",
        "placePlateWorkStation:C1",
        "pickPlateWorkStation:C1"
    };

    auto result = impl_->sendCommandsInOrder(initialMoves);
    if (!result.isSuccess()) {
        return result;
    }

    static const std::vector<char> rows = {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    for (size_t i = 0; i < rows.size(); ++i) {
        auto row_points = getRowPoints(rows[i]);

        for (size_t j = 0; j + 1 < row_points.size(); ++j) {
            const auto& next_point = row_points[j + 1].value();
            result = impl_->sendCommandsInOrder({
                "placePlateWorkStation:" + next_point,
                "pickPlateWorkStation:" + next_point
            });
            if (!result.isSuccess()) return result;
        }

        if (i + 1 < rows.size()) {
            std::string next_row_first = std::string(1, rows[i + 1]) + "1";
            result = impl_->sendCommandsInOrder({
                "placePlateWorkStation:" + next_row_first,
                "pickPlateWorkStation:" + next_row_first
            });
            if (!result.isSuccess()) return result;
        } else {
            std::vector<std::string> finalMoves = {
                "placePlateWorkStation:L1",
                "pickPlateWorkStation:L1",
                "placePlateWorkStation:M1",
                "pickPlateWorkStation:M1",
                "placePlateWorkStation:G1"
            };

            result = impl_->sendCommandsInOrder(finalMoves);
            if (!result.isSuccess()) return result;
        }
    }

    return impl_->sendCommand(impl_->formatCommand("homeEndFactor"));
}

Result<void> CoreCommandInterface::handleMoveAllPlatesRandom()
{
    std::vector<PointIdentifier> available_points;
    available_points.reserve(impl_->points_.size());

    for (const auto& point : impl_->points_) {
        if (point != "A2" && point != "B2" && point != "L2" && point != "M2") {
            available_points.emplace_back(point);
        }
    }

    auto result = impl_->sendCommandsInOrder({"pickPlateWorkStation:G1"});
    if (!result.isSuccess()) return result;

    available_points.erase(
        std::remove_if(
            available_points.begin(),
            available_points.end(),
            [](const PointIdentifier& p){ return p.value() == "G1"; }
        ),
        available_points.end()
    );

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(available_points.begin(), available_points.end(), gen);

    const size_t total_points = available_points.size();
    size_t points_processed = 0;
    for (const auto& pointId : available_points) {
        points_processed++;
        RCLCPP_INFO(impl_->node_->get_logger(),
                    "Moving plate %zu/%zu - Position: %s",
                    points_processed, total_points, pointId.value().c_str());

        result = impl_->sendCommandsInOrder({
            "placePlateWorkStation:" + pointId.value(),
            "pickPlateWorkStation:" + pointId.value()
        });
        if (!result.isSuccess()) return result;
    }

    result = impl_->sendCommandsInOrder({"placePlateWorkStation:G1"});
    if (!result.isSuccess()) return result;

    return impl_->sendCommand(impl_->formatCommand("homeEndFactor"));
}

Result<void> CoreCommandInterface::handleMoveRowPlates(const std::string& row) 
{
    if (!isValidRow(row)) {
        return Result<void>::error("Invalid row letter: " + row);
    }

    const char row_char = static_cast<char>(std::toupper(row[0]));
    auto row_points = getRowPoints(row_char);
    
    if (row_points.empty()) {
        return Result<void>::error("No points found for row: " + row);
    }

    if (row_points.front().value() != "G1") {
        auto result = impl_->sendCommandsInOrder({
            "pickPlateWorkStation:G1",
            "placePlateWorkStation:" + row_points.front().value()
        });
        if (!result.isSuccess()) return result;
    }

    for (size_t i = 0; i + 1 < row_points.size(); ++i) {
        const auto& current_point = row_points[i].value();
        const auto& next_point = row_points[i + 1].value();

        auto result = impl_->sendCommandsInOrder({
            "pickPlateWorkStation:" + current_point,
            "placePlateWorkStation:" + next_point
        });
        if (!result.isSuccess()) return result;
    }

    auto result = impl_->sendCommandsInOrder({
        "pickPlateWorkStation:" + row_points.back().value(),
        "placePlateWorkStation:G1"
    });
    if (!result.isSuccess()) return result;

    return impl_->sendCommand(impl_->formatCommand("homeEndFactor"));
}

//------------------- Movement Sequence Helpers -------------------------

Result<void> CoreCommandInterface::executeMovementSequence(
    const std::vector<PointIdentifier>& points)
{
    for (const auto& point : points) {
        auto result = impl_->sendCommandsInOrder({"moveToPoint:" + point.value()});
        if (!result.isSuccess()) return result;
    }
    return impl_->sendCommand(impl_->formatCommand("homeEndFactor"));
}

bool CoreCommandInterface::isValidRow(const std::string& row) const 
{
    return (row.size() == 1 && std::isalpha(static_cast<unsigned char>(row[0])) &&
            toupper(row[0]) >= 'A' && toupper(row[0]) <= 'M');
}

std::vector<PointIdentifier> CoreCommandInterface::getRowPoints(char row) const 
{
    std::vector<PointIdentifier> result;
    for (const auto& point : impl_->points_) {
        if (!point.empty() && static_cast<char>(std::toupper(point.front())) == row) {
            result.emplace_back(point); 
        }
    }
    return result;
}

} // namespace worm_picker