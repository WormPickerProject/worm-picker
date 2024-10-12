// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motoros2_interfaces:srv/QueueTrajPoint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motoros2_interfaces/srv/detail/queue_traj_point__rosidl_typesupport_introspection_c.h"
#include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motoros2_interfaces/srv/detail/queue_traj_point__functions.h"
#include "motoros2_interfaces/srv/detail/queue_traj_point__struct.h"


// Include directives for member types
// Member `joint_names`
#include "rosidl_runtime_c/string_functions.h"
// Member `point`
#include "trajectory_msgs/msg/joint_trajectory_point.h"
// Member `point`
#include "trajectory_msgs/msg/detail/joint_trajectory_point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__srv__QueueTrajPoint_Request__init(message_memory);
}

void motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_fini_function(void * message_memory)
{
  motoros2_interfaces__srv__QueueTrajPoint_Request__fini(message_memory);
}

size_t motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__size_function__QueueTrajPoint_Request__joint_names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_const_function__QueueTrajPoint_Request__joint_names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_function__QueueTrajPoint_Request__joint_names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__fetch_function__QueueTrajPoint_Request__joint_names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_const_function__QueueTrajPoint_Request__joint_names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__assign_function__QueueTrajPoint_Request__joint_names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_function__QueueTrajPoint_Request__joint_names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__resize_function__QueueTrajPoint_Request__joint_names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_member_array[2] = {
  {
    "joint_names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__QueueTrajPoint_Request, joint_names),  // bytes offset in struct
    NULL,  // default value
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__size_function__QueueTrajPoint_Request__joint_names,  // size() function pointer
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_const_function__QueueTrajPoint_Request__joint_names,  // get_const(index) function pointer
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__get_function__QueueTrajPoint_Request__joint_names,  // get(index) function pointer
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__fetch_function__QueueTrajPoint_Request__joint_names,  // fetch(index, &value) function pointer
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__assign_function__QueueTrajPoint_Request__joint_names,  // assign(index, value) function pointer
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__resize_function__QueueTrajPoint_Request__joint_names  // resize(index) function pointer
  },
  {
    "point",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__QueueTrajPoint_Request, point),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_members = {
  "motoros2_interfaces__srv",  // message namespace
  "QueueTrajPoint_Request",  // message name
  2,  // number of fields
  sizeof(motoros2_interfaces__srv__QueueTrajPoint_Request),
  motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_member_array,  // message members
  motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_type_support_handle = {
  0,
  &motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Request)() {
  motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, trajectory_msgs, msg, JointTrajectoryPoint)();
  if (!motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__srv__QueueTrajPoint_Request__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "motoros2_interfaces/srv/detail/queue_traj_point__rosidl_typesupport_introspection_c.h"
// already included above
// #include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "motoros2_interfaces/srv/detail/queue_traj_point__functions.h"
// already included above
// #include "motoros2_interfaces/srv/detail/queue_traj_point__struct.h"


// Include directives for member types
// Member `result_code`
#include "motoros2_interfaces/msg/queue_result_enum.h"
// Member `result_code`
#include "motoros2_interfaces/msg/detail/queue_result_enum__rosidl_typesupport_introspection_c.h"
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motoros2_interfaces__srv__QueueTrajPoint_Response__init(message_memory);
}

void motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_fini_function(void * message_memory)
{
  motoros2_interfaces__srv__QueueTrajPoint_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_member_array[2] = {
  {
    "result_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__QueueTrajPoint_Response, result_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces__srv__QueueTrajPoint_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_members = {
  "motoros2_interfaces__srv",  // message namespace
  "QueueTrajPoint_Response",  // message name
  2,  // number of fields
  sizeof(motoros2_interfaces__srv__QueueTrajPoint_Response),
  motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_member_array,  // message members
  motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_type_support_handle = {
  0,
  &motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Response)() {
  motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, msg, QueueResultEnum)();
  if (!motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motoros2_interfaces__srv__QueueTrajPoint_Response__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "motoros2_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "motoros2_interfaces/srv/detail/queue_traj_point__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_members = {
  "motoros2_interfaces__srv",  // service namespace
  "QueueTrajPoint",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_Request_message_type_support_handle,
  NULL  // response message
  // motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_Response_message_type_support_handle
};

static rosidl_service_type_support_t motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_type_support_handle = {
  0,
  &motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motoros2_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint)() {
  if (!motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_type_support_handle.typesupport_identifier) {
    motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motoros2_interfaces, srv, QueueTrajPoint_Response)()->data;
  }

  return &motoros2_interfaces__srv__detail__queue_traj_point__rosidl_typesupport_introspection_c__QueueTrajPoint_service_type_support_handle;
}
