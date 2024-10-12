// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice
#include "industrial_msgs/msg/detail/device_info__rosidl_typesupport_fastrtps_cpp.hpp"
#include "industrial_msgs/msg/detail/device_info__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace industrial_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_industrial_msgs
cdr_serialize(
  const industrial_msgs::msg::DeviceInfo & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: model
  cdr << ros_message.model;
  // Member: serial_number
  cdr << ros_message.serial_number;
  // Member: hw_version
  cdr << ros_message.hw_version;
  // Member: sw_version
  cdr << ros_message.sw_version;
  // Member: address
  cdr << ros_message.address;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_industrial_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  industrial_msgs::msg::DeviceInfo & ros_message)
{
  // Member: model
  cdr >> ros_message.model;

  // Member: serial_number
  cdr >> ros_message.serial_number;

  // Member: hw_version
  cdr >> ros_message.hw_version;

  // Member: sw_version
  cdr >> ros_message.sw_version;

  // Member: address
  cdr >> ros_message.address;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_industrial_msgs
get_serialized_size(
  const industrial_msgs::msg::DeviceInfo & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: model
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.model.size() + 1);
  // Member: serial_number
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.serial_number.size() + 1);
  // Member: hw_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.hw_version.size() + 1);
  // Member: sw_version
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.sw_version.size() + 1);
  // Member: address
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.address.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_industrial_msgs
max_serialized_size_DeviceInfo(
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


  // Member: model
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

  // Member: serial_number
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

  // Member: hw_version
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

  // Member: sw_version
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

  // Member: address
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
    using DataType = industrial_msgs::msg::DeviceInfo;
    is_plain =
      (
      offsetof(DataType, address) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _DeviceInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const industrial_msgs::msg::DeviceInfo *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _DeviceInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<industrial_msgs::msg::DeviceInfo *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _DeviceInfo__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const industrial_msgs::msg::DeviceInfo *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _DeviceInfo__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_DeviceInfo(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _DeviceInfo__callbacks = {
  "industrial_msgs::msg",
  "DeviceInfo",
  _DeviceInfo__cdr_serialize,
  _DeviceInfo__cdr_deserialize,
  _DeviceInfo__get_serialized_size,
  _DeviceInfo__max_serialized_size
};

static rosidl_message_type_support_t _DeviceInfo__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_DeviceInfo__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace industrial_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_industrial_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<industrial_msgs::msg::DeviceInfo>()
{
  return &industrial_msgs::msg::typesupport_fastrtps_cpp::_DeviceInfo__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, industrial_msgs, msg, DeviceInfo)() {
  return &industrial_msgs::msg::typesupport_fastrtps_cpp::_DeviceInfo__handle;
}

#ifdef __cplusplus
}
#endif
