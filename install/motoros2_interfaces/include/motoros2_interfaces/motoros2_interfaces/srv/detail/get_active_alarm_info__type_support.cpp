// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace motoros2_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetActiveAlarmInfo_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motoros2_interfaces::srv::GetActiveAlarmInfo_Request(_init);
}

void GetActiveAlarmInfo_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motoros2_interfaces::srv::GetActiveAlarmInfo_Request *>(message_memory);
  typed_message->~GetActiveAlarmInfo_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetActiveAlarmInfo_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::srv::GetActiveAlarmInfo_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetActiveAlarmInfo_Request_message_members = {
  "motoros2_interfaces::srv",  // message namespace
  "GetActiveAlarmInfo_Request",  // message name
  1,  // number of fields
  sizeof(motoros2_interfaces::srv::GetActiveAlarmInfo_Request),
  GetActiveAlarmInfo_Request_message_member_array,  // message members
  GetActiveAlarmInfo_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetActiveAlarmInfo_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetActiveAlarmInfo_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetActiveAlarmInfo_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace motoros2_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::srv::GetActiveAlarmInfo_Request>()
{
  return &::motoros2_interfaces::srv::rosidl_typesupport_introspection_cpp::GetActiveAlarmInfo_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motoros2_interfaces, srv, GetActiveAlarmInfo_Request)() {
  return &::motoros2_interfaces::srv::rosidl_typesupport_introspection_cpp::GetActiveAlarmInfo_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace motoros2_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetActiveAlarmInfo_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motoros2_interfaces::srv::GetActiveAlarmInfo_Response(_init);
}

void GetActiveAlarmInfo_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motoros2_interfaces::srv::GetActiveAlarmInfo_Response *>(message_memory);
  typed_message->~GetActiveAlarmInfo_Response();
}

size_t size_function__GetActiveAlarmInfo_Response__alarms(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<motoros2_interfaces::msg::AlarmInfo> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetActiveAlarmInfo_Response__alarms(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<motoros2_interfaces::msg::AlarmInfo> *>(untyped_member);
  return &member[index];
}

void * get_function__GetActiveAlarmInfo_Response__alarms(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<motoros2_interfaces::msg::AlarmInfo> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetActiveAlarmInfo_Response__alarms(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const motoros2_interfaces::msg::AlarmInfo *>(
    get_const_function__GetActiveAlarmInfo_Response__alarms(untyped_member, index));
  auto & value = *reinterpret_cast<motoros2_interfaces::msg::AlarmInfo *>(untyped_value);
  value = item;
}

void assign_function__GetActiveAlarmInfo_Response__alarms(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<motoros2_interfaces::msg::AlarmInfo *>(
    get_function__GetActiveAlarmInfo_Response__alarms(untyped_member, index));
  const auto & value = *reinterpret_cast<const motoros2_interfaces::msg::AlarmInfo *>(untyped_value);
  item = value;
}

void resize_function__GetActiveAlarmInfo_Response__alarms(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<motoros2_interfaces::msg::AlarmInfo> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetActiveAlarmInfo_Response__errors(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<motoros2_interfaces::msg::ErrorInfo> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetActiveAlarmInfo_Response__errors(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<motoros2_interfaces::msg::ErrorInfo> *>(untyped_member);
  return &member[index];
}

void * get_function__GetActiveAlarmInfo_Response__errors(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<motoros2_interfaces::msg::ErrorInfo> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetActiveAlarmInfo_Response__errors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const motoros2_interfaces::msg::ErrorInfo *>(
    get_const_function__GetActiveAlarmInfo_Response__errors(untyped_member, index));
  auto & value = *reinterpret_cast<motoros2_interfaces::msg::ErrorInfo *>(untyped_value);
  value = item;
}

void assign_function__GetActiveAlarmInfo_Response__errors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<motoros2_interfaces::msg::ErrorInfo *>(
    get_function__GetActiveAlarmInfo_Response__errors(untyped_member, index));
  const auto & value = *reinterpret_cast<const motoros2_interfaces::msg::ErrorInfo *>(untyped_value);
  item = value;
}

void resize_function__GetActiveAlarmInfo_Response__errors(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<motoros2_interfaces::msg::ErrorInfo> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetActiveAlarmInfo_Response_message_member_array[4] = {
  {
    "result_code",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::srv::GetActiveAlarmInfo_Response, result_code),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "result_message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::srv::GetActiveAlarmInfo_Response, result_message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "alarms",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<motoros2_interfaces::msg::AlarmInfo>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::srv::GetActiveAlarmInfo_Response, alarms),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetActiveAlarmInfo_Response__alarms,  // size() function pointer
    get_const_function__GetActiveAlarmInfo_Response__alarms,  // get_const(index) function pointer
    get_function__GetActiveAlarmInfo_Response__alarms,  // get(index) function pointer
    fetch_function__GetActiveAlarmInfo_Response__alarms,  // fetch(index, &value) function pointer
    assign_function__GetActiveAlarmInfo_Response__alarms,  // assign(index, value) function pointer
    resize_function__GetActiveAlarmInfo_Response__alarms  // resize(index) function pointer
  },
  {
    "errors",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<motoros2_interfaces::msg::ErrorInfo>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::srv::GetActiveAlarmInfo_Response, errors),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetActiveAlarmInfo_Response__errors,  // size() function pointer
    get_const_function__GetActiveAlarmInfo_Response__errors,  // get_const(index) function pointer
    get_function__GetActiveAlarmInfo_Response__errors,  // get(index) function pointer
    fetch_function__GetActiveAlarmInfo_Response__errors,  // fetch(index, &value) function pointer
    assign_function__GetActiveAlarmInfo_Response__errors,  // assign(index, value) function pointer
    resize_function__GetActiveAlarmInfo_Response__errors  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetActiveAlarmInfo_Response_message_members = {
  "motoros2_interfaces::srv",  // message namespace
  "GetActiveAlarmInfo_Response",  // message name
  4,  // number of fields
  sizeof(motoros2_interfaces::srv::GetActiveAlarmInfo_Response),
  GetActiveAlarmInfo_Response_message_member_array,  // message members
  GetActiveAlarmInfo_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetActiveAlarmInfo_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetActiveAlarmInfo_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetActiveAlarmInfo_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace motoros2_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::srv::GetActiveAlarmInfo_Response>()
{
  return &::motoros2_interfaces::srv::rosidl_typesupport_introspection_cpp::GetActiveAlarmInfo_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motoros2_interfaces, srv, GetActiveAlarmInfo_Response)() {
  return &::motoros2_interfaces::srv::rosidl_typesupport_introspection_cpp::GetActiveAlarmInfo_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace motoros2_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetActiveAlarmInfo_service_members = {
  "motoros2_interfaces::srv",  // service namespace
  "GetActiveAlarmInfo",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<motoros2_interfaces::srv::GetActiveAlarmInfo>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t GetActiveAlarmInfo_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetActiveAlarmInfo_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace motoros2_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<motoros2_interfaces::srv::GetActiveAlarmInfo>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::motoros2_interfaces::srv::rosidl_typesupport_introspection_cpp::GetActiveAlarmInfo_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::motoros2_interfaces::srv::GetActiveAlarmInfo_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motoros2_interfaces, srv, GetActiveAlarmInfo)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<motoros2_interfaces::srv::GetActiveAlarmInfo>();
}

#ifdef __cplusplus
}
#endif
