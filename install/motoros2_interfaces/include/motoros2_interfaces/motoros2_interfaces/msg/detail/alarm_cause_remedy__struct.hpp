// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__AlarmCauseRemedy __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__AlarmCauseRemedy __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AlarmCauseRemedy_
{
  using Type = AlarmCauseRemedy_<ContainerAllocator>;

  explicit AlarmCauseRemedy_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cause = "";
      this->remedy = "";
    }
  }

  explicit AlarmCauseRemedy_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : cause(_alloc),
    remedy(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cause = "";
      this->remedy = "";
    }
  }

  // field types and members
  using _cause_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _cause_type cause;
  using _remedy_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _remedy_type remedy;

  // setters for named parameter idiom
  Type & set__cause(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->cause = _arg;
    return *this;
  }
  Type & set__remedy(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->remedy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__AlarmCauseRemedy
    std::shared_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__AlarmCauseRemedy
    std::shared_ptr<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AlarmCauseRemedy_ & other) const
  {
    if (this->cause != other.cause) {
      return false;
    }
    if (this->remedy != other.remedy) {
      return false;
    }
    return true;
  }
  bool operator!=(const AlarmCauseRemedy_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AlarmCauseRemedy_

// alias to use template instance with default allocator
using AlarmCauseRemedy =
  motoros2_interfaces::msg::AlarmCauseRemedy_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_CAUSE_REMEDY__STRUCT_HPP_
