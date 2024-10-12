// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from industrial_msgs:msg/TriState.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__BUILDER_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "industrial_msgs/msg/detail/tri_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace industrial_msgs
{

namespace msg
{

namespace builder
{

class Init_TriState_val
{
public:
  Init_TriState_val()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::industrial_msgs::msg::TriState val(::industrial_msgs::msg::TriState::_val_type arg)
  {
    msg_.val = std::move(arg);
    return std::move(msg_);
  }

private:
  ::industrial_msgs::msg::TriState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::industrial_msgs::msg::TriState>()
{
  return industrial_msgs::msg::builder::Init_TriState_val();
}

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__TRI_STATE__BUILDER_HPP_
