// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__BUILDER_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::GetActiveAlarmInfo_Request>()
{
  return ::motoros2_interfaces::srv::GetActiveAlarmInfo_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetActiveAlarmInfo_Response_errors
{
public:
  explicit Init_GetActiveAlarmInfo_Response_errors(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response errors(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response::_errors_type arg)
  {
    msg_.errors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response msg_;
};

class Init_GetActiveAlarmInfo_Response_alarms
{
public:
  explicit Init_GetActiveAlarmInfo_Response_alarms(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response & msg)
  : msg_(msg)
  {}
  Init_GetActiveAlarmInfo_Response_errors alarms(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response::_alarms_type arg)
  {
    msg_.alarms = std::move(arg);
    return Init_GetActiveAlarmInfo_Response_errors(msg_);
  }

private:
  ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response msg_;
};

class Init_GetActiveAlarmInfo_Response_result_message
{
public:
  explicit Init_GetActiveAlarmInfo_Response_result_message(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response & msg)
  : msg_(msg)
  {}
  Init_GetActiveAlarmInfo_Response_alarms result_message(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response::_result_message_type arg)
  {
    msg_.result_message = std::move(arg);
    return Init_GetActiveAlarmInfo_Response_alarms(msg_);
  }

private:
  ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response msg_;
};

class Init_GetActiveAlarmInfo_Response_result_code
{
public:
  Init_GetActiveAlarmInfo_Response_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetActiveAlarmInfo_Response_result_message result_code(::motoros2_interfaces::srv::GetActiveAlarmInfo_Response::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return Init_GetActiveAlarmInfo_Response_result_message(msg_);
  }

private:
  ::motoros2_interfaces::srv::GetActiveAlarmInfo_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::GetActiveAlarmInfo_Response>()
{
  return motoros2_interfaces::srv::builder::Init_GetActiveAlarmInfo_Response_result_code();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__GET_ACTIVE_ALARM_INFO__BUILDER_HPP_
