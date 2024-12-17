// workstation_json_generator.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0

#ifndef WORKSTATION_JSON_GENERATOR_HPP
#define WORKSTATION_JSON_GENERATOR_HPP

#include <nlohmann/json.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <map>
#include <string>

class WorkstationJsonGenerator {
public:
    using PoseMap = std::map<std::string, geometry_msgs::msg::PoseStamped>;
    using OrderedJson = nlohmann::ordered_json;

    explicit WorkstationJsonGenerator(const PoseMap& averaged_poses);
    void generateJson(const std::string& output_path) const;

private:
    using PosePtrMap = std::map<std::string, const geometry_msgs::msg::PoseStamped*>;
    using GroupedPoseMap = std::map<char, PosePtrMap>;

    OrderedJson generateJsonData() const;
    void writeJsonToFile(const OrderedJson& json_data, const std::string& output_path) const;
    GroupedPoseMap groupPoses() const;

    const PoseMap& averaged_poses_;
};

#endif // WORKSTATION_JSON_GENERATOR_HPP