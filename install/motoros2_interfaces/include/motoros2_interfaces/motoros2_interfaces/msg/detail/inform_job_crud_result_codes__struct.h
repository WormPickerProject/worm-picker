// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_H_
#define MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RC_OK'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_OK = 1ul
};

/// Constant 'STR_OK'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_OK = "Success";

/// Constant 'RC_ERR_REFRESHING_JOB_LIST'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_ERR_REFRESHING_JOB_LIST = 10ul
};

/// Constant 'STR_ERR_REFRESHING_JOB_LIST'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_ERR_REFRESHING_JOB_LIST = "Error refreshing job list";

/// Constant 'RC_ERR_RETRIEVING_FILE_COUNT'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_ERR_RETRIEVING_FILE_COUNT = 11ul
};

/// Constant 'STR_ERR_RETRIEVING_FILE_COUNT'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_ERR_RETRIEVING_FILE_COUNT = "Error retrieving file count";

/// Constant 'RC_ERR_TOO_MANY_JOBS'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_ERR_TOO_MANY_JOBS = 12ul
};

/// Constant 'STR_ERR_TOO_MANY_JOBS'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_ERR_TOO_MANY_JOBS = "Too many jobs";

/// Constant 'RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST = 13ul
};

/// Constant 'STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST = "Failed retrieving job name from list";

/// Constant 'RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'.
enum
{
  motoros2_interfaces__msg__InformJobCrudResultCodes__RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE = 14ul
};

/// Constant 'STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'.
static const char * const motoros2_interfaces__msg__InformJobCrudResultCodes__STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE = "Error adding job name to service response";

/// Struct defined in msg/InformJobCrudResultCodes in the package motoros2_interfaces.
/**
  * SPDX-FileCopyrightText: 2024, Yaskawa America, Inc.
  * SPDX-FileCopyrightText: 2024, Delft University of Technology
  *
  * SPDX-License-Identifier: Apache-2.0
 */
typedef struct motoros2_interfaces__msg__InformJobCrudResultCodes
{
  uint8_t structure_needs_at_least_one_member;
} motoros2_interfaces__msg__InformJobCrudResultCodes;

// Struct for a sequence of motoros2_interfaces__msg__InformJobCrudResultCodes.
typedef struct motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence
{
  motoros2_interfaces__msg__InformJobCrudResultCodes * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_H_
