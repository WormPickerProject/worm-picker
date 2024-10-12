// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'model'
// Member 'serial_number'
// Member 'hw_version'
// Member 'sw_version'
// Member 'address'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DeviceInfo in the package industrial_msgs.
/**
  * Device info captures device agnostic information about a piece of hardware.
  * This message is meant as a generic as possible.  Items that don't apply should
  * be left blank.  This message is not meant to replace diagnostic messages, but
  * rather provide a standard service message that can be used to populate standard
  * components (like a GUI for example)
 */
typedef struct industrial_msgs__msg__DeviceInfo
{
  rosidl_runtime_c__String model;
  rosidl_runtime_c__String serial_number;
  rosidl_runtime_c__String hw_version;
  rosidl_runtime_c__String sw_version;
  rosidl_runtime_c__String address;
} industrial_msgs__msg__DeviceInfo;

// Struct for a sequence of industrial_msgs__msg__DeviceInfo.
typedef struct industrial_msgs__msg__DeviceInfo__Sequence
{
  industrial_msgs__msg__DeviceInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__DeviceInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_H_
