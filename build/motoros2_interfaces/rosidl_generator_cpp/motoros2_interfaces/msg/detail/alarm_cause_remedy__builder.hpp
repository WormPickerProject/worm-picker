// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__BUILDER_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_AlarmCauseRemedy_remedy
{
public:
  explicit Init_AlarmCauseRemedy_remedy(::motoros2_interfaces::msg::AlarmCauseRemedy & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::msg::AlarmCauseRemedy remedy(::motoros2_interfaces::msg::AlarmCauseRemedy::_remedy_type arg)
  {
    msg_.remedy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmCauseRemedy msg_;
};

class Init_AlarmCauseRemedy_cause
{
public:
  Init_AlarmCauseRemedy_cause()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AlarmCauseRemedy_remedy cause(::motoros2_interfaces::msg::AlarmCauseRemedy::_cause_type arg)
  {
    msg_.cause = std::move(arg);
    return Init_AlarmCauseRemedy_remedy(msg_);
  }

private:
  ::motoros2_interfaces::msg::AlarmCauseRemedy msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::msg::AlarmCauseRemedy>()
{
  return motoros2_interfaces::msg::builder::Init_AlarmCauseRemedy_cause();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__BUILDER_HPP_
