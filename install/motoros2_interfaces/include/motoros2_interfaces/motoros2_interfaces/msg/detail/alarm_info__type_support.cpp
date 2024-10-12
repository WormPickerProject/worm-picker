// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "motoros2_interfaces/msg/detail/alarm_info__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace motoros2_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AlarmInfo_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motoros2_interfaces::msg::AlarmInfo(_init);
}

void AlarmInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motoros2_interfaces::msg::AlarmInfo *>(message_memory);
  typed_message->~AlarmInfo();
}

size_t size_function__AlarmInfo__help(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<motoros2_interfaces::msg::AlarmCauseRemedy> *>(untyped_member);
  return member->size();
}

const void * get_const_function__AlarmInfo__help(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<motoros2_interfaces::msg::AlarmCauseRemedy> *>(untyped_member);
  return &member[index];
}

void * get_function__AlarmInfo__help(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<motoros2_interfaces::msg::AlarmCauseRemedy> *>(untyped_member);
  return &member[index];
}

void fetch_function__AlarmInfo__help(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const motoros2_interfaces::msg::AlarmCauseRemedy *>(
    get_const_function__AlarmInfo__help(untyped_member, index));
  auto & value = *reinterpret_cast<motoros2_interfaces::msg::AlarmCauseRemedy *>(untyped_value);
  value = item;
}

void assign_function__AlarmInfo__help(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<motoros2_interfaces::msg::AlarmCauseRemedy *>(
    get_function__AlarmInfo__help(untyped_member, index));
  const auto & value = *reinterpret_cast<const motoros2_interfaces::msg::AlarmCauseRemedy *>(untyped_value);
  item = value;
}

void resize_function__AlarmInfo__help(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<motoros2_interfaces::msg::AlarmCauseRemedy> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AlarmInfo_message_member_array[7] = {
  {
    "number",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, number),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "sub_code",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, sub_code),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "datetime",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, datetime),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "contents",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, contents),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "description",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, description),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "help",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<motoros2_interfaces::msg::AlarmCauseRemedy>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motoros2_interfaces::msg::AlarmInfo, help),  // bytes offset in struct
    nullptr,  // default value
    size_function__AlarmInfo__help,  // size() function pointer
    get_const_function__AlarmInfo__help,  // get_const(index) function pointer
    get_function__AlarmInfo__help,  // get(index) function pointer
    fetch_function__AlarmInfo__help,  // fetch(index, &value) function pointer
    assign_function__AlarmInfo__help,  // assign(index, value) function pointer
    resize_function__AlarmInfo__help  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AlarmInfo_message_members = {
  "motoros2_interfaces::msg",  // message namespace
  "AlarmInfo",  // message name
  7,  // number of fields
  sizeof(motoros2_interfaces::msg::AlarmInfo),
  AlarmInfo_message_member_array,  // message members
  AlarmInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  AlarmInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AlarmInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AlarmInfo_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace motoros2_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::msg::AlarmInfo>()
{
  return &::motoros2_interfaces::msg::rosidl_typesupport_introspection_cpp::AlarmInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motoros2_interfaces, msg, AlarmInfo)() {
  return &::motoros2_interfaces::msg::rosidl_typesupport_introspection_cpp::AlarmInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
