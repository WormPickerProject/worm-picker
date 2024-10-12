// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/ListInformJobs.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__LIST_INFORM_JOBS__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__LIST_INFORM_JOBS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ListInformJobs in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__ListInformJobs_Request
{
  uint8_t structure_needs_at_least_one_member;
} motoros2_interfaces__srv__ListInformJobs_Request;

// Struct for a sequence of motoros2_interfaces__srv__ListInformJobs_Request.
typedef struct motoros2_interfaces__srv__ListInformJobs_Request__Sequence
{
  motoros2_interfaces__srv__ListInformJobs_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__ListInformJobs_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// Member 'names'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListInformJobs in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__ListInformJobs_Response
{
  /// Result of the service invocation. Values other than one (1) signal failure.
  ///
  /// Values defined in 'motoros2_interfaces/msg/InformJobCrudResultCodes'.
  ///
  /// NOTE: future versions of this service may use a different set of result
  /// codes. Always make sure to compare against defined named constants instead
  /// of integers directly.
  uint32_t result_code;
  /// string representation of the value in 'result_code', for humans
  rosidl_runtime_c__String message;
  /// The list of jobs present on the controller.
  ///
  /// NOTE:
  /// - these are job names, not filenames, and thus will not include the file
  ///   extension (JBI)
  /// - character encodings other than ASCII are only partially supported
  rosidl_runtime_c__String__Sequence names;
} motoros2_interfaces__srv__ListInformJobs_Response;

// Struct for a sequence of motoros2_interfaces__srv__ListInformJobs_Response.
typedef struct motoros2_interfaces__srv__ListInformJobs_Response__Sequence
{
  motoros2_interfaces__srv__ListInformJobs_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__ListInformJobs_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__LIST_INFORM_JOBS__STRUCT_H_
