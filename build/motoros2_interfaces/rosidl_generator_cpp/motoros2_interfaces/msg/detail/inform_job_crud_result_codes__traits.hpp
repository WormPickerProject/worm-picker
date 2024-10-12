// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__TRAITS_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motoros2_interfaces/msg/detail/inform_job_crud_result_codes__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motoros2_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const InformJobCrudResultCodes & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InformJobCrudResultCodes & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InformJobCrudResultCodes & msg, bool use_flow_style = false)
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
  const motoros2_interfaces::msg::InformJobCrudResultCodes & msg,
  std::ostream & out, size_t indentation = 0)
{
  motoros2_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motoros2_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const motoros2_interfaces::msg::InformJobCrudResultCodes & msg)
{
  return motoros2_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motoros2_interfaces::msg::InformJobCrudResultCodes>()
{
  return "motoros2_interfaces::msg::InformJobCrudResultCodes";
}

template<>
inline const char * name<motoros2_interfaces::msg::InformJobCrudResultCodes>()
{
  return "motoros2_interfaces/msg/InformJobCrudResultCodes";
}

template<>
struct has_fixed_size<motoros2_interfaces::msg::InformJobCrudResultCodes>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motoros2_interfaces::msg::InformJobCrudResultCodes>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motoros2_interfaces::msg::InformJobCrudResultCodes>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__TRAITS_HPP_
