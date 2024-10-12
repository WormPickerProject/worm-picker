// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/MotionReadyEnum.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__MotionReadyEnum __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__MotionReadyEnum __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotionReadyEnum_
{
  using Type = MotionReadyEnum_<ContainerAllocator>;

  explicit MotionReadyEnum_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit MotionReadyEnum_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  // field types and members
  using _value_type =
    uint16_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint16_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t READY =
    1u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> READY_STR;
  static constexpr uint16_t NOT_READY_UNSPECIFIED =
    100u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_UNSPECIFIED_STR;
  static constexpr uint16_t NOT_READY_ALARM =
    101u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_ALARM_STR;
  static constexpr uint16_t NOT_READY_ERROR =
    102u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_ERROR_STR;
  static constexpr uint16_t NOT_READY_ESTOP =
    103u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_ESTOP_STR;
  static constexpr uint16_t NOT_READY_NOT_PLAY =
    104u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_NOT_PLAY_STR;
  static constexpr uint16_t NOT_READY_NOT_REMOTE =
    105u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_NOT_REMOTE_STR;
  static constexpr uint16_t NOT_READY_SERVO_OFF =
    106u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_SERVO_OFF_STR;
  static constexpr uint16_t NOT_READY_HOLD =
    107u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_HOLD_STR;
  static constexpr uint16_t NOT_READY_JOB_NOT_STARTED =
    108u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_JOB_NOT_STARTED_STR;
  static constexpr uint16_t NOT_READY_NOT_ON_WAIT_CMD =
    109u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_NOT_ON_WAIT_CMD_STR;
  static constexpr uint16_t NOT_READY_PFL_ACTIVE =
    111u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_PFL_ACTIVE_STR;
  static constexpr uint16_t NOT_READY_INC_MOVE_ERROR =
    112u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_INC_MOVE_ERROR_STR;
  static constexpr uint16_t NOT_READY_OTHER_PROGRAM_RUNNING =
    113u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_OTHER_PROGRAM_RUNNING_STR;
  static constexpr uint16_t NOT_READY_OTHER_TRAJ_MODE_ACTIVE =
    114u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR;
  static constexpr uint16_t NOT_READY_NOT_CONT_CYCLE_MODE =
    115u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_NOT_CONT_CYCLE_MODE_STR;
  static constexpr uint16_t NOT_READY_MAJOR_ALARM =
    116u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_MAJOR_ALARM_STR;
  static constexpr uint16_t NOT_READY_ECO_MODE =
    117u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_ECO_MODE_STR;
  static constexpr uint16_t NOT_READY_SERVO_ON_TIMEOUT =
    118u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> NOT_READY_SERVO_ON_TIMEOUT_STR;

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__MotionReadyEnum
    std::shared_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__MotionReadyEnum
    std::shared_ptr<motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotionReadyEnum_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotionReadyEnum_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotionReadyEnum_

// alias to use template instance with default allocator
using MotionReadyEnum =
  motoros2_interfaces::msg::MotionReadyEnum_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::READY;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::READY_STR = "Ready";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_UNSPECIFIED;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_UNSPECIFIED_STR = "Unspecified";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_ALARM;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_ALARM_STR = "The controller has an active Alarm";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_ERROR;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_ERROR_STR = "The controller has an active Error";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_ESTOP;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_ESTOP_STR = "The controller is in E-Stop";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_PLAY;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_PLAY_STR = "The teach pendant must not be in TEACH mode";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_REMOTE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_REMOTE_STR = "The teach pendant must be in REMOTE mode";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_SERVO_OFF;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_SERVO_OFF_STR = "Servo power is OFF. Please call start_traj_mode or start_point_queue_mode service";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_HOLD;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_HOLD_STR = "The controller is in HOLD";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_JOB_NOT_STARTED;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_JOB_NOT_STARTED_STR = "The INIT_ROS job has not started. Please call start_traj_mode or start_point_queue_mode service";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_ON_WAIT_CMD;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_ON_WAIT_CMD_STR = "INFORM job is not on a WAIT command. Check the format of INIT_ROS";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_PFL_ACTIVE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_PFL_ACTIVE_STR = "A PFL event has occurred. Please return the robot to a safe state";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_INC_MOVE_ERROR;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_INC_MOVE_ERROR_STR = "The controller is in an error state. Please call reset_error to attempt to clear the error";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_OTHER_PROGRAM_RUNNING;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_OTHER_PROGRAM_RUNNING_STR = "Controller is running another job";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_OTHER_TRAJ_MODE_ACTIVE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR = "Another trajectory mode is already active. Please call stop_traj_mode service";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_CONT_CYCLE_MODE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_NOT_CONT_CYCLE_MODE_STR = "AUTO cycle mode not set. Please set the cycle mode to AUTO";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_MAJOR_ALARM;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_MAJOR_ALARM_STR = "Major Alarms can't be reset. Please check the teach pendant";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_ECO_MODE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_ECO_MODE_STR = "Couldn't disable eco mode";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t MotionReadyEnum_<ContainerAllocator>::NOT_READY_SERVO_ON_TIMEOUT;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
MotionReadyEnum_<ContainerAllocator>::NOT_READY_SERVO_ON_TIMEOUT_STR = "Timed out while waiting for servo on";

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__MOTION_READY_ENUM__STRUCT_HPP_
