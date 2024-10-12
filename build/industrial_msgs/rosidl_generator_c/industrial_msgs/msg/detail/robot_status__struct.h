// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'mode'
#include "industrial_msgs/msg/detail/robot_mode__struct.h"
// Member 'e_stopped'
// Member 'drives_powered'
// Member 'motion_possible'
// Member 'in_motion'
// Member 'in_error'
#include "industrial_msgs/msg/detail/tri_state__struct.h"
// Member 'error_codes'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/RobotStatus in the package industrial_msgs.
/**
  * The RobotStatus message contains low level status information 
  * that is specific to an industrial robot controller
 */
typedef struct industrial_msgs__msg__RobotStatus
{
  /// The header frame ID is not used
  std_msgs__msg__Header header;
  /// The robot mode captures the operating mode of the robot.  When in
  /// manual, remote motion is not possible.
  industrial_msgs__msg__RobotMode mode;
  /// Estop status: True if robot is e-stopped.  The drives are disabled
  /// and motion is not possible.  The e-stop condition must be acknowledged
  /// and cleared before any motion can begin.
  industrial_msgs__msg__TriState e_stopped;
  /// Drive power status: True if drives are powered.  Motion commands will
  /// automatically enable the drives if required.  Drive power is not requred
  /// for possible motion
  industrial_msgs__msg__TriState drives_powered;
  /// Motion enabled: True if robot motion is possible.
  industrial_msgs__msg__TriState motion_possible;
  /// Motion status: True if robot is in motion, otherwise false
  industrial_msgs__msg__TriState in_motion;
  /// Error status: True if there is an error condition on the robot. Motion may
  /// or may not be affected (see motion_possible)
  industrial_msgs__msg__TriState in_error;
  /// Error code: Vendor specific error codes. If this list is empty, there are
  /// no active errors on the controller. Order of entries in this list does
  /// not necessarily encode for any specific severity or priority of active
  /// errors.
  rosidl_runtime_c__int32__Sequence error_codes;
} industrial_msgs__msg__RobotStatus;

// Struct for a sequence of industrial_msgs__msg__RobotStatus.
typedef struct industrial_msgs__msg__RobotStatus__Sequence
{
  industrial_msgs__msg__RobotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__RobotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_H_
