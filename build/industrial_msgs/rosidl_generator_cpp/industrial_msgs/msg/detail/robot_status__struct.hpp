// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'mode'
#include "industrial_msgs/msg/detail/robot_mode__struct.hpp"
// Member 'e_stopped'
// Member 'drives_powered'
// Member 'motion_possible'
// Member 'in_motion'
// Member 'in_error'
#include "industrial_msgs/msg/detail/tri_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__industrial_msgs__msg__RobotStatus __attribute__((deprecated))
#else
# define DEPRECATED__industrial_msgs__msg__RobotStatus __declspec(deprecated)
#endif

namespace industrial_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotStatus_
{
  using Type = RobotStatus_<ContainerAllocator>;

  explicit RobotStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    mode(_init),
    e_stopped(_init),
    drives_powered(_init),
    motion_possible(_init),
    in_motion(_init),
    in_error(_init)
  {
    (void)_init;
  }

  explicit RobotStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    mode(_alloc, _init),
    e_stopped(_alloc, _init),
    drives_powered(_alloc, _init),
    motion_possible(_alloc, _init),
    in_motion(_alloc, _init),
    in_error(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _mode_type =
    industrial_msgs::msg::RobotMode_<ContainerAllocator>;
  _mode_type mode;
  using _e_stopped_type =
    industrial_msgs::msg::TriState_<ContainerAllocator>;
  _e_stopped_type e_stopped;
  using _drives_powered_type =
    industrial_msgs::msg::TriState_<ContainerAllocator>;
  _drives_powered_type drives_powered;
  using _motion_possible_type =
    industrial_msgs::msg::TriState_<ContainerAllocator>;
  _motion_possible_type motion_possible;
  using _in_motion_type =
    industrial_msgs::msg::TriState_<ContainerAllocator>;
  _in_motion_type in_motion;
  using _in_error_type =
    industrial_msgs::msg::TriState_<ContainerAllocator>;
  _in_error_type in_error;
  using _error_codes_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _error_codes_type error_codes;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__mode(
    const industrial_msgs::msg::RobotMode_<ContainerAllocator> & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__e_stopped(
    const industrial_msgs::msg::TriState_<ContainerAllocator> & _arg)
  {
    this->e_stopped = _arg;
    return *this;
  }
  Type & set__drives_powered(
    const industrial_msgs::msg::TriState_<ContainerAllocator> & _arg)
  {
    this->drives_powered = _arg;
    return *this;
  }
  Type & set__motion_possible(
    const industrial_msgs::msg::TriState_<ContainerAllocator> & _arg)
  {
    this->motion_possible = _arg;
    return *this;
  }
  Type & set__in_motion(
    const industrial_msgs::msg::TriState_<ContainerAllocator> & _arg)
  {
    this->in_motion = _arg;
    return *this;
  }
  Type & set__in_error(
    const industrial_msgs::msg::TriState_<ContainerAllocator> & _arg)
  {
    this->in_error = _arg;
    return *this;
  }
  Type & set__error_codes(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->error_codes = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    industrial_msgs::msg::RobotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const industrial_msgs::msg::RobotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::RobotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::RobotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__industrial_msgs__msg__RobotStatus
    std::shared_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__industrial_msgs__msg__RobotStatus
    std::shared_ptr<industrial_msgs::msg::RobotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->e_stopped != other.e_stopped) {
      return false;
    }
    if (this->drives_powered != other.drives_powered) {
      return false;
    }
    if (this->motion_possible != other.motion_possible) {
      return false;
    }
    if (this->in_motion != other.in_motion) {
      return false;
    }
    if (this->in_error != other.in_error) {
      return false;
    }
    if (this->error_codes != other.error_codes) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotStatus_

// alias to use template instance with default allocator
using RobotStatus =
  industrial_msgs::msg::RobotStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__ROBOT_STATUS__STRUCT_HPP_
