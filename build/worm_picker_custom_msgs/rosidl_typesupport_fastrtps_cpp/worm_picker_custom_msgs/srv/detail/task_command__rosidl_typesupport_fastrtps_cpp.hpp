// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from worm_picker_custom_msgs:srv/TaskCommand.idl
// generated code does not contain a copyright notice

#ifndef WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "worm_picker_custom_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "worm_picker_custom_msgs/srv/detail/task_command__struct.hpp"

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

namespace worm_picker_custom_msgs
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
cdr_serialize(
  const worm_picker_custom_msgs::srv::TaskCommand_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  worm_picker_custom_msgs::srv::TaskCommand_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
get_serialized_size(
  const worm_picker_custom_msgs::srv::TaskCommand_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
max_serialized_size_TaskCommand_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace worm_picker_custom_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, worm_picker_custom_msgs, srv, TaskCommand_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "worm_picker_custom_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "worm_picker_custom_msgs/srv/detail/task_command__struct.hpp"

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

// already included above
// #include "fastcdr/Cdr.h"

namespace worm_picker_custom_msgs
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
cdr_serialize(
  const worm_picker_custom_msgs::srv::TaskCommand_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  worm_picker_custom_msgs::srv::TaskCommand_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
get_serialized_size(
  const worm_picker_custom_msgs::srv::TaskCommand_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
max_serialized_size_TaskCommand_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace worm_picker_custom_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, worm_picker_custom_msgs, srv, TaskCommand_Response)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "worm_picker_custom_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_worm_picker_custom_msgs
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, worm_picker_custom_msgs, srv, TaskCommand)();

#ifdef __cplusplus
}
#endif

#endif  // WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
