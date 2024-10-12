// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from worm_picker_custom_msgs:srv/TaskCommand.idl
// generated code does not contain a copyright notice

#ifndef WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__BUILDER_HPP_
#define WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "worm_picker_custom_msgs/srv/detail/task_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace worm_picker_custom_msgs
{

namespace srv
{

namespace builder
{

class Init_TaskCommand_Request_command
{
public:
  Init_TaskCommand_Request_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::worm_picker_custom_msgs::srv::TaskCommand_Request command(::worm_picker_custom_msgs::srv::TaskCommand_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return std::move(msg_);
  }

private:
  ::worm_picker_custom_msgs::srv::TaskCommand_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::worm_picker_custom_msgs::srv::TaskCommand_Request>()
{
  return worm_picker_custom_msgs::srv::builder::Init_TaskCommand_Request_command();
}

}  // namespace worm_picker_custom_msgs


namespace worm_picker_custom_msgs
{

namespace srv
{

namespace builder
{

class Init_TaskCommand_Response_success
{
public:
  Init_TaskCommand_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::worm_picker_custom_msgs::srv::TaskCommand_Response success(::worm_picker_custom_msgs::srv::TaskCommand_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::worm_picker_custom_msgs::srv::TaskCommand_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::worm_picker_custom_msgs::srv::TaskCommand_Response>()
{
  return worm_picker_custom_msgs::srv::builder::Init_TaskCommand_Response_success();
}

}  // namespace worm_picker_custom_msgs

#endif  // WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__BUILDER_HPP_
