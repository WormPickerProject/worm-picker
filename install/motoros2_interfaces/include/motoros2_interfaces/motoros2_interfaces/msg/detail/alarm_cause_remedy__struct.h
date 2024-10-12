// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'cause'
// Member 'remedy'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AlarmCauseRemedy in the package motoros2_interfaces.
/**
  * SPDX-FileCopyrightText: 2023, Yaskawa America, Inc.
  * SPDX-FileCopyrightText: 2023, Delft University of Technology
  *
  * SPDX-License-Identifier: Apache-2.0
 */
typedef struct motoros2_interfaces__msg__AlarmCauseRemedy
{
  /// Cause
  rosidl_runtime_c__String cause;
  /// Remedy
  rosidl_runtime_c__String remedy;
} motoros2_interfaces__msg__AlarmCauseRemedy;

// Struct for a sequence of motoros2_interfaces__msg__AlarmCauseRemedy.
typedef struct motoros2_interfaces__msg__AlarmCauseRemedy__Sequence
{
  motoros2_interfaces__msg__AlarmCauseRemedy * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__msg__AlarmCauseRemedy__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_H_
