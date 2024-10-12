// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from industrial_msgs:msg/RobotMode.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__industrial_msgs__msg__RobotMode __attribute__((deprecated))
#else
# define DEPRECATED__industrial_msgs__msg__RobotMode __declspec(deprecated)
#endif

namespace industrial_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotMode_
{
  using Type = RobotMode_<ContainerAllocator>;

  explicit RobotMode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->val = 0;
    }
  }

  explicit RobotMode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->val = 0;
    }
  }

  // field types and members
  using _val_type =
    int8_t;
  _val_type val;

  // setters for named parameter idiom
  Type & set__val(
    const int8_t & _arg)
  {
    this->val = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int8_t UNKNOWN =
    -1;
  static constexpr int8_t MANUAL =
    1;
  static constexpr int8_t AUTO =
    2;

  // pointer types
  using RawPtr =
    industrial_msgs::msg::RobotMode_<ContainerAllocator> *;
  using ConstRawPtr =
    const industrial_msgs::msg::RobotMode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::RobotMode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::RobotMode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__industrial_msgs__msg__RobotMode
    std::shared_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__industrial_msgs__msg__RobotMode
    std::shared_ptr<industrial_msgs::msg::RobotMode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotMode_ & other) const
  {
    if (this->val != other.val) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotMode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotMode_

// alias to use template instance with default allocator
using RobotMode =
  industrial_msgs::msg::RobotMode_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t RobotMode_<ContainerAllocator>::UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t RobotMode_<ContainerAllocator>::MANUAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t RobotMode_<ContainerAllocator>::AUTO;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_MODE__STRUCT_HPP_
