// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/QueueTrajPoint.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joint_names'
#include "rosidl_runtime_c/string.h"
// Member 'point'
#include "trajectory_msgs/msg/detail/joint_trajectory_point__struct.h"

/// Struct defined in srv/QueueTrajPoint in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__QueueTrajPoint_Request
{
  /// Submit a trajectory point to the continuous motion queue.
  ///
  /// The start_point_queue_mode service must have been invoked first
  rosidl_runtime_c__String__Sequence joint_names;
  trajectory_msgs__msg__JointTrajectoryPoint point;
} motoros2_interfaces__srv__QueueTrajPoint_Request;

// Struct for a sequence of motoros2_interfaces__srv__QueueTrajPoint_Request.
typedef struct motoros2_interfaces__srv__QueueTrajPoint_Request__Sequence
{
  motoros2_interfaces__srv__QueueTrajPoint_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__QueueTrajPoint_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result_code'
#include "motoros2_interfaces/msg/detail/queue_result_enum__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/QueueTrajPoint in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__QueueTrajPoint_Response
{
  motoros2_interfaces__msg__QueueResultEnum result_code;
  /// string representation of the value in 'result_code', for humans
  rosidl_runtime_c__String message;
} motoros2_interfaces__srv__QueueTrajPoint_Response;

// Struct for a sequence of motoros2_interfaces__srv__QueueTrajPoint_Response.
typedef struct motoros2_interfaces__srv__QueueTrajPoint_Response__Sequence
{
  motoros2_interfaces__srv__QueueTrajPoint_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__QueueTrajPoint_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__STRUCT_H_
