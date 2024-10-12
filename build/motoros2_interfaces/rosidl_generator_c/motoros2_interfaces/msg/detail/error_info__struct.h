// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:msg/ErrorInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'datetime'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/ErrorInfo in the package motoros2_interfaces.
/**
  * SPDX-FileCopyrightText: 2023, Yaskawa America, Inc.
  * SPDX-FileCopyrightText: 2023, Delft University of Technology
  *
  * SPDX-License-Identifier: Apache-2.0
 */
typedef struct motoros2_interfaces__msg__ErrorInfo
{
  /// Error Number
  uint32_t number;
  /// Error Name/Message
  rosidl_runtime_c__String message;
  /// Sub Code
  int32_t sub_code;
  /// reserved for future use
  ///
  /// Date & time at which this error was raised on the controller
  ///
  /// NOTE: in accordance with the "Clock and Time" ROS 2 design article, this
  /// stamp is in ROSTime == (local) SystemTime on Yaskawa Motoman robot
  /// controllers, as the latter is the only clock source supported on those
  /// platforms.
  ///
  /// This stamp will not be corrected for Host PC <-> Yaskawa controller clock
  /// drift, as it is intended purely for informational purposes (ie: for humans)
  /// at this time.
  builtin_interfaces__msg__Time datetime;
} motoros2_interfaces__msg__ErrorInfo;

// Struct for a sequence of motoros2_interfaces__msg__ErrorInfo.
typedef struct motoros2_interfaces__msg__ErrorInfo__Sequence
{
  motoros2_interfaces__msg__ErrorInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__msg__ErrorInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_H_
