// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__industrial_msgs__msg__DeviceInfo __attribute__((deprecated))
#else
# define DEPRECATED__industrial_msgs__msg__DeviceInfo __declspec(deprecated)
#endif

namespace industrial_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DeviceInfo_
{
  using Type = DeviceInfo_<ContainerAllocator>;

  explicit DeviceInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->model = "";
      this->serial_number = "";
      this->hw_version = "";
      this->sw_version = "";
      this->address = "";
    }
  }

  explicit DeviceInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : model(_alloc),
    serial_number(_alloc),
    hw_version(_alloc),
    sw_version(_alloc),
    address(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->model = "";
      this->serial_number = "";
      this->hw_version = "";
      this->sw_version = "";
      this->address = "";
    }
  }

  // field types and members
  using _model_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _model_type model;
  using _serial_number_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _serial_number_type serial_number;
  using _hw_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _hw_version_type hw_version;
  using _sw_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _sw_version_type sw_version;
  using _address_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _address_type address;

  // setters for named parameter idiom
  Type & set__model(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->model = _arg;
    return *this;
  }
  Type & set__serial_number(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->serial_number = _arg;
    return *this;
  }
  Type & set__hw_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->hw_version = _arg;
    return *this;
  }
  Type & set__sw_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->sw_version = _arg;
    return *this;
  }
  Type & set__address(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->address = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    industrial_msgs::msg::DeviceInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const industrial_msgs::msg::DeviceInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::DeviceInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::DeviceInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__industrial_msgs__msg__DeviceInfo
    std::shared_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__industrial_msgs__msg__DeviceInfo
    std::shared_ptr<industrial_msgs::msg::DeviceInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DeviceInfo_ & other) const
  {
    if (this->model != other.model) {
      return false;
    }
    if (this->serial_number != other.serial_number) {
      return false;
    }
    if (this->hw_version != other.hw_version) {
      return false;
    }
    if (this->sw_version != other.sw_version) {
      return false;
    }
    if (this->address != other.address) {
      return false;
    }
    return true;
  }
  bool operator!=(const DeviceInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DeviceInfo_

// alias to use template instance with default allocator
using DeviceInfo =
  industrial_msgs::msg::DeviceInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEVICE_INFO__STRUCT_HPP_
