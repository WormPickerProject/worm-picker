// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:msg/MotionReadyEnum.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__BUILDER_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/msg/detail/motion_ready_enum__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotionReadyEnum_value
{
public:
  Init_MotionReadyEnum_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::motoros2_interfaces::msg::MotionReadyEnum value(::motoros2_interfaces::msg::MotionReadyEnum::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::msg::MotionReadyEnum msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::msg::MotionReadyEnum>()
{
  return motoros2_interfaces::msg::builder::Init_MotionReadyEnum_value();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__BUILDER_HPP_
