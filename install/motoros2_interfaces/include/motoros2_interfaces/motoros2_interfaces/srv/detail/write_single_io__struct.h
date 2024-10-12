// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/WriteSingleIO.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__WRITE_SINGLE_IO__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__WRITE_SINGLE_IO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/WriteSingleIO in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__WriteSingleIO_Request
{
  /// Write 'value' to the IO element at 'address'.
  ///
  /// This service does not return anything.
  ///
  /// Addresses are plain, base-10 integers, as used and displayed by the controller
  /// (on the teach pendant for instance).
  ///
  /// Only the following addresses can be written to:
  ///
  ///  - 27010 and up : Network Inputs (25010 and up on DX100 and FS100)
  ///  - 10010 and up : Universal/General Outputs
  ///
  /// Refer also the Yaskawa Motoman documentation on IO addressing and
  /// configuration.
  uint32_t address;
  int32_t value;
} motoros2_interfaces__srv__WriteSingleIO_Request;

// Struct for a sequence of motoros2_interfaces__srv__WriteSingleIO_Request.
typedef struct motoros2_interfaces__srv__WriteSingleIO_Request__Sequence
{
  motoros2_interfaces__srv__WriteSingleIO_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__WriteSingleIO_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/WriteSingleIO in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__WriteSingleIO_Response
{
  uint32_t result_code;
  rosidl_runtime_c__String message;
  bool success;
} motoros2_interfaces__srv__WriteSingleIO_Response;

// Struct for a sequence of motoros2_interfaces__srv__WriteSingleIO_Response.
typedef struct motoros2_interfaces__srv__WriteSingleIO_Response__Sequence
{
  motoros2_interfaces__srv__WriteSingleIO_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__WriteSingleIO_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__WRITE_SINGLE_IO__STRUCT_H_
