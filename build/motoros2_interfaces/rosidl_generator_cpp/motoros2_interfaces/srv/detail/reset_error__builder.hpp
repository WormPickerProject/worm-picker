// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motoros2_interfaces:srv/ResetError.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__RESET_ERROR__BUILDER_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__RESET_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motoros2_interfaces/srv/detail/reset_error__struct.hpp"
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
auto build<::motoros2_interfaces::srv::ResetError_Request>()
{
  return ::motoros2_interfaces::srv::ResetError_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace builder
{

class Init_ResetError_Response_message
{
public:
  explicit Init_ResetError_Response_message(::motoros2_interfaces::srv::ResetError_Response & msg)
  : msg_(msg)
  {}
  ::motoros2_interfaces::srv::ResetError_Response message(::motoros2_interfaces::srv::ResetError_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motoros2_interfaces::srv::ResetError_Response msg_;
};

class Init_ResetError_Response_result_code
{
public:
  Init_ResetError_Response_result_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ResetError_Response_message result_code(::motoros2_interfaces::srv::ResetError_Response::_result_code_type arg)
  {
    msg_.result_code = std::move(arg);
    return Init_ResetError_Response_message(msg_);
  }

private:
  ::motoros2_interfaces::srv::ResetError_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::motoros2_interfaces::srv::ResetError_Response>()
{
  return motoros2_interfaces::srv::builder::Init_ResetError_Response_result_code();
}

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__RESET_ERROR__BUILDER_HPP_
