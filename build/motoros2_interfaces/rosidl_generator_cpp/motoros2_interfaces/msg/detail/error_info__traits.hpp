// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:msg/ErrorInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__TRAITS_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/msg/detail/error_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'datetime'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace motoros2_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ErrorInfo & msg,
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ErrorInfo & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ErrorInfo & msg, bool use_flow_style = false)
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
  const motoros2_interfaces::msg::ErrorInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::msg::ErrorInfo & msg)
{
  return motoros2_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::msg::ErrorInfo>()
{
  return "motoros2_interfaces::msg::ErrorInfo";
}

template<>
inline const char * name<motoros2_interfaces::msg::ErrorInfo>()
{
  return "motoros2_interfaces/msg/ErrorInfo";
}

template<>
struct has_fixed_size<motoros2_interfaces::msg::ErrorInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motoros2_interfaces::msg::ErrorInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motoros2_interfaces::msg::ErrorInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__TRAITS_HPP_
