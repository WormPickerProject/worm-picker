// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__STRUCT_H_
#define MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetActiveAlarmInfo in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__GetActiveAlarmInfo_Request
{
  uint8_t structure_needs_at_least_one_member;
} motoros2_interfaces__srv__GetActiveAlarmInfo_Request;

// Struct for a sequence of motoros2_interfaces__srv__GetActiveAlarmInfo_Request.
typedef struct motoros2_interfaces__srv__GetActiveAlarmInfo_Request__Sequence
{
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__GetActiveAlarmInfo_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result_message'
#include "rosidl_runtime_c/string.h"
// Member 'alarms'
#include "motoros2_interfaces/msg/detail/alarm_info__struct.h"
// Member 'errors'
#include "motoros2_interfaces/msg/detail/error_info__struct.h"

/// Struct defined in srv/GetActiveAlarmInfo in the package motoros2_interfaces.
typedef struct motoros2_interfaces__srv__GetActiveAlarmInfo_Response
{
  /// Result of the service invocation. Values other than one (1) signal failure.
  ///
  /// NOTE: future versions of this service may use a different set of result codes
  uint32_t result_code;
  /// string representation of the value in 'result_code', for humans
  rosidl_runtime_c__String result_message;
  /// Each entry in this list provides detailed information about all currently
  /// active alarms. If this list is empty, there are no active alarms.
  ///
  /// Note: order of entries in this list does not encode for any specific severity
  /// or priority of active alarms.
  motoros2_interfaces__msg__AlarmInfo__Sequence alarms;
  /// Each entry in this list provides detailed information about all currently
  /// active errors. If this list is empty, there are no active errors.
  ///
  /// Note: order of entries in this list does not encode for any specific severity
  /// or priority of active errors.
  motoros2_interfaces__msg__ErrorInfo__Sequence errors;
} motoros2_interfaces__srv__GetActiveAlarmInfo_Response;

// Struct for a sequence of motoros2_interfaces__srv__GetActiveAlarmInfo_Response.
typedef struct motoros2_interfaces__srv__GetActiveAlarmInfo_Response__Sequence
{
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motoros2_interfaces__srv__GetActiveAlarmInfo_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__STRUCT_H_
