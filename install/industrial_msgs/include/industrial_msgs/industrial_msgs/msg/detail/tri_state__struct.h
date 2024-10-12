// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from industrial_msgs:msg/TriState.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__STRUCT_H_
#define INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'UNKNOWN'.
/**
  * enumerated values
  * Unknown or unavailable
 */
enum
{
  industrial_msgs__msg__TriState__UNKNOWN = -1
};

/// Constant 'TRUE'.
/**
  * High state
 */
enum
{
  industrial_msgs__msg__TriState__TRUE = 1
};

/// Constant 'ON'.
enum
{
  industrial_msgs__msg__TriState__ON = 1
};

/// Constant 'ENABLED'.
enum
{
  industrial_msgs__msg__TriState__ENABLED = 1
};

/// Constant 'HIGH'.
enum
{
  industrial_msgs__msg__TriState__HIGH = 1
};

/// Constant 'CLOSED'.
enum
{
  industrial_msgs__msg__TriState__CLOSED = 1
};

/// Constant 'FALSE'.
/**
  * Low state
 */
enum
{
  industrial_msgs__msg__TriState__FALSE = 0
};

/// Constant 'OFF'.
enum
{
  industrial_msgs__msg__TriState__OFF = 0
};

/// Constant 'DISABLED'.
enum
{
  industrial_msgs__msg__TriState__DISABLED = 0
};

/// Constant 'LOW'.
enum
{
  industrial_msgs__msg__TriState__LOW = 0
};

/// Constant 'OPEN'.
enum
{
  industrial_msgs__msg__TriState__OPEN = 0
};

/// Struct defined in msg/TriState in the package industrial_msgs.
/**
  * The tri-state captures boolean values with the additional state of unknown
 */
typedef struct industrial_msgs__msg__TriState
{
  int8_t val;
} industrial_msgs__msg__TriState;

// Struct for a sequence of industrial_msgs__msg__TriState.
typedef struct industrial_msgs__msg__TriState__Sequence
{
  industrial_msgs__msg__TriState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} industrial_msgs__msg__TriState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__STRUCT_H_
