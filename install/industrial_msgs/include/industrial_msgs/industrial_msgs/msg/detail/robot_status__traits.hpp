// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "industrial_msgs/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'mode'
#include "industrial_msgs/msg/detail/robot_mode__traits.hpp"
// Member 'e_stopped'
// Member 'drives_powered'
// Member 'motion_possible'
// Member 'in_motion'
// Member 'in_error'
#include "industrial_msgs/msg/detail/tri_state__traits.hpp"

namespace industrial_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    to_flow_style_yaml(msg.mode, out);
    out << ", ";
  }

  // member: e_stopped
  {
    out << "e_stopped: ";
    to_flow_style_yaml(msg.e_stopped, out);
    out << ", ";
  }

  // member: drives_powered
  {
    out << "drives_powered: ";
    to_flow_style_yaml(msg.drives_powered, out);
    out << ", ";
  }

  // member: motion_possible
  {
    out << "motion_possible: ";
    to_flow_style_yaml(msg.motion_possible, out);
    out << ", ";
  }

  // member: in_motion
  {
    out << "in_motion: ";
    to_flow_style_yaml(msg.in_motion, out);
    out << ", ";
  }

  // member: in_error
  {
    out << "in_error: ";
    to_flow_style_yaml(msg.in_error, out);
    out << ", ";
  }

  // member: error_codes
  {
    if (msg.error_codes.size() == 0) {
      out << "error_codes: []";
    } else {
      out << "error_codes: [";
      size_t pending_items = msg.error_codes.size();
      for (auto item : msg.error_codes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode:\n";
    to_block_style_yaml(msg.mode, out, indentation + 2);
  }

  // member: e_stopped
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "e_stopped:\n";
    to_block_style_yaml(msg.e_stopped, out, indentation + 2);
  }

  // member: drives_powered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "drives_powered:\n";
    to_block_style_yaml(msg.drives_powered, out, indentation + 2);
  }

  // member: motion_possible
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motion_possible:\n";
    to_block_style_yaml(msg.motion_possible, out, indentation + 2);
  }

  // member: in_motion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "in_motion:\n";
    to_block_style_yaml(msg.in_motion, out, indentation + 2);
  }

  // member: in_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "in_error:\n";
    to_block_style_yaml(msg.in_error, out, indentation + 2);
  }

  // member: error_codes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.error_codes.size() == 0) {
      out << "error_codes: []\n";
    } else {
      out << "error_codes:\n";
      for (auto item : msg.error_codes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace industrial_msgs

namespace rosidl_generator_traits
{

[[deprecated("use industrial_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const industrial_msgs::msg::RobotStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  industrial_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use industrial_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const industrial_msgs::msg::RobotStatus & msg)
{
  return industrial_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<industrial_msgs::msg::RobotStatus>()
{
  return "industrial_msgs::msg::RobotStatus";
}

template<>
inline const char * name<industrial_msgs::msg::RobotStatus>()
{
  return "industrial_msgs/msg/RobotStatus";
}

template<>
struct has_fixed_size<industrial_msgs::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<industrial_msgs::msg::RobotStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<industrial_msgs::msg::RobotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__TRAITS_HPP_
