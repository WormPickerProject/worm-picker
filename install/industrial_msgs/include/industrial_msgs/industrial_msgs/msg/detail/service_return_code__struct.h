// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/ServiceReturnCode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'SUCCESS'.
enum
{
  industrial_msgs__msg__ServiceReturnCode__SUCCESS = 1
};

/// Constant 'FAILURE'.
enum
{
  industrial_msgs__msg__ServiceReturnCode__FAILURE = -1
};

/// Struct defined in msg/ServiceReturnCode in the package industrial_msgs.
/**
  * Service return codes for simple requests.  All ROS-Industrial service
  * replies are required to have a return code indicating success or failure
  * Specific return codes for different failure should be negative.
 */
typedef struct industrial_msgs__msg__ServiceReturnCode
{
  int8_t val;
} industrial_msgs__msg__ServiceReturnCode;

// Struct for a sequence of industrial_msgs__msg__ServiceReturnCode.
typedef struct industrial_msgs__msg__ServiceReturnCode__Sequence
{
  industrial_msgs__msg__ServiceReturnCode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__ServiceReturnCode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__STRUCT_H_
