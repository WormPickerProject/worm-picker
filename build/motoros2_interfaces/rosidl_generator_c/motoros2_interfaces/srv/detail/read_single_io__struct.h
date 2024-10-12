// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/ReadSingleIO.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__READ_SINGLE_IO__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__READ_SINGLE_IO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ReadSingleIO in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__ReadSingleIO_Request
{
  /// Read (and return) the current value of the IO element at 'address'.
  ///
  /// Addresses are plain, base-10 integers, as used and displayed by the controller
  /// (on the teach pendant for instance).
  ///
  /// There are no restrictions as to which IO elements can be read, but they have
  /// to exist on the controller and be configured correctly.
  ///
  /// Refer also the Yaskawa Motoman documentation on IO addressing and
  /// configuration.
  uint32_t address;
} motoros2_interfaces__srv__ReadSingleIO_Request;

// Struct for a sequence of motoros2_interfaces__srv__ReadSingleIO_Request.
typedef struct motoros2_interfaces__srv__ReadSingleIO_Request__Sequence
{
  motoros2_interfaces__srv__ReadSingleIO_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__ReadSingleIO_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ReadSingleIO in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__ReadSingleIO_Response
{
  uint32_t result_code;
  rosidl_runtime_c__String message;
  bool success;
  int32_t value;
} motoros2_interfaces__srv__ReadSingleIO_Response;

// Struct for a sequence of motoros2_interfaces__srv__ReadSingleIO_Response.
typedef struct motoros2_interfaces__srv__ReadSingleIO_Response__Sequence
{
  motoros2_interfaces__srv__ReadSingleIO_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__ReadSingleIO_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__READ_SINGLE_IO__STRUCT_H_
