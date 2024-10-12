// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from worm_picker_custom_msgs:srv/TaskCommand.idl
// generated code does not contain a copyright notice

#ifndef WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__TRAITS_HPP_
#define WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "worm_picker_custom_msgs/srv/detail/task_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace worm_picker_custom_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const TaskCommand_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TaskCommand_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TaskCommand_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace worm_picker_custom_msgs

namespace rosidl_generator_traits
{

[[deprecated("use worm_picker_custom_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const worm_picker_custom_msgs::srv::TaskCommand_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  worm_picker_custom_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use worm_picker_custom_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const worm_picker_custom_msgs::srv::TaskCommand_Request & msg)
{
  return worm_picker_custom_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<worm_picker_custom_msgs::srv::TaskCommand_Request>()
{
  return "worm_picker_custom_msgs::srv::TaskCommand_Request";
}

template<>
inline const char * name<worm_picker_custom_msgs::srv::TaskCommand_Request>()
{
  return "worm_picker_custom_msgs/srv/TaskCommand_Request";
}

template<>
struct has_fixed_size<worm_picker_custom_msgs::srv::TaskCommand_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<worm_picker_custom_msgs::srv::TaskCommand_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<worm_picker_custom_msgs::srv::TaskCommand_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace worm_picker_custom_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const TaskCommand_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TaskCommand_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TaskCommand_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace worm_picker_custom_msgs

namespace rosidl_generator_traits
{

[[deprecated("use worm_picker_custom_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const worm_picker_custom_msgs::srv::TaskCommand_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  worm_picker_custom_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use worm_picker_custom_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const worm_picker_custom_msgs::srv::TaskCommand_Response & msg)
{
  return worm_picker_custom_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<worm_picker_custom_msgs::srv::TaskCommand_Response>()
{
  return "worm_picker_custom_msgs::srv::TaskCommand_Response";
}

template<>
inline const char * name<worm_picker_custom_msgs::srv::TaskCommand_Response>()
{
  return "worm_picker_custom_msgs/srv/TaskCommand_Response";
}

template<>
struct has_fixed_size<worm_picker_custom_msgs::srv::TaskCommand_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<worm_picker_custom_msgs::srv::TaskCommand_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<worm_picker_custom_msgs::srv::TaskCommand_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<worm_picker_custom_msgs::srv::TaskCommand>()
{
  return "worm_picker_custom_msgs::srv::TaskCommand";
}

template<>
inline const char * name<worm_picker_custom_msgs::srv::TaskCommand>()
{
  return "worm_picker_custom_msgs/srv/TaskCommand";
}

template<>
struct has_fixed_size<worm_picker_custom_msgs::srv::TaskCommand>
  : std::integral_constant<
    bool,
    has_fixed_size<worm_picker_custom_msgs::srv::TaskCommand_Request>::value &&
    has_fixed_size<worm_picker_custom_msgs::srv::TaskCommand_Response>::value
  >
{
};

template<>
struct has_bounded_size<worm_picker_custom_msgs::srv::TaskCommand>
  : std::integral_constant<
    bool,
    has_bounded_size<worm_picker_custom_msgs::srv::TaskCommand_Request>::value &&
    has_bounded_size<worm_picker_custom_msgs::srv::TaskCommand_Response>::value
  >
{
};

template<>
struct is_service<worm_picker_custom_msgs::srv::TaskCommand>
  : std::true_type
{
};

template<>
struct is_service_request<worm_picker_custom_msgs::srv::TaskCommand_Request>
  : std::true_type
{
};

template<>
struct is_service_response<worm_picker_custom_msgs::srv::TaskCommand_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__TRAITS_HPP_
