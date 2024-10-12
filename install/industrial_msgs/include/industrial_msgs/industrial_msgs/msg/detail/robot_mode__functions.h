// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from industrial_msgs:msg/RobotMode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__FUNCTIONS_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "industrial_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "industrial_msgs/msg/detail/robot_mode__struct.h"

/// Initialize msg/RobotMode message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * industrial_msgs__msg__RobotMode
 * )) before or use
 * industrial_msgs__msg__RobotMode__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__init(industrial_msgs__msg__RobotMode * msg);

/// Finalize msg/RobotMode message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__RobotMode__fini(industrial_msgs__msg__RobotMode * msg);

/// Create msg/RobotMode message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * industrial_msgs__msg__RobotMode__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__RobotMode *
industrial_msgs__msg__RobotMode__create();

/// Destroy msg/RobotMode message.
/**
 * It calls
 * industrial_msgs__msg__RobotMode__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__RobotMode__destroy(industrial_msgs__msg__RobotMode * msg);

/// Check for msg/RobotMode message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__are_equal(const industrial_msgs__msg__RobotMode * lhs, const industrial_msgs__msg__RobotMode * rhs);

/// Copy a msg/RobotMode message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__copy(
  const industrial_msgs__msg__RobotMode * input,
  industrial_msgs__msg__RobotMode * output);

/// Initialize array of msg/RobotMode messages.
/**
 * It allocates the memory for the number of elements and calls
 * industrial_msgs__msg__RobotMode__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__Sequence__init(industrial_msgs__msg__RobotMode__Sequence * array, size_t size);

/// Finalize array of msg/RobotMode messages.
/**
 * It calls
 * industrial_msgs__msg__RobotMode__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__RobotMode__Sequence__fini(industrial_msgs__msg__RobotMode__Sequence * array);

/// Create array of msg/RobotMode messages.
/**
 * It allocates the memory for the array and calls
 * industrial_msgs__msg__RobotMode__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__RobotMode__Sequence *
industrial_msgs__msg__RobotMode__Sequence__create(size_t size);

/// Destroy array of msg/RobotMode messages.
/**
 * It calls
 * industrial_msgs__msg__RobotMode__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__RobotMode__Sequence__destroy(industrial_msgs__msg__RobotMode__Sequence * array);

/// Check for msg/RobotMode message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__Sequence__are_equal(const industrial_msgs__msg__RobotMode__Sequence * lhs, const industrial_msgs__msg__RobotMode__Sequence * rhs);

/// Copy an array of msg/RobotMode messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__RobotMode__Sequence__copy(
  const industrial_msgs__msg__RobotMode__Sequence * input,
  industrial_msgs__msg__RobotMode__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__FUNCTIONS_H_
