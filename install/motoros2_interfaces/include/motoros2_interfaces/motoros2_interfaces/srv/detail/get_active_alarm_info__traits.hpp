// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__TRAITS_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motoros2_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetActiveAlarmInfo_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetActiveAlarmInfo_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetActiveAlarmInfo_Request & msg, bool use_flow_style = false)
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
  const motoros2_interfaces::srv::GetActiveAlarmInfo_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::srv::GetActiveAlarmInfo_Request & msg)
{
  return motoros2_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>()
{
  return "motoros2_interfaces::srv::GetActiveAlarmInfo_Request";
}

template<>
inline const char * name<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>()
{
  return "motoros2_interfaces/srv/GetActiveAlarmInfo_Request";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'alarms'
#include "motoros2_interfaces/msg/detail/alarm_info__traits.hpp"
// Member 'errors'
#include "motoros2_interfaces/msg/detail/error_info__traits.hpp"

namespace motoros2_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetActiveAlarmInfo_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result_code
  {
    out << "result_code: ";
    rosidl_generator_traits::value_to_yaml(msg.result_code, out);
    out << ", ";
  }

  // member: result_message
  {
    out << "result_message: ";
    rosidl_generator_traits::value_to_yaml(msg.result_message, out);
    out << ", ";
  }

  // member: alarms
  {
    if (msg.alarms.size() == 0) {
      out << "alarms: []";
    } else {
      out << "alarms: [";
      size_t pending_items = msg.alarms.size();
      for (auto item : msg.alarms) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: errors
  {
    if (msg.errors.size() == 0) {
      out << "errors: []";
    } else {
      out << "errors: [";
      size_t pending_items = msg.errors.size();
      for (auto item : msg.errors) {
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
  const GetActiveAlarmInfo_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result_code: ";
    rosidl_generator_traits::value_to_yaml(msg.result_code, out);
    out << "\n";
  }

  // member: result_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result_message: ";
    rosidl_generator_traits::value_to_yaml(msg.result_message, out);
    out << "\n";
  }

  // member: alarms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.alarms.size() == 0) {
      out << "alarms: []\n";
    } else {
      out << "alarms:\n";
      for (auto item : msg.alarms) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: errors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.errors.size() == 0) {
      out << "errors: []\n";
    } else {
      out << "errors:\n";
      for (auto item : msg.errors) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetActiveAlarmInfo_Response & msg, bool use_flow_style = false)
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
  const motoros2_interfaces::srv::GetActiveAlarmInfo_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::srv::GetActiveAlarmInfo_Response & msg)
{
  return motoros2_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>()
{
  return "motoros2_interfaces::srv::GetActiveAlarmInfo_Response";
}

template<>
inline const char * name<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>()
{
  return "motoros2_interfaces/srv/GetActiveAlarmInfo_Response";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<motoros2_interfaces::srv::GetActiveAlarmInfo>()
{
  return "motoros2_interfaces::srv::GetActiveAlarmInfo";
}

template<>
inline const char * name<motoros2_interfaces::srv::GetActiveAlarmInfo>()
{
  return "motoros2_interfaces/srv/GetActiveAlarmInfo";
}

template<>
struct has_fixed_size<motoros2_interfaces::srv::GetActiveAlarmInfo>
  : std::integral_constant<
    bool,
    has_fixed_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>::value &&
    has_fixed_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>::value
  >
{
};

template<>
struct has_bounded_size<motoros2_interfaces::srv::GetActiveAlarmInfo>
  : std::integral_constant<
    bool,
    has_bounded_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>::value &&
    has_bounded_size<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>::value
  >
{
};

template<>
struct is_service<motoros2_interfaces::srv::GetActiveAlarmInfo>
  : std::true_type
{
};

template<>
struct is_service_request<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>
  : std::true_type
{
};

template<>
struct is_service_response<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__TRAITS_HPP_
