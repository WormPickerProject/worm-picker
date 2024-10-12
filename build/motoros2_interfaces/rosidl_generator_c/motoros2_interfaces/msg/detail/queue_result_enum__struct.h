// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:msg/QueueResultEnum.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'SUCCESS'.
/**
  * The result code for an attempted invocation of the queue_traj_point service
 */
enum
{
  motoros2_interfaces__msg__QueueResultEnum__SUCCESS = 1
};

/// Constant 'SUCCESS_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__SUCCESS_STR = "";

/// Constant 'WRONG_MODE'.
enum
{
  motoros2_interfaces__msg__QueueResultEnum__WRONG_MODE = 2
};

/// Constant 'WRONG_MODE_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__WRONG_MODE_STR = "Must call start_point_queue_mode service";

/// Constant 'INIT_FAILURE'.
enum
{
  motoros2_interfaces__msg__QueueResultEnum__INIT_FAILURE = 3
};

/// Constant 'INIT_FAILURE_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__INIT_FAILURE_STR = "Failed to initialize the streaming trajectory";

/// Constant 'BUSY'.
enum
{
  motoros2_interfaces__msg__QueueResultEnum__BUSY = 4
};

/// Constant 'BUSY_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__BUSY_STR = "Busy processing the previous trajectory point. Please resend the next point shortly";

/// Constant 'INVALID_JOINT_LIST'.
enum
{
  motoros2_interfaces__msg__QueueResultEnum__INVALID_JOINT_LIST = 5
};

/// Constant 'INVALID_JOINT_LIST_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__INVALID_JOINT_LIST_STR = "Point must contain data for all joints";

/// Constant 'UNABLE_TO_PROCESS_POINT'.
enum
{
  motoros2_interfaces__msg__QueueResultEnum__UNABLE_TO_PROCESS_POINT = 6
};

/// Constant 'UNABLE_TO_PROCESS_POINT_STR'.
static const char * const motoros2_interfaces__msg__QueueResultEnum__UNABLE_TO_PROCESS_POINT_STR = "Error while processing the trajectory point. Check debug log for more details";

/// Struct defined in msg/QueueResultEnum in the package motoros2_interfaces.
/**
  * SPDX-FileCopyrightText: 2022-2023, Yaskawa America, Inc.
  * SPDX-FileCopyrightText: 2022-2023, Delft University of Technology
  *
  * SPDX-License-Identifier: Apache-2.0
 */
typedef struct motoros2_interfaces__msg__QueueResultEnum
{
  uint8_t value;
} motoros2_interfaces__msg__QueueResultEnum;

// Struct for a sequence of motoros2_interfaces__msg__QueueResultEnum.
typedef struct motoros2_interfaces__msg__QueueResultEnum__Sequence
{
  motoros2_interfaces__msg__QueueResultEnum * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__msg__QueueResultEnum__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_H_
