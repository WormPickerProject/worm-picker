// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:srv/SelectMotionTool.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__BUILDER_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/srv/detail/select_motion_tool__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_SelectMotionTool_Request_tool_number
{
public:
  explicit Init_SelectMotionTool_Request_tool_number(::motoros2_interfaces::srv::SelectMotionTool_Request & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::SelectMotionTool_Request tool_number(::motoros2_interfaces::srv::SelectMotionTool_Request::_tool_number_type arg)
  {
    msg_.tool_number = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::SelectMotionTool_Request msg_;
};

class Init_SelectMotionTool_Request_group_number
{
public:
  Init_SelectMotionTool_Request_group_number()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SelectMotionTool_Request_tool_number group_number(::motoros2_interfaces::srv::SelectMotionTool_Request::_group_number_type arg)
  {
    msg_.group_number = std::move(arg);
    return Init_SelectMotionTool_Request_tool_number(msg_);
  }

private:
  ::motoros2_interfaces::srv::SelectMotionTool_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::SelectMotionTool_Request>()
{
  return motoros2_interfaces::srv::builder::Init_SelectMotionTool_Request_group_number();
}

}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_SelectMotionTool_Response_success
{
public:
  explicit Init_SelectMotionTool_Response_success(::motoros2_interfaces::srv::SelectMotionTool_Response & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::SelectMotionTool_Response success(::motoros2_interfaces::srv::SelectMotionTool_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::SelectMotionTool_Response msg_;
};

class Init_SelectMotionTool_Response_message
{
public:
  explicit Init_SelectMotionTool_Response_message(::motoros2_interfaces::srv::SelectMotionTool_Response & msg)
  : msg_(msg)
  {}
  Init_SelectMotionTool_Response_success message(::motoros2_interfaces::srv::SelectMotionTool_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_SelectMotionTool_Response_success(msg_);
  }

private:
  ::motoros2_interfaces::srv::SelectMotionTool_Response msg_;
};

class Init_SelectMotionTool_Response_result_code
{
public:
  Init_SelectMotionTool_Response_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SelectMotionTool_Response_message result_code(::motoros2_interfaces::srv::SelectMotionTool_Response::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return Init_SelectMotionTool_Response_message(msg_);
  }

private:
  ::motoros2_interfaces::srv::SelectMotionTool_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::SelectMotionTool_Response>()
{
  return motoros2_interfaces::srv::builder::Init_SelectMotionTool_Response_result_code();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__SELECT_MOTION_TOOL__BUILDER_HPP_
