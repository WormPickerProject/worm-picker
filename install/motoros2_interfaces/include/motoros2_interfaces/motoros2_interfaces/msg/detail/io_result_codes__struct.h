// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:msg/IoResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'OK'.
enum
{
  motoros2_interfaces__msg__IoResultCodes__OK = 0ul
};

/// Constant 'OK_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__OK_STR = "Success";

/// Constant 'READ_ADDRESS_INVALID'.
/**
  * The ioAddress cannot be read on this controller
 */
enum
{
  motoros2_interfaces__msg__IoResultCodes__READ_ADDRESS_INVALID = 1001ul
};

/// Constant 'READ_ADDRESS_INVALID_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__READ_ADDRESS_INVALID_STR = "Address cannot be read from (out of readable range)";

/// Constant 'WRITE_ADDRESS_INVALID'.
/**
  * The ioAddress cannot be written to on this controller
 */
enum
{
  motoros2_interfaces__msg__IoResultCodes__WRITE_ADDRESS_INVALID = 1002ul
};

/// Constant 'WRITE_ADDRESS_INVALID_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__WRITE_ADDRESS_INVALID_STR = "Address cannot be written to (out of writable range)";

/// Constant 'WRITE_VALUE_INVALID'.
/**
  * The value supplied is not a valid value for the addressed IO element
 */
enum
{
  motoros2_interfaces__msg__IoResultCodes__WRITE_VALUE_INVALID = 1003ul
};

/// Constant 'WRITE_VALUE_INVALID_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__WRITE_VALUE_INVALID_STR = "Illegal value for the type of IO element addressed";

/// Constant 'READ_API_ERROR'.
/**
  * mpReadIO return -1
 */
enum
{
  motoros2_interfaces__msg__IoResultCodes__READ_API_ERROR = 1004ul
};

/// Constant 'READ_API_ERROR_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__READ_API_ERROR_STR = "The MotoPlus function mpReadIO returned -1. No further information is available";

/// Constant 'WRITE_API_ERROR'.
/**
  * mpWriteIO returned -1
 */
enum
{
  motoros2_interfaces__msg__IoResultCodes__WRITE_API_ERROR = 1005ul
};

/// Constant 'WRITE_API_ERROR_STR'.
static const char * const motoros2_interfaces__msg__IoResultCodes__WRITE_API_ERROR_STR = "The MotoPlus function mpWriteIO returned -1. No further information is available";

/// Constant 'UNKNOWN_API_ERROR_STR'.
/**
  * Unknown fallback failure
 */
static const char * const motoros2_interfaces__msg__IoResultCodes__UNKNOWN_API_ERROR_STR = "Unknown error accessing I/O. No further information is available";

/// Struct defined in msg/IoResultCodes in the package motoros2_interfaces.
/**
  * SPDX-FileCopyrightText: 2022-2023, Yaskawa America, Inc.
  * SPDX-FileCopyrightText: 2022-2023, Delft University of Technology
  *
  * SPDX-License-Identifier: Apache-2.0
 */
typedef struct motoros2_interfaces__msg__IoResultCodes
{
  uint8_t structure_needs_at_least_one_member;
} motoros2_interfaces__msg__IoResultCodes;

// Struct for a sequence of motoros2_interfaces__msg__IoResultCodes.
typedef struct motoros2_interfaces__msg__IoResultCodes__Sequence
{
  motoros2_interfaces__msg__IoResultCodes * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__msg__IoResultCodes__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_H_
