// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:msg/SelectionResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__BUILDER_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/msg/detail/selection_result_codes__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motoros2_interfaces
{

namespace msg
{

namespace builder
{

class Init_SelectionResultCodes_value
{
public:
  Init_SelectionResultCodes_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::motoros2_interfaces::msg::SelectionResultCodes value(::motoros2_interfaces::msg::SelectionResultCodes::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::msg::SelectionResultCodes msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::msg::SelectionResultCodes>()
{
  return motoros2_interfaces::msg::builder::Init_SelectionResultCodes_value();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__BUILDER_HPP_
