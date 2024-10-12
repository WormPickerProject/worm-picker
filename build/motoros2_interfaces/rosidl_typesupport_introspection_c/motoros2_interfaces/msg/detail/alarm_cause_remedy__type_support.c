// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__rosidl_typesupport_introspection_c.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__functions.h"
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__struct.h"


// Include directives for member types
// Member `cause`
// Member `remedy`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__msg__AlarmCauseRemedy__init(message_memory);
}

void motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_fini_function(void * message_memory)
{
  motoros2_interfaces__msg__AlarmCauseRemedy__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_member_array[2] = {
  {
    "cause",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmCauseRemedy, cause),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "remedy",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__msg__AlarmCauseRemedy, remedy),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_members = {
  "motoros2_interfaces__msg",  // message namespace
  "AlarmCauseRemedy",  // message name
  2,  // number of fields
  sizeof(motoros2_interfaces__msg__AlarmCauseRemedy),
  motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_member_array,  // message members
  motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_type_support_handle = {
  0,
  &motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, AlarmCauseRemedy)() {
  if (!motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__msg__AlarmCauseRemedy__rosidl_typesupport_introspection_c__AlarmCauseRemedy_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
