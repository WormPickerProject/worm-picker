// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__BUILDER_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/msg/detail/alarm_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_AlarmInfo_help
{
public:
  explicit Init_AlarmInfo_help(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::msg::AlarmInfo help(::motoros2_interfaces::msg::AlarmInfo::_help_type arg)
  {
    msg_.help = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_description
{
public:
  explicit Init_AlarmInfo_description(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  Init_AlarmInfo_help description(::motoros2_interfaces::msg::AlarmInfo::_description_type arg)
  {
    msg_.description = std::move(arg);
    return Init_AlarmInfo_help(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_contents
{
public:
  explicit Init_AlarmInfo_contents(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  Init_AlarmInfo_description contents(::motoros2_interfaces::msg::AlarmInfo::_contents_type arg)
  {
    msg_.contents = std::move(arg);
    return Init_AlarmInfo_description(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_datetime
{
public:
  explicit Init_AlarmInfo_datetime(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  Init_AlarmInfo_contents datetime(::motoros2_interfaces::msg::AlarmInfo::_datetime_type arg)
  {
    msg_.datetime = std::move(arg);
    return Init_AlarmInfo_contents(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_sub_code
{
public:
  explicit Init_AlarmInfo_sub_code(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  Init_AlarmInfo_datetime sub_code(::motoros2_interfaces::msg::AlarmInfo::_sub_code_type arg)
  {
    msg_.sub_code = std::move(arg);
    return Init_AlarmInfo_datetime(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_message
{
public:
  explicit Init_AlarmInfo_message(::motoros2_interfaces::msg::AlarmInfo & msg)
  : msg_(msg)
  {}
  Init_AlarmInfo_sub_code message(::motoros2_interfaces::msg::AlarmInfo::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_AlarmInfo_sub_code(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

class Init_AlarmInfo_number
{
public:
  Init_AlarmInfo_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AlarmInfo_message number(::motoros2_interfaces::msg::AlarmInfo::_number_type arg)
  {
    msg_.number = std::move(arg);
    return Init_AlarmInfo_message(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::msg::AlarmInfo>()
{
  return motoros2_interfaces::msg::builder::Init_AlarmInfo_number();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__BUILDER_HPP_
