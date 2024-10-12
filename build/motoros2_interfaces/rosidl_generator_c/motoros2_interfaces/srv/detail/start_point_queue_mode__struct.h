// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/StartPointQueueMode.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__START_POINT_QUEUE_MODE__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__START_POINT_QUEUE_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/StartPointQueueMode in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__StartPointQueueMode_Request
{
  uint8_t structure_needs_at_least_one_member;
} motoros2_interfaces__srv__StartPointQueueMode_Request;

// Struct for a sequence of motoros2_interfaces__srv__StartPointQueueMode_Request.
typedef struct motoros2_interfaces__srv__StartPointQueueMode_Request__Sequence
{
  motoros2_interfaces__srv__StartPointQueueMode_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__StartPointQueueMode_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result_code'
#include "motoros2_interfaces/msg/detail/motion_ready_enum__struct.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/StartPointQueueMode in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__StartPointQueueMode_Response
{
  motoros2_interfaces__msg__MotionReadyEnum result_code;
  /// string representation of the value in 'result_code', for humans
  rosidl_runtime_c__String message;
} motoros2_interfaces__srv__StartPointQueueMode_Response;

// Struct for a sequence of motoros2_interfaces__srv__StartPointQueueMode_Response.
typedef struct motoros2_interfaces__srv__StartPointQueueMode_Response__Sequence
{
  motoros2_interfaces__srv__StartPointQueueMode_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__StartPointQueueMode_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__START_POINT_QUEUE_MODE__STRUCT_H_
