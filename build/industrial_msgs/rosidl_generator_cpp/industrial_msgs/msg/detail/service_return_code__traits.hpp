// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from industrial_msgs:msg/ServiceReturnCode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__TRAITS_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "industrial_msgs/msg/detail/service_return_code__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace industrial_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServiceReturnCode & msg,
  std::ostream & out)
{
  out << "{";
  // member: val
  {
    out << "val: ";
    rosidl_generator_traits::value_to_yaml(msg.val, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServiceReturnCode & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: val
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "val: ";
    rosidl_generator_traits::value_to_yaml(msg.val, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServiceReturnCode & msg, bool use_flow_style = false)
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
  const industrial_msgs::msg::ServiceReturnCode & msg,
  std::ostream & out, size_t indentation = 0)
{
  industrial_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use industrial_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const industrial_msgs::msg::ServiceReturnCode & msg)
{
  return industrial_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<industrial_msgs::msg::ServiceReturnCode>()
{
  return "industrial_msgs::msg::ServiceReturnCode";
}

template<>
inline const char * name<industrial_msgs::msg::ServiceReturnCode>()
{
  return "industrial_msgs/msg/ServiceReturnCode";
}

template<>
struct has_fixed_size<industrial_msgs::msg::ServiceReturnCode>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<industrial_msgs::msg::ServiceReturnCode>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<industrial_msgs::msg::ServiceReturnCode>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__TRAITS_HPP_
