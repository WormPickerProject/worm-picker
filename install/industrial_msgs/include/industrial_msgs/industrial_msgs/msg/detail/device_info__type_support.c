// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "industrial_msgs/msg/detail/device_info__rosidl_typesupport_introspection_c.h"
#include "industrial_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "industrial_msgs/msg/detail/device_info__functions.h"
#include "industrial_msgs/msg/detail/device_info__struct.h"


// Include directives for member types
// Member `model`
// Member `serial_number`
// Member `hw_version`
// Member `sw_version`
// Member `address`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  industrial_msgs__msg__DeviceInfo__init(message_memory);
}

void industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_fini_function(void * message_memory)
{
  industrial_msgs__msg__DeviceInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_member_array[5] = {
  {
    "model",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__DeviceInfo, model),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "serial_number",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__DeviceInfo, serial_number),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "hw_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__DeviceInfo, hw_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sw_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__DeviceInfo, sw_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "address",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(industrial_msgs__msg__DeviceInfo, address),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_members = {
  "industrial_msgs__msg",  // message namespace
  "DeviceInfo",  // message name
  5,  // number of fields
  sizeof(industrial_msgs__msg__DeviceInfo),
  industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_member_array,  // message members
  industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_type_support_handle = {
  0,
  &industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_industrial_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, industrial_msgs, msg, DeviceInfo)() {
  if (!industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_type_support_handle.typesupport_identifier) {
    industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &industrial_msgs__msg__DeviceInfo__rosidl_typesupport_introspection_c__DeviceInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
