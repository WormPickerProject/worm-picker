// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "motoros2_interfaces/msg/detail/inform_job_crud_result_codes__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace motoros2_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_serialize(
  const motoros2_interfaces::msg::InformJobCrudResultCodes & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  motoros2_interfaces::msg::InformJobCrudResultCodes & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
get_serialized_size(
  const motoros2_interfaces::msg::InformJobCrudResultCodes & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
max_serialized_size_InformJobCrudResultCodes(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace motoros2_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, msg, InformJobCrudResultCodes)();

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
