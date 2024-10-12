// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "industrial_msgs/msg/detail/robot_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace industrial_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotStatus_error_codes
{
public:
  explicit Init_RobotStatus_error_codes(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  ::industrial_msgs::msg::RobotStatus error_codes(::industrial_msgs::msg::RobotStatus::_error_codes_type arg)
  {
    msg_.error_codes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_in_error
{
public:
  explicit Init_RobotStatus_in_error(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_error_codes in_error(::industrial_msgs::msg::RobotStatus::_in_error_type arg)
  {
    msg_.in_error = std::move(arg);
    return Init_RobotStatus_error_codes(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_in_motion
{
public:
  explicit Init_RobotStatus_in_motion(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_in_error in_motion(::industrial_msgs::msg::RobotStatus::_in_motion_type arg)
  {
    msg_.in_motion = std::move(arg);
    return Init_RobotStatus_in_error(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_motion_possible
{
public:
  explicit Init_RobotStatus_motion_possible(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_in_motion motion_possible(::industrial_msgs::msg::RobotStatus::_motion_possible_type arg)
  {
    msg_.motion_possible = std::move(arg);
    return Init_RobotStatus_in_motion(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_drives_powered
{
public:
  explicit Init_RobotStatus_drives_powered(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_motion_possible drives_powered(::industrial_msgs::msg::RobotStatus::_drives_powered_type arg)
  {
    msg_.drives_powered = std::move(arg);
    return Init_RobotStatus_motion_possible(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_e_stopped
{
public:
  explicit Init_RobotStatus_e_stopped(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_drives_powered e_stopped(::industrial_msgs::msg::RobotStatus::_e_stopped_type arg)
  {
    msg_.e_stopped = std::move(arg);
    return Init_RobotStatus_drives_powered(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_mode
{
public:
  explicit Init_RobotStatus_mode(::industrial_msgs::msg::RobotStatus & msg)
  : msg_(msg)
  {}
  Init_RobotStatus_e_stopped mode(::industrial_msgs::msg::RobotStatus::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_RobotStatus_e_stopped(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

class Init_RobotStatus_header
{
public:
  Init_RobotStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotStatus_mode header(::industrial_msgs::msg::RobotStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RobotStatus_mode(msg_);
  }

private:
  ::industrial_msgs::msg::RobotStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::industrial_msgs::msg::RobotStatus>()
{
  return industrial_msgs::msg::builder::Init_RobotStatus_header();
}

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__BUILDER_HPP_
