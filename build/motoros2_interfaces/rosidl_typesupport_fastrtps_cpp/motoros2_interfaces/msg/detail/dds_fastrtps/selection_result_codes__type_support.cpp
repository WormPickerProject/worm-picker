// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from motoros2_interfaces:msg/SelectionResultCodes.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/msg/detail/selection_result_codes__rosidl_typesupport_fastrtps_cpp.hpp"
#include "motoros2_interfaces/msg/detail/selection_result_codes__struct.hpp"

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

namespace motoros2_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_serialize(
  const motoros2_interfaces::msg::SelectionResultCodes & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: value
  cdr << ros_message.value;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  motoros2_interfaces::msg::SelectionResultCodes & ros_message)
{
  // Member: value
  cdr >> ros_message.value;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
get_serialized_size(
  const motoros2_interfaces::msg::SelectionResultCodes & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: value
  {
    size_t item_size = sizeof(ros_message.value);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
max_serialized_size_SelectionResultCodes(
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


  // Member: value
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = motoros2_interfaces::msg::SelectionResultCodes;
    is_plain =
      (
      offsetof(DataType, value) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _SelectionResultCodes__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::msg::SelectionResultCodes *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SelectionResultCodes__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<motoros2_interfaces::msg::SelectionResultCodes *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SelectionResultCodes__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::msg::SelectionResultCodes *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SelectionResultCodes__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_SelectionResultCodes(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _SelectionResultCodes__callbacks = {
  "motoros2_interfaces::msg",
  "SelectionResultCodes",
  _SelectionResultCodes__cdr_serialize,
  _SelectionResultCodes__cdr_deserialize,
  _SelectionResultCodes__get_serialized_size,
  _SelectionResultCodes__max_serialized_size
};

static rosidl_message_type_support_t _SelectionResultCodes__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SelectionResultCodes__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace motoros2_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::msg::SelectionResultCodes>()
{
  return &motoros2_interfaces::msg::typesupport_fastrtps_cpp::_SelectionResultCodes__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, msg, SelectionResultCodes)() {
  return &motoros2_interfaces::msg::typesupport_fastrtps_cpp::_SelectionResultCodes__handle;
}

#ifdef __cplusplus
}
#endif
