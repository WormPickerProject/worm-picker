// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motoros2_interfaces/msg/detail/alarm_info__rosidl_typesupport_introspection_c.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motoros2_interfaces/msg/detail/alarm_info__functions.h"
#include "motoros2_interfaces/msg/detail/alarm_info__struct.h"


// Include directives for member types
// Member `message`
// Member `contents`
// Member `description`
#include "rosidl_runtime_c/string_functions.h"
// Member `datetime`
#include "builtin_interfaces/msg/time.h"
// Member `datetime`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `help`
#include "motoros2_interfaces/msg/alarm_cause_remedy.h"
// Member `help`
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__msg__AlarmInfo__init(message_memory);
}

void motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_fini_function(void * message_memory)
{
  motoros2_interfaces__msg__AlarmInfo__fini(message_memory);
}

size_t motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__size_function__AlarmInfo__help(
  const void * untyped_member)
{
  const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * member =
    (const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *)(untyped_member);
  return member->size;
}

const void * motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_const_function__AlarmInfo__help(
  const void * untyped_member, size_t index)
{
  const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * member =
    (const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *)(untyped_member);
  return &member->data[index];
}

void * motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_function__AlarmInfo__help(
  void * untyped_member, size_t index)
{
  motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * member =
    (motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *)(untyped_member);
  return &member->data[index];
}

void motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__fetch_function__AlarmInfo__help(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motoros2_interfaces__msg__AlarmCauseRemedy * item =
    ((const motoros2_interfaces__msg__AlarmCauseRemedy *)
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_const_function__AlarmInfo__help(untyped_member, index));
  motoros2_interfaces__msg__AlarmCauseRemedy * value =
    (motoros2_interfaces__msg__AlarmCauseRemedy *)(untyped_value);
  *value = *item;
}

void motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__assign_function__AlarmInfo__help(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motoros2_interfaces__msg__AlarmCauseRemedy * item =
    ((motoros2_interfaces__msg__AlarmCauseRemedy *)
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_function__AlarmInfo__help(untyped_member, index));
  const motoros2_interfaces__msg__AlarmCauseRemedy * value =
    (const motoros2_interfaces__msg__AlarmCauseRemedy *)(untyped_value);
  *item = *value;
}

bool motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__resize_function__AlarmInfo__help(
  void * untyped_member, size_t size)
{
  motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * member =
    (motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *)(untyped_member);
  motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__fini(member);
  return motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_member_array[7] = {
  {
    "number",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, number),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sub_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, sub_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "datetime",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, datetime),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "contents",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, contents),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "description",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, description),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "help",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmInfo, help),  // bytes offset in struct
    NULL,  // default value
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__size_function__AlarmInfo__help,  // size() function pointer
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_const_function__AlarmInfo__help,  // get_const(index) function pointer
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__get_function__AlarmInfo__help,  // get(index) function pointer
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__fetch_function__AlarmInfo__help,  // fetch(index, &value) function pointer
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__assign_function__AlarmInfo__help,  // assign(index, value) function pointer
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__resize_function__AlarmInfo__help  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_members = {
  "motoros2_interfaces__msg",  // message namespace
  "AlarmInfo",  // message name
  7,  // number of fields
  sizeof(motoros2_interfaces__msg__AlarmInfo),
  motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_member_array,  // message members
  motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_type_support_handle = {
  0,
  &motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, AlarmInfo)() {
  motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, AlarmCauseRemedy)();
  if (!motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__msg__AlarmInfo__rosidl_typesupport_introspection_c__AlarmInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
