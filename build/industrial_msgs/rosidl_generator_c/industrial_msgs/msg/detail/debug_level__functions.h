// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from industrial_msgs:msg/DebugLevel.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__FUNCTIONS_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "industrial_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "industrial_msgs/msg/detail/debug_level__struct.h"

/// Initialize msg/DebugLevel message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * industrial_msgs__msg__DebugLevel
 * )) before or use
 * industrial_msgs__msg__DebugLevel__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__DebugLevel__init(industrial_msgs__msg__DebugLevel * msg);

/// Finalize msg/DebugLevel message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__DebugLevel__fini(industrial_msgs__msg__DebugLevel * msg);

/// Create msg/DebugLevel message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * industrial_msgs__msg__DebugLevel__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__DebugLevel *
industrial_msgs__msg__DebugLevel__create();

/// Destroy msg/DebugLevel message.
/**
 * It calls
 * industrial_msgs__msg__DebugLevel__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__DebugLevel__destroy(industrial_msgs__msg__DebugLevel * msg);

/// Check for msg/DebugLevel message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__DebugLevel__are_equal(const industrial_msgs__msg__DebugLevel * lhs, const industrial_msgs__msg__DebugLevel * rhs);

/// Copy a msg/DebugLevel message.
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
industrial_msgs__msg__DebugLevel__copy(
  const industrial_msgs__msg__DebugLevel * input,
  industrial_msgs__msg__DebugLevel * output);

/// Initialize array of msg/DebugLevel messages.
/**
 * It allocates the memory for the number of elements and calls
 * industrial_msgs__msg__DebugLevel__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__DebugLevel__Sequence__init(industrial_msgs__msg__DebugLevel__Sequence * array, size_t size);

/// Finalize array of msg/DebugLevel messages.
/**
 * It calls
 * industrial_msgs__msg__DebugLevel__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__DebugLevel__Sequence__fini(industrial_msgs__msg__DebugLevel__Sequence * array);

/// Create array of msg/DebugLevel messages.
/**
 * It allocates the memory for the array and calls
 * industrial_msgs__msg__DebugLevel__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
industrial_msgs__msg__DebugLevel__Sequence *
industrial_msgs__msg__DebugLevel__Sequence__create(size_t size);

/// Destroy array of msg/DebugLevel messages.
/**
 * It calls
 * industrial_msgs__msg__DebugLevel__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
void
industrial_msgs__msg__DebugLevel__Sequence__destroy(industrial_msgs__msg__DebugLevel__Sequence * array);

/// Check for msg/DebugLevel message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_industrial_msgs
bool
industrial_msgs__msg__DebugLevel__Sequence__are_equal(const industrial_msgs__msg__DebugLevel__Sequence * lhs, const industrial_msgs__msg__DebugLevel__Sequence * rhs);

/// Copy an array of msg/DebugLevel messages.
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
industrial_msgs__msg__DebugLevel__Sequence__copy(
  const industrial_msgs__msg__DebugLevel__Sequence * input,
  industrial_msgs__msg__DebugLevel__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__FUNCTIONS_H_
