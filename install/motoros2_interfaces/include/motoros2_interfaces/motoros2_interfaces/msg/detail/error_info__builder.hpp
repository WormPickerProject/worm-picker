// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:msg/ErrorInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__BUILDER_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/msg/detail/error_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_ErrorInfo_datetime
{
public:
  explicit Init_ErrorInfo_datetime(::motoros2_interfaces::msg::ErrorInfo & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::msg::ErrorInfo datetime(::motoros2_interfaces::msg::ErrorInfo::_datetime_type arg)
  {
    msg_.datetime = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::msg::ErrorInfo msg_;
};

class Init_ErrorInfo_sub_code
{
public:
  explicit Init_ErrorInfo_sub_code(::motoros2_interfaces::msg::ErrorInfo & msg)
  : msg_(msg)
  {}
  Init_ErrorInfo_datetime sub_code(::motoros2_interfaces::msg::ErrorInfo::_sub_code_type arg)
  {
    msg_.sub_code = std::move(arg);
    return Init_ErrorInfo_datetime(msg_);
  }

private:
  ::motoros2_interfaces::msg::ErrorInfo msg_;
};

class Init_ErrorInfo_message
{
public:
  explicit Init_ErrorInfo_message(::motoros2_interfaces::msg::ErrorInfo & msg)
  : msg_(msg)
  {}
  Init_ErrorInfo_sub_code message(::motoros2_interfaces::msg::ErrorInfo::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ErrorInfo_sub_code(msg_);
  }

private:
  ::motoros2_interfaces::msg::ErrorInfo msg_;
};

class Init_ErrorInfo_number
{
public:
  Init_ErrorInfo_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ErrorInfo_message number(::motoros2_interfaces::msg::ErrorInfo::_number_type arg)
  {
    msg_.number = std::move(arg);
    return Init_ErrorInfo_message(msg_);
  }

private:
  ::motoros2_interfaces::msg::ErrorInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::msg::ErrorInfo>()
{
  return motoros2_interfaces::msg::builder::Init_ErrorInfo_number();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__BUILDER_HPP_
