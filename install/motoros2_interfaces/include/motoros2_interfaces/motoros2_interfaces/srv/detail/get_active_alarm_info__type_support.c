// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__rosidl_typesupport_introspection_c.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__functions.h"
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request__init(message_memory);
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_fini_function(void * message_memory)
{
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__GetActiveAlarmInfo_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_members = {
  "motoros2_interfaces__srv",  // message namespace
  "GetActiveAlarmInfo_Request",  // message name
  1,  // number of fields
  sizeof(motoros2_interfaces__srv__GetActiveAlarmInfo_Request),
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_member_array,  // message members
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_type_support_handle = {
  0,
  &motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Request)() {
  if (!motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__srv__GetActiveAlarmInfo_Request__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__rosidl_typesupport_introspection_c.h"
// already included above
// #include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__functions.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.h"


// Include directives for member types
// Member `result_message`
#include "rosidl_runtime_c/string_functions.h"
// Member `alarms`
#include "motoros2_interfaces/msg/alarm_info.h"
// Member `alarms`
#include "motoros2_interfaces/msg/detail/alarm_info__rosidl_typesupport_introspection_c.h"
// Member `errors`
#include "motoros2_interfaces/msg/error_info.h"
// Member `errors`
#include "motoros2_interfaces/msg/detail/error_info__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__init(message_memory);
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_fini_function(void * message_memory)
{
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__fini(message_memory);
}

size_t motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__size_function__GetActiveAlarmInfo_Response__alarms(
  const void * untyped_member)
{
  const motoros2_interfaces__msg__AlarmInfo__Sequence * member =
    (const motoros2_interfaces__msg__AlarmInfo__Sequence *)(untyped_member);
  return member->size;
}

const void * motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__alarms(
  const void * untyped_member, size_t index)
{
  const motoros2_interfaces__msg__AlarmInfo__Sequence * member =
    (const motoros2_interfaces__msg__AlarmInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__alarms(
  void * untyped_member, size_t index)
{
  motoros2_interfaces__msg__AlarmInfo__Sequence * member =
    (motoros2_interfaces__msg__AlarmInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__fetch_function__GetActiveAlarmInfo_Response__alarms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motoros2_interfaces__msg__AlarmInfo * item =
    ((const motoros2_interfaces__msg__AlarmInfo *)
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__alarms(untyped_member, index));
  motoros2_interfaces__msg__AlarmInfo * value =
    (motoros2_interfaces__msg__AlarmInfo *)(untyped_value);
  *value = *item;
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__assign_function__GetActiveAlarmInfo_Response__alarms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motoros2_interfaces__msg__AlarmInfo * item =
    ((motoros2_interfaces__msg__AlarmInfo *)
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__alarms(untyped_member, index));
  const motoros2_interfaces__msg__AlarmInfo * value =
    (const motoros2_interfaces__msg__AlarmInfo *)(untyped_value);
  *item = *value;
}

bool motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__resize_function__GetActiveAlarmInfo_Response__alarms(
  void * untyped_member, size_t size)
{
  motoros2_interfaces__msg__AlarmInfo__Sequence * member =
    (motoros2_interfaces__msg__AlarmInfo__Sequence *)(untyped_member);
  motoros2_interfaces__msg__AlarmInfo__Sequence__fini(member);
  return motoros2_interfaces__msg__AlarmInfo__Sequence__init(member, size);
}

size_t motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__size_function__GetActiveAlarmInfo_Response__errors(
  const void * untyped_member)
{
  const motoros2_interfaces__msg__ErrorInfo__Sequence * member =
    (const motoros2_interfaces__msg__ErrorInfo__Sequence *)(untyped_member);
  return member->size;
}

const void * motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__errors(
  const void * untyped_member, size_t index)
{
  const motoros2_interfaces__msg__ErrorInfo__Sequence * member =
    (const motoros2_interfaces__msg__ErrorInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__errors(
  void * untyped_member, size_t index)
{
  motoros2_interfaces__msg__ErrorInfo__Sequence * member =
    (motoros2_interfaces__msg__ErrorInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__fetch_function__GetActiveAlarmInfo_Response__errors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motoros2_interfaces__msg__ErrorInfo * item =
    ((const motoros2_interfaces__msg__ErrorInfo *)
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__errors(untyped_member, index));
  motoros2_interfaces__msg__ErrorInfo * value =
    (motoros2_interfaces__msg__ErrorInfo *)(untyped_value);
  *value = *item;
}

void motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__assign_function__GetActiveAlarmInfo_Response__errors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motoros2_interfaces__msg__ErrorInfo * item =
    ((motoros2_interfaces__msg__ErrorInfo *)
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__errors(untyped_member, index));
  const motoros2_interfaces__msg__ErrorInfo * value =
    (const motoros2_interfaces__msg__ErrorInfo *)(untyped_value);
  *item = *value;
}

bool motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__resize_function__GetActiveAlarmInfo_Response__errors(
  void * untyped_member, size_t size)
{
  motoros2_interfaces__msg__ErrorInfo__Sequence * member =
    (motoros2_interfaces__msg__ErrorInfo__Sequence *)(untyped_member);
  motoros2_interfaces__msg__ErrorInfo__Sequence__fini(member);
  return motoros2_interfaces__msg__ErrorInfo__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_member_array[4] = {
  {
    "result_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__GetActiveAlarmInfo_Response, result_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__GetActiveAlarmInfo_Response, result_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "alarms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__GetActiveAlarmInfo_Response, alarms),  // bytes offset in struct
    NULL,  // default value
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__size_function__GetActiveAlarmInfo_Response__alarms,  // size() function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__alarms,  // get_const(index) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__alarms,  // get(index) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__fetch_function__GetActiveAlarmInfo_Response__alarms,  // fetch(index, &value) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__assign_function__GetActiveAlarmInfo_Response__alarms,  // assign(index, value) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__resize_function__GetActiveAlarmInfo_Response__alarms  // resize(index) function pointer
  },
  {
    "errors",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__GetActiveAlarmInfo_Response, errors),  // bytes offset in struct
    NULL,  // default value
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__size_function__GetActiveAlarmInfo_Response__errors,  // size() function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_const_function__GetActiveAlarmInfo_Response__errors,  // get_const(index) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__get_function__GetActiveAlarmInfo_Response__errors,  // get(index) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__fetch_function__GetActiveAlarmInfo_Response__errors,  // fetch(index, &value) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__assign_function__GetActiveAlarmInfo_Response__errors,  // assign(index, value) function pointer
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__resize_function__GetActiveAlarmInfo_Response__errors  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_members = {
  "motoros2_interfaces__srv",  // message namespace
  "GetActiveAlarmInfo_Response",  // message name
  4,  // number of fields
  sizeof(motoros2_interfaces__srv__GetActiveAlarmInfo_Response),
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_member_array,  // message members
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_type_support_handle = {
  0,
  &motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Response)() {
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, AlarmInfo)();
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, ErrorInfo)();
  if (!motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__srv__GetActiveAlarmInfo_Response__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_members = {
  "motoros2_interfaces__srv",  // service namespace
  "GetActiveAlarmInfo",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Request_message_type_support_handle,
  NULL  // response message
  // motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_Response_message_type_support_handle
};

static rosidl_service_type_support_t motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_type_support_handle = {
  0,
  &motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo)() {
  if (!motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, GetActiveAlarmInfo_Response)()->data;
  }

  return &motoros2_interfaces__srv__detail__get_active_alarm_info__rosidl_typesupport_introspection_c__GetActiveAlarmInfo_service_type_support_handle;
}
