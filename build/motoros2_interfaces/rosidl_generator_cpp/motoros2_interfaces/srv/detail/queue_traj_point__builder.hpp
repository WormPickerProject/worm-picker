// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:srv/QueueTrajPoint.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__BUILDER_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/srv/detail/queue_traj_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_QueueTrajPoint_Request_point
{
public:
  explicit Init_QueueTrajPoint_Request_point(::motoros2_interfaces::srv::QueueTrajPoint_Request & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::QueueTrajPoint_Request point(::motoros2_interfaces::srv::QueueTrajPoint_Request::_point_type arg)
  {
    msg_.point = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::QueueTrajPoint_Request msg_;
};

class Init_QueueTrajPoint_Request_joint_names
{
public:
  Init_QueueTrajPoint_Request_joint_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_QueueTrajPoint_Request_point joint_names(::motoros2_interfaces::srv::QueueTrajPoint_Request::_joint_names_type arg)
  {
    msg_.joint_names = std::move(arg);
    return Init_QueueTrajPoint_Request_point(msg_);
  }

private:
  ::motoros2_interfaces::srv::QueueTrajPoint_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::QueueTrajPoint_Request>()
{
  return motoros2_interfaces::srv::builder::Init_QueueTrajPoint_Request_joint_names();
}

}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_QueueTrajPoint_Response_message
{
public:
  explicit Init_QueueTrajPoint_Response_message(::motoros2_interfaces::srv::QueueTrajPoint_Response & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::QueueTrajPoint_Response message(::motoros2_interfaces::srv::QueueTrajPoint_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::QueueTrajPoint_Response msg_;
};

class Init_QueueTrajPoint_Response_result_code
{
public:
  Init_QueueTrajPoint_Response_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_QueueTrajPoint_Response_message result_code(::motoros2_interfaces::srv::QueueTrajPoint_Response::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return Init_QueueTrajPoint_Response_message(msg_);
  }

private:
  ::motoros2_interfaces::srv::QueueTrajPoint_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::QueueTrajPoint_Response>()
{
  return motoros2_interfaces::srv::builder::Init_QueueTrajPoint_Response_result_code();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__QUEUE_TRAJ_POINT__BUILDER_HPP_
