// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/DebugLevel.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'DEBUG'.
enum
{
  industrial_msgs__msg__DebugLevel__DEBUG = 5
};

/// Constant 'INFO'.
enum
{
  industrial_msgs__msg__DebugLevel__INFO = 4
};

/// Constant 'WARN'.
enum
{
  industrial_msgs__msg__DebugLevel__WARN = 3
};

/// Constant 'ERROR'.
enum
{
  industrial_msgs__msg__DebugLevel__ERROR = 2
};

/// Constant 'FATAL'.
enum
{
  industrial_msgs__msg__DebugLevel__FATAL = 1
};

/// Constant 'NONE'.
enum
{
  industrial_msgs__msg__DebugLevel__NONE = 0
};

/// Struct defined in msg/DebugLevel in the package industrial_msgs.
/**
  * Debug level message enumeration.  This may replicate some functionality that
  * alreay exists in the ROS logger.
  * TODO: Get more information on the ROS Logger.
 */
typedef struct industrial_msgs__msg__DebugLevel
{
  uint8_t val;
} industrial_msgs__msg__DebugLevel;

// Struct for a sequence of industrial_msgs__msg__DebugLevel.
typedef struct industrial_msgs__msg__DebugLevel__Sequence
{
  industrial_msgs__msg__DebugLevel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__DebugLevel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_H_
