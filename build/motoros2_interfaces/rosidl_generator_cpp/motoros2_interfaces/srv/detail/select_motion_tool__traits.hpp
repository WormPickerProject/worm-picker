// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:srv/SelectMotionTool.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__TRAITS_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/srv/detail/select_motion_tool__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motoros2_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SelectMotionTool_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: group_number
  {
    out << "group_number: ";
    rosidl_generator_traits::value_to_yaml(msg.group_number, out);
    out << ", ";
  }

  // member: tool_number
  {
    out << "tool_number: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_number, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SelectMotionTool_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: group_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "group_number: ";
    rosidl_generator_traits::value_to_yaml(msg.group_number, out);
    out << "\n";
  }

  // member: tool_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tool_number: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_number, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SelectMotionTool_Request & msg, bool use_flow_style = false)
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

}  // namespace motoros2_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use motoros2_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motoros2_interfaces::srv::SelectMotionTool_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::srv::SelectMotionTool_Request & msg)
{
  return motoros2_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::srv::SelectMotionTool_Request>()
{
  return "motoros2_interfaces::srv::SelectMotionTool_Request";
}

template<>
inline const char * name<motoros2_interfaces::srv::SelectMotionTool_Request>()
{
  return "motoros2_interfaces/srv/SelectMotionTool_Request";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::SelectMotionTool_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motoros2_interfaces::srv::SelectMotionTool_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motoros2_interfaces::srv::SelectMotionTool_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result_code'
#include "motoros2_interfaces/msg/detail/selection_result_codes__traits.hpp"

namespace motoros2_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SelectMotionTool_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result_code
  {
    out << "result_code: ";
    to_flow_style_yaml(msg.result_code, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SelectMotionTool_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result_code:\n";
    to_block_style_yaml(msg.result_code, out, indentation + 2);
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

inline std::string to_yaml(const SelectMotionTool_Response & msg, bool use_flow_style = false)
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

}  // namespace motoros2_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use motoros2_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motoros2_interfaces::srv::SelectMotionTool_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::srv::SelectMotionTool_Response & msg)
{
  return motoros2_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::srv::SelectMotionTool_Response>()
{
  return "motoros2_interfaces::srv::SelectMotionTool_Response";
}

template<>
inline const char * name<motoros2_interfaces::srv::SelectMotionTool_Response>()
{
  return "motoros2_interfaces/srv/SelectMotionTool_Response";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::SelectMotionTool_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motoros2_interfaces::srv::SelectMotionTool_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motoros2_interfaces::srv::SelectMotionTool_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motoros2_interfaces::srv::SelectMotionTool>()
{
  return "motoros2_interfaces::srv::SelectMotionTool";
}

template<>
inline const char * name<motoros2_interfaces::srv::SelectMotionTool>()
{
  return "motoros2_interfaces/srv/SelectMotionTool";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::SelectMotionTool>
  : std::integral_constant<
    bool,
    has_fixed_size<motoros2_interfaces::srv::SelectMotionTool_Request>::value &&
    has_fixed_size<motoros2_interfaces::srv::SelectMotionTool_Response>::value
  >
{
};

template<>
struct has_bounded_size<motoros2_interfaces::srv::SelectMotionTool>
  : std::integral_constant<
    bool,
    has_bounded_size<motoros2_interfaces::srv::SelectMotionTool_Request>::value &&
    has_bounded_size<motoros2_interfaces::srv::SelectMotionTool_Response>::value
  >
{
};

template<>
struct is_service<motoros2_interfaces::srv::SelectMotionTool>
  : std::true_type
{
};

template<>
struct is_service_request<motoros2_interfaces::srv::SelectMotionTool_Request>
  : std::true_type
{
};

template<>
struct is_service_response<motoros2_interfaces::srv::SelectMotionTool_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__TRAITS_HPP_
