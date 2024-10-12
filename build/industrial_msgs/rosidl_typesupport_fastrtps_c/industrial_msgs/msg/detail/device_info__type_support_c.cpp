// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice
#include "industrial_msgs/msg/detail/device_info__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "industrial_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "industrial_msgs/msg/detail/device_info__struct.h"
#include "industrial_msgs/msg/detail/device_info__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // address, hw_version, model, serial_number, sw_version
#include "rosidl_runtime_c/string_functions.h"  // address, hw_version, model, serial_number, sw_version

// forward declare type support functions


using _DeviceInfo__ros_msg_type = industrial_msgs__msg__DeviceInfo;

static bool _DeviceInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _DeviceInfo__ros_msg_type * ros_message = static_cast<const _DeviceInfo__ros_msg_type *>(untyped_ros_message);
  // Field name: model
  {
    const rosidl_runtime_c__String * str = &ros_message->model;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: serial_number
  {
    const rosidl_runtime_c__String * str = &ros_message->serial_number;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: hw_version
  {
    const rosidl_runtime_c__String * str = &ros_message->hw_version;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: sw_version
  {
    const rosidl_runtime_c__String * str = &ros_message->sw_version;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: address
  {
    const rosidl_runtime_c__String * str = &ros_message->address;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _DeviceInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _DeviceInfo__ros_msg_type * ros_message = static_cast<_DeviceInfo__ros_msg_type *>(untyped_ros_message);
  // Field name: model
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->model.data) {
      rosidl_runtime_c__String__init(&ros_message->model);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->model,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'model'\n");
      return false;
    }
  }

  // Field name: serial_number
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->serial_number.data) {
      rosidl_runtime_c__String__init(&ros_message->serial_number);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->serial_number,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'serial_number'\n");
      return false;
    }
  }

  // Field name: hw_version
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->hw_version.data) {
      rosidl_runtime_c__String__init(&ros_message->hw_version);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->hw_version,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'hw_version'\n");
      return false;
    }
  }

  // Field name: sw_version
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->sw_version.data) {
      rosidl_runtime_c__String__init(&ros_message->sw_version);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->sw_version,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'sw_version'\n");
      return false;
    }
  }

  // Field name: address
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->address.data) {
      rosidl_runtime_c__String__init(&ros_message->address);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->address,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'address'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_industrial_msgs
size_t get_serialized_size_industrial_msgs__msg__DeviceInfo(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _DeviceInfo__ros_msg_type * ros_message = static_cast<const _DeviceInfo__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name model
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->model.size + 1);
  // field.name serial_number
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->serial_number.size + 1);
  // field.name hw_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->hw_version.size + 1);
  // field.name sw_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->sw_version.size + 1);
  // field.name address
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->address.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _DeviceInfo__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_industrial_msgs__msg__DeviceInfo(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_industrial_msgs
size_t max_serialized_size_industrial_msgs__msg__DeviceInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: model
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: serial_number
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: hw_version
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: sw_version
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: address
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = industrial_msgs__msg__DeviceInfo;
    is_plain =
      (
      offsetof(DataType, address) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _DeviceInfo__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_industrial_msgs__msg__DeviceInfo(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_DeviceInfo = {
  "industrial_msgs::msg",
  "DeviceInfo",
  _DeviceInfo__cdr_serialize,
  _DeviceInfo__cdr_deserialize,
  _DeviceInfo__get_serialized_size,
  _DeviceInfo__max_serialized_size
};

static rosidl_message_type_support_t _DeviceInfo__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_DeviceInfo,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, industrial_msgs, msg, DeviceInfo)() {
  return &_DeviceInfo__type_support;
}

#if defined(__cplusplus)
}
#endif
