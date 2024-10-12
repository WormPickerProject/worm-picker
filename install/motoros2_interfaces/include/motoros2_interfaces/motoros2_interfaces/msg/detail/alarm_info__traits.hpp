// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__TRAITS_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/msg/detail/alarm_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'datetime'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'help'
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__traits.hpp"

namespace motoros2_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AlarmInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: number
  {
    out << "number: ";
    rosidl_generator_traits::value_to_yaml(msg.number, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: sub_code
  {
    out << "sub_code: ";
    rosidl_generator_traits::value_to_yaml(msg.sub_code, out);
    out << ", ";
  }

  // member: datetime
  {
    out << "datetime: ";
    to_flow_style_yaml(msg.datetime, out);
    out << ", ";
  }

  // member: contents
  {
    out << "contents: ";
    rosidl_generator_traits::value_to_yaml(msg.contents, out);
    out << ", ";
  }

  // member: description
  {
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << ", ";
  }

  // member: help
  {
    if (msg.help.size() == 0) {
      out << "help: []";
    } else {
      out << "help: [";
      size_t pending_items = msg.help.size();
      for (auto item : msg.help) {
        to_flow_style_yaml(item, out);
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
  const AlarmInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "number: ";
    rosidl_generator_traits::value_to_yaml(msg.number, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: sub_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sub_code: ";
    rosidl_generator_traits::value_to_yaml(msg.sub_code, out);
    out << "\n";
  }

  // member: datetime
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "datetime:\n";
    to_block_style_yaml(msg.datetime, out, indentation + 2);
  }

  // member: contents
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contents: ";
    rosidl_generator_traits::value_to_yaml(msg.contents, out);
    out << "\n";
  }

  // member: description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << "\n";
  }

  // member: help
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.help.size() == 0) {
      out << "help: []\n";
    } else {
      out << "help:\n";
      for (auto item : msg.help) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AlarmInfo & msg, bool use_flow_style = false)
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

}  // namespace motoros2_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use motoros2_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motoros2_interfaces::msg::AlarmInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::msg::AlarmInfo & msg)
{
  return motoros2_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::msg::AlarmInfo>()
{
  return "motoros2_interfaces::msg::AlarmInfo";
}

template<>
inline const char * name<motoros2_interfaces::msg::AlarmInfo>()
{
  return "motoros2_interfaces/msg/AlarmInfo";
}

template<>
struct has_fixed_size<motoros2_interfaces::msg::AlarmInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motoros2_interfaces::msg::AlarmInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motoros2_interfaces::msg::AlarmInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__TRAITS_HPP_
