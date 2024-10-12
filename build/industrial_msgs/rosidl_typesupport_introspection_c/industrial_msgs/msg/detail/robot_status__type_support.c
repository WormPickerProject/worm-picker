// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "industrial_msgs/msg/detail/robot_status__rosidl_typesupport_introspection_c.h"
#include "industrial_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "industrial_msgs/msg/detail/robot_status__functions.h"
#include "industrial_msgs/msg/detail/robot_status__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `mode`
#include "industrial_msgs/msg/robot_mode.h"
// Member `mode`
#include "industrial_msgs/msg/detail/robot_mode__rosidl_typesupport_introspection_c.h"
// Member `e_stopped`
// Member `drives_powered`
// Member `motion_possible`
// Member `in_motion`
// Member `in_error`
#include "industrial_msgs/msg/tri_state.h"
// Member `e_stopped`
// Member `drives_powered`
// Member `motion_possible`
// Member `in_motion`
// Member `in_error`
#include "industrial_msgs/msg/detail/tri_state__rosidl_typesupport_introspection_c.h"
// Member `error_codes`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  industrial_msgs__msg__RobotStatus__init(message_memory);
}

void industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_fini_function(void * message_memory)
{
  industrial_msgs__msg__RobotStatus__fini(message_memory);
}

size_t industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__size_function__RobotStatus__error_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__error_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__error_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__fetch_function__RobotStatus__error_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__error_codes(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__assign_function__RobotStatus__error_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__error_codes(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__resize_function__RobotStatus__error_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[8] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "e_stopped",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, e_stopped),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "drives_powered",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, drives_powered),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motion_possible",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, motion_possible),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "in_motion",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, in_motion),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "in_error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, in_error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_codes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__RobotStatus, error_codes),  // bytes offset in struct
    NULL,  // default value
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__size_function__RobotStatus__error_codes,  // size() function pointer
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_const_function__RobotStatus__error_codes,  // get_const(index) function pointer
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__get_function__RobotStatus__error_codes,  // get(index) function pointer
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__fetch_function__RobotStatus__error_codes,  // fetch(index, &value) function pointer
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__assign_function__RobotStatus__error_codes,  // assign(index, value) function pointer
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__resize_function__RobotStatus__error_codes  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_members = {
  "industrial_msgs__msg",  // message namespace
  "RobotStatus",  // message name
  8,  // number of fields
  sizeof(industrial_msgs__msg__RobotStatus),
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array,  // message members
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle = {
  0,
  &industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_industrial_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, RobotStatus)() {
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, RobotMode)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, TriState)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, TriState)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, TriState)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, TriState)();
  industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, TriState)();
  if (!industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle.typesupport_identifier) {
    industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &industrial_msgs__msg__RobotStatus__rosidl_typesupport_introspection_c__RobotStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
