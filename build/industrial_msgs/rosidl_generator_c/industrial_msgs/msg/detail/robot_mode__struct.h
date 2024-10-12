// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/RobotMode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'UNKNOWN'.
/**
  * enumerated values
  * Unknown or unavailable
 */
enum
{
  industrial_msgs__msg__RobotMode__UNKNOWN = -1
};

/// Constant 'MANUAL'.
/**
  * Teach OR manual mode
 */
enum
{
  industrial_msgs__msg__RobotMode__MANUAL = 1
};

/// Constant 'AUTO'.
/**
  * Automatic mode
 */
enum
{
  industrial_msgs__msg__RobotMode__AUTO = 2
};

/// Struct defined in msg/RobotMode in the package industrial_msgs.
/**
  * The Robot mode message encapsulates the mode/teach state of the robot
  * Typically this is controlled by the pendant key switch, but not always
 */
typedef struct industrial_msgs__msg__RobotMode
{
  int8_t val;
} industrial_msgs__msg__RobotMode;

// Struct for a sequence of industrial_msgs__msg__RobotMode.
typedef struct industrial_msgs__msg__RobotMode__Sequence
{
  industrial_msgs__msg__RobotMode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__RobotMode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_H_
