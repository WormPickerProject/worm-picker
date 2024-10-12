// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from motoros2_interfaces:msg/SelectionResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__FUNCTIONS_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "motoros2_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "motoros2_interfaces/msg/detail/selection_result_codes__struct.h"

/// Initialize msg/SelectionResultCodes message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motoros2_interfaces__msg__SelectionResultCodes
 * )) before or use
 * motoros2_interfaces__msg__SelectionResultCodes__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__init(motoros2_interfaces__msg__SelectionResultCodes * msg);

/// Finalize msg/SelectionResultCodes message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
void
motoros2_interfaces__msg__SelectionResultCodes__fini(motoros2_interfaces__msg__SelectionResultCodes * msg);

/// Create msg/SelectionResultCodes message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motoros2_interfaces__msg__SelectionResultCodes__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
motoros2_interfaces__msg__SelectionResultCodes *
motoros2_interfaces__msg__SelectionResultCodes__create();

/// Destroy msg/SelectionResultCodes message.
/**
 * It calls
 * motoros2_interfaces__msg__SelectionResultCodes__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
void
motoros2_interfaces__msg__SelectionResultCodes__destroy(motoros2_interfaces__msg__SelectionResultCodes * msg);

/// Check for msg/SelectionResultCodes message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__are_equal(const motoros2_interfaces__msg__SelectionResultCodes * lhs, const motoros2_interfaces__msg__SelectionResultCodes * rhs);

/// Copy a msg/SelectionResultCodes message.
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
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__copy(
  const motoros2_interfaces__msg__SelectionResultCodes * input,
  motoros2_interfaces__msg__SelectionResultCodes * output);

/// Initialize array of msg/SelectionResultCodes messages.
/**
 * It allocates the memory for the number of elements and calls
 * motoros2_interfaces__msg__SelectionResultCodes__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__Sequence__init(motoros2_interfaces__msg__SelectionResultCodes__Sequence * array, size_t size);

/// Finalize array of msg/SelectionResultCodes messages.
/**
 * It calls
 * motoros2_interfaces__msg__SelectionResultCodes__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
void
motoros2_interfaces__msg__SelectionResultCodes__Sequence__fini(motoros2_interfaces__msg__SelectionResultCodes__Sequence * array);

/// Create array of msg/SelectionResultCodes messages.
/**
 * It allocates the memory for the array and calls
 * motoros2_interfaces__msg__SelectionResultCodes__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
motoros2_interfaces__msg__SelectionResultCodes__Sequence *
motoros2_interfaces__msg__SelectionResultCodes__Sequence__create(size_t size);

/// Destroy array of msg/SelectionResultCodes messages.
/**
 * It calls
 * motoros2_interfaces__msg__SelectionResultCodes__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
void
motoros2_interfaces__msg__SelectionResultCodes__Sequence__destroy(motoros2_interfaces__msg__SelectionResultCodes__Sequence * array);

/// Check for msg/SelectionResultCodes message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__Sequence__are_equal(const motoros2_interfaces__msg__SelectionResultCodes__Sequence * lhs, const motoros2_interfaces__msg__SelectionResultCodes__Sequence * rhs);

/// Copy an array of msg/SelectionResultCodes messages.
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
ROSIDL_GENERATOR_C_PUBLIC_motoros2_interfaces
bool
motoros2_interfaces__msg__SelectionResultCodes__Sequence__copy(
  const motoros2_interfaces__msg__SelectionResultCodes__Sequence * input,
  motoros2_interfaces__msg__SelectionResultCodes__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__FUNCTIONS_H_
