// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:srv/ReadGroupIO.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__READ_GROUP_IO__BUILDER_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__READ_GROUP_IO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/srv/detail/read_group_io__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_ReadGroupIO_Request_address
{
public:
  Init_ReadGroupIO_Request_address()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::motoros2_interfaces::srv::ReadGroupIO_Request address(::motoros2_interfaces::srv::ReadGroupIO_Request::_address_type arg)
  {
    msg_.address = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::ReadGroupIO_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::ReadGroupIO_Request>()
{
  return motoros2_interfaces::srv::builder::Init_ReadGroupIO_Request_address();
}

}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_ReadGroupIO_Response_value
{
public:
  explicit Init_ReadGroupIO_Response_value(::motoros2_interfaces::srv::ReadGroupIO_Response & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::ReadGroupIO_Response value(::motoros2_interfaces::srv::ReadGroupIO_Response::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::ReadGroupIO_Response msg_;
};

class Init_ReadGroupIO_Response_success
{
public:
  explicit Init_ReadGroupIO_Response_success(::motoros2_interfaces::srv::ReadGroupIO_Response & msg)
  : msg_(msg)
  {}
  Init_ReadGroupIO_Response_value success(::motoros2_interfaces::srv::ReadGroupIO_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ReadGroupIO_Response_value(msg_);
  }

private:
  ::motoros2_interfaces::srv::ReadGroupIO_Response msg_;
};

class Init_ReadGroupIO_Response_message
{
public:
  explicit Init_ReadGroupIO_Response_message(::motoros2_interfaces::srv::ReadGroupIO_Response & msg)
  : msg_(msg)
  {}
  Init_ReadGroupIO_Response_success message(::motoros2_interfaces::srv::ReadGroupIO_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ReadGroupIO_Response_success(msg_);
  }

private:
  ::motoros2_interfaces::srv::ReadGroupIO_Response msg_;
};

class Init_ReadGroupIO_Response_result_code
{
public:
  Init_ReadGroupIO_Response_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReadGroupIO_Response_message result_code(::motoros2_interfaces::srv::ReadGroupIO_Response::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return Init_ReadGroupIO_Response_message(msg_);
  }

private:
  ::motoros2_interfaces::srv::ReadGroupIO_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::ReadGroupIO_Response>()
{
  return motoros2_interfaces::srv::builder::Init_ReadGroupIO_Response_result_code();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__READ_GROUP_IO__BUILDER_HPP_
