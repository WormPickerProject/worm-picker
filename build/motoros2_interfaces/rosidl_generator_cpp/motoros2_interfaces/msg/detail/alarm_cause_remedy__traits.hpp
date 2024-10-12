// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__TRAITS_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motoros2_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const AlarmCauseRemedy & msg,
  std::ostream & out)
{
  out << "{";
  // member: cause
  {
    out << "cause: ";
    rosidl_generator_traits::value_to_yaml(msg.cause, out);
    out << ", ";
  }

  // member: remedy
  {
    out << "remedy: ";
    rosidl_generator_traits::value_to_yaml(msg.remedy, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AlarmCauseRemedy & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cause
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cause: ";
    rosidl_generator_traits::value_to_yaml(msg.cause, out);
    out << "\n";
  }

  // member: remedy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remedy: ";
    rosidl_generator_traits::value_to_yaml(msg.remedy, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AlarmCauseRemedy & msg, bool use_flow_style = false)
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
  const motoros2_interfaces::msg::AlarmCauseRemedy & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::msg::AlarmCauseRemedy & msg)
{
  return motoros2_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::msg::AlarmCauseRemedy>()
{
  return "motoros2_interfaces::msg::AlarmCauseRemedy";
}

template<>
inline const char * name<motoros2_interfaces::msg::AlarmCauseRemedy>()
{
  return "motoros2_interfaces/msg/AlarmCauseRemedy";
}

template<>
struct has_fixed_size<motoros2_interfaces::msg::AlarmCauseRemedy>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motoros2_interfaces::msg::AlarmCauseRemedy>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motoros2_interfaces::msg::AlarmCauseRemedy>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__TRAITS_HPP_
