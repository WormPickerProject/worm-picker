// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/msg/detail/alarm_info__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "motoros2_interfaces/msg/detail/alarm_info__struct.h"
#include "motoros2_interfaces/msg/detail/alarm_info__functions.h"
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

#include "builtin_interfaces/msg/detail/time__functions.h"  // datetime
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__functions.h"  // help
#include "rosidl_runtime_c/string.h"  // contents, description, message
#include "rosidl_runtime_c/string_functions.h"  // contents, description, message

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_motoros2_interfaces
size_t get_serialized_size_builtin_interfaces__msg__Time(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_motoros2_interfaces
size_t max_serialized_size_builtin_interfaces__msg__Time(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_motoros2_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time)();
size_t get_serialized_size_motoros2_interfaces__msg__AlarmCauseRemedy(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_motoros2_interfaces__msg__AlarmCauseRemedy(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, motoros2_interfaces, msg, AlarmCauseRemedy)();


using _AlarmInfo__ros_msg_type = motoros2_interfaces__msg__AlarmInfo;

static bool _AlarmInfo__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _AlarmInfo__ros_msg_type * ros_message = static_cast<const _AlarmInfo__ros_msg_type *>(untyped_ros_message);
  // Field name: number
  {
    cdr << ros_message->number;
  }

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
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

  // Field name: sub_code
  {
    cdr << ros_message->sub_code;
  }

  // Field name: datetime
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->datetime, cdr))
    {
      return false;
    }
  }

  // Field name: contents
  {
    const rosidl_runtime_c__String * str = &ros_message->contents;
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

  // Field name: description
  {
    const rosidl_runtime_c__String * str = &ros_message->description;
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

  // Field name: help
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, motoros2_interfaces, msg, AlarmCauseRemedy
      )()->data);
    size_t size = ros_message->help.size;
    auto array_ptr = ros_message->help.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _AlarmInfo__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _AlarmInfo__ros_msg_type * ros_message = static_cast<_AlarmInfo__ros_msg_type *>(untyped_ros_message);
  // Field name: number
  {
    cdr >> ros_message->number;
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
  }

  // Field name: sub_code
  {
    cdr >> ros_message->sub_code;
  }

  // Field name: datetime
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->datetime))
    {
      return false;
    }
  }

  // Field name: contents
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->contents.data) {
      rosidl_runtime_c__String__init(&ros_message->contents);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->contents,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'contents'\n");
      return false;
    }
  }

  // Field name: description
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->description.data) {
      rosidl_runtime_c__String__init(&ros_message->description);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->description,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'description'\n");
      return false;
    }
  }

  // Field name: help
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, motoros2_interfaces, msg, AlarmCauseRemedy
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->help.data) {
      motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__fini(&ros_message->help);
    }
    if (!motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__init(&ros_message->help, size)) {
      fprintf(stderr, "failed to create array for field 'help'");
      return false;
    }
    auto array_ptr = ros_message->help.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motoros2_interfaces
size_t get_serialized_size_motoros2_interfaces__msg__AlarmInfo(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AlarmInfo__ros_msg_type * ros_message = static_cast<const _AlarmInfo__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name number
  {
    size_t item_size = sizeof(ros_message->number);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);
  // field.name sub_code
  {
    size_t item_size = sizeof(ros_message->sub_code);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name datetime

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->datetime), current_alignment);
  // field.name contents
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->contents.size + 1);
  // field.name description
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->description.size + 1);
  // field.name help
  {
    size_t array_size = ros_message->help.size;
    auto array_ptr = ros_message->help.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_motoros2_interfaces__msg__AlarmCauseRemedy(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _AlarmInfo__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_motoros2_interfaces__msg__AlarmInfo(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motoros2_interfaces
size_t max_serialized_size_motoros2_interfaces__msg__AlarmInfo(
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

  // member: number
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: message
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
  // member: sub_code
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: datetime
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_builtin_interfaces__msg__Time(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: contents
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
  // member: description
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
  // member: help
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_motoros2_interfaces__msg__AlarmCauseRemedy(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = motoros2_interfaces__msg__AlarmInfo;
    is_plain =
      (
      offsetof(DataType, help) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _AlarmInfo__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_motoros2_interfaces__msg__AlarmInfo(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_AlarmInfo = {
  "motoros2_interfaces::msg",
  "AlarmInfo",
  _AlarmInfo__cdr_serialize,
  _AlarmInfo__cdr_deserialize,
  _AlarmInfo__get_serialized_size,
  _AlarmInfo__max_serialized_size
};

static rosidl_message_type_support_t _AlarmInfo__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AlarmInfo,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, motoros2_interfaces, msg, AlarmInfo)() {
  return &_AlarmInfo__type_support;
}

#if defined(__cplusplus)
}
#endif
