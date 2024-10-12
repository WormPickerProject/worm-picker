// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/QueueResultEnum.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__QueueResultEnum __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__QueueResultEnum __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct QueueResultEnum_
{
  using Type = QueueResultEnum_<ContainerAllocator>;

  explicit QueueResultEnum_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit QueueResultEnum_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    uint8_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint8_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t SUCCESS =
    1u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> SUCCESS_STR;
  static constexpr uint8_t WRONG_MODE =
    2u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> WRONG_MODE_STR;
  static constexpr uint8_t INIT_FAILURE =
    3u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> INIT_FAILURE_STR;
  static constexpr uint8_t BUSY =
    4u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> BUSY_STR;
  static constexpr uint8_t INVALID_JOINT_LIST =
    5u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> INVALID_JOINT_LIST_STR;
  static constexpr uint8_t UNABLE_TO_PROCESS_POINT =
    6u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> UNABLE_TO_PROCESS_POINT_STR;

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__QueueResultEnum
    std::shared_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__QueueResultEnum
    std::shared_ptr<motoros2_interfaces::msg::QueueResultEnum_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const QueueResultEnum_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const QueueResultEnum_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct QueueResultEnum_

// alias to use template instance with default allocator
using QueueResultEnum =
  motoros2_interfaces::msg::QueueResultEnum_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::SUCCESS;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::SUCCESS_STR = "";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::WRONG_MODE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::WRONG_MODE_STR = "Must call start_point_queue_mode service";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::INIT_FAILURE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::INIT_FAILURE_STR = "Failed to initialize the streaming trajectory";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::BUSY;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::BUSY_STR = "Busy processing the previous trajectory point. Please resend the next point shortly";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::INVALID_JOINT_LIST;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::INVALID_JOINT_LIST_STR = "Point must contain data for all joints";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t QueueResultEnum_<ContainerAllocator>::UNABLE_TO_PROCESS_POINT;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
QueueResultEnum_<ContainerAllocator>::UNABLE_TO_PROCESS_POINT_STR = "Error while processing the trajectory point. Check debug log for more details";

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__QUEUE_RESULT_ENUM__STRUCT_HPP_
