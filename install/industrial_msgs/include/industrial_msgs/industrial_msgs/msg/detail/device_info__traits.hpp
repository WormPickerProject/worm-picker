// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__TRAITS_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "industrial_msgs/msg/detail/device_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace industrial_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DeviceInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: model
  {
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << ", ";
  }

  // member: serial_number
  {
    out << "serial_number: ";
    rosidl_generator_traits::value_to_yaml(msg.serial_number, out);
    out << ", ";
  }

  // member: hw_version
  {
    out << "hw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.hw_version, out);
    out << ", ";
  }

  // member: sw_version
  {
    out << "sw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_version, out);
    out << ", ";
  }

  // member: address
  {
    out << "address: ";
    rosidl_generator_traits::value_to_yaml(msg.address, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DeviceInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: model
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << "\n";
  }

  // member: serial_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "serial_number: ";
    rosidl_generator_traits::value_to_yaml(msg.serial_number, out);
    out << "\n";
  }

  // member: hw_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.hw_version, out);
    out << "\n";
  }

  // member: sw_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sw_version: ";
    rosidl_generator_traits::value_to_yaml(msg.sw_version, out);
    out << "\n";
  }

  // member: address
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "address: ";
    rosidl_generator_traits::value_to_yaml(msg.address, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DeviceInfo & msg, bool use_flow_style = false)
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
  const industrial_msgs::msg::DeviceInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  industrial_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use industrial_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const industrial_msgs::msg::DeviceInfo & msg)
{
  return industrial_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<industrial_msgs::msg::DeviceInfo>()
{
  return "industrial_msgs::msg::DeviceInfo";
}

template<>
inline const char * name<industrial_msgs::msg::DeviceInfo>()
{
  return "industrial_msgs/msg/DeviceInfo";
}

template<>
struct has_fixed_size<industrial_msgs::msg::DeviceInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<industrial_msgs::msg::DeviceInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<industrial_msgs::msg::DeviceInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__TRAITS_HPP_
