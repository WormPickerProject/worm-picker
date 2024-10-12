// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__BUILDER_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "industrial_msgs/msg/detail/device_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace industrial_msgs
{

namespace msg
{

namespace builder
{

class Init_DeviceInfo_address
{
public:
  explicit Init_DeviceInfo_address(::industrial_msgs::msg::DeviceInfo & msg)
  : msg_(msg)
  {}
  ::industrial_msgs::msg::DeviceInfo address(::industrial_msgs::msg::DeviceInfo::_address_type arg)
  {
    msg_.address = std::move(arg);
    return std::move(msg_);
  }

private:
  ::industrial_msgs::msg::DeviceInfo msg_;
};

class Init_DeviceInfo_sw_version
{
public:
  explicit Init_DeviceInfo_sw_version(::industrial_msgs::msg::DeviceInfo & msg)
  : msg_(msg)
  {}
  Init_DeviceInfo_address sw_version(::industrial_msgs::msg::DeviceInfo::_sw_version_type arg)
  {
    msg_.sw_version = std::move(arg);
    return Init_DeviceInfo_address(msg_);
  }

private:
  ::industrial_msgs::msg::DeviceInfo msg_;
};

class Init_DeviceInfo_hw_version
{
public:
  explicit Init_DeviceInfo_hw_version(::industrial_msgs::msg::DeviceInfo & msg)
  : msg_(msg)
  {}
  Init_DeviceInfo_sw_version hw_version(::industrial_msgs::msg::DeviceInfo::_hw_version_type arg)
  {
    msg_.hw_version = std::move(arg);
    return Init_DeviceInfo_sw_version(msg_);
  }

private:
  ::industrial_msgs::msg::DeviceInfo msg_;
};

class Init_DeviceInfo_serial_number
{
public:
  explicit Init_DeviceInfo_serial_number(::industrial_msgs::msg::DeviceInfo & msg)
  : msg_(msg)
  {}
  Init_DeviceInfo_hw_version serial_number(::industrial_msgs::msg::DeviceInfo::_serial_number_type arg)
  {
    msg_.serial_number = std::move(arg);
    return Init_DeviceInfo_hw_version(msg_);
  }

private:
  ::industrial_msgs::msg::DeviceInfo msg_;
};

class Init_DeviceInfo_model
{
public:
  Init_DeviceInfo_model()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DeviceInfo_serial_number model(::industrial_msgs::msg::DeviceInfo::_model_type arg)
  {
    msg_.model = std::move(arg);
    return Init_DeviceInfo_serial_number(msg_);
  }

private:
  ::industrial_msgs::msg::DeviceInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::industrial_msgs::msg::DeviceInfo>()
{
  return industrial_msgs::msg::builder::Init_DeviceInfo_model();
}

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__BUILDER_HPP_
