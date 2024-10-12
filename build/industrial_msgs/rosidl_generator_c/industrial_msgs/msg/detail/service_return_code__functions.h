// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from industrial_msgs:msg/ServiceReturnCode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__FUNCTIONS_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "industrial_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "industrial_msgs/msg/detail/service_return_code__struct.h"

/// Initialize msg/ServiceReturnCode message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * industrial_msgs__msg__ServiceReturnCode
 * )) before or use
 * industrial_msgs__msg__ServiceReturnCode__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__ServiceReturnCode__init(industrial_msgs__msg__ServiceReturnCode * msg);

/// Finalize msg/ServiceReturnCode message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__ServiceReturnCode__fini(industrial_msgs__msg__ServiceReturnCode * msg);

/// Create msg/ServiceReturnCode message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * industrial_msgs__msg__ServiceReturnCode__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__ServiceReturnCode *
industrial_msgs__msg__ServiceReturnCode__create();

/// Destroy msg/ServiceReturnCode message.
/**
 * It calls
 * industrial_msgs__msg__ServiceReturnCode__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__ServiceReturnCode__destroy(industrial_msgs__msg__ServiceReturnCode * msg);

/// Check for msg/ServiceReturnCode message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__ServiceReturnCode__are_equal(const industrial_msgs__msg__ServiceReturnCode * lhs, const industrial_msgs__msg__ServiceReturnCode * rhs);

/// Copy a msg/ServiceReturnCode message.
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
industrial_msgs__msg__ServiceReturnCode__copy(
  const industrial_msgs__msg__ServiceReturnCode * input,
  industrial_msgs__msg__ServiceReturnCode * output);

/// Initialize array of msg/ServiceReturnCode messages.
/**
 * It allocates the memory for the number of elements and calls
 * industrial_msgs__msg__ServiceReturnCode__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__ServiceReturnCode__Sequence__init(industrial_msgs__msg__ServiceReturnCode__Sequence * array, size_t size);

/// Finalize array of msg/ServiceReturnCode messages.
/**
 * It calls
 * industrial_msgs__msg__ServiceReturnCode__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__ServiceReturnCode__Sequence__fini(industrial_msgs__msg__ServiceReturnCode__Sequence * array);

/// Create array of msg/ServiceReturnCode messages.
/**
 * It allocates the memory for the array and calls
 * industrial_msgs__msg__ServiceReturnCode__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__ServiceReturnCode__Sequence *
industrial_msgs__msg__ServiceReturnCode__Sequence__create(size_t size);

/// Destroy array of msg/ServiceReturnCode messages.
/**
 * It calls
 * industrial_msgs__msg__ServiceReturnCode__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__ServiceReturnCode__Sequence__destroy(industrial_msgs__msg__ServiceReturnCode__Sequence * array);

/// Check for msg/ServiceReturnCode message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__ServiceReturnCode__Sequence__are_equal(const industrial_msgs__msg__ServiceReturnCode__Sequence * lhs, const industrial_msgs__msg__ServiceReturnCode__Sequence * rhs);

/// Copy an array of msg/ServiceReturnCode messages.
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
industrial_msgs__msg__ServiceReturnCode__Sequence__copy(
  const industrial_msgs__msg__ServiceReturnCode__Sequence * input,
  industrial_msgs__msg__ServiceReturnCode__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__SERVICE_RETURN_CODE__FUNCTIONS_H_
