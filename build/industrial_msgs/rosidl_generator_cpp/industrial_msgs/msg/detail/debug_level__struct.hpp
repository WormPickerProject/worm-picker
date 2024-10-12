// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from industrial_msgs:msg/DebugLevel.idl
// generated code does not contain a copyright notice

#ifndef INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_HPP_
#define INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__industrial_msgs__msg__DebugLevel __attribute__((deprecated))
#else
# define DEPRECATED__industrial_msgs__msg__DebugLevel __declspec(deprecated)
#endif

namespace industrial_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DebugLevel_
{
  using Type = DebugLevel_<ContainerAllocator>;

  explicit DebugLevel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->val = 0;
    }
  }

  explicit DebugLevel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    uint8_t;
  _val_type val;

  // setters for named parameter idiom
  Type & set__val(
    const uint8_t & _arg)
  {
    this->val = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t DEBUG =
    5u;
  static constexpr uint8_t INFO =
    4u;
  static constexpr uint8_t WARN =
    3u;
  // guard against 'ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(ERROR)
#    pragma push_macro("ERROR")
#    undef ERROR
#  endif
#endif
  static constexpr uint8_t ERROR =
    2u;
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("ERROR")
#endif
  static constexpr uint8_t FATAL =
    1u;
  static constexpr uint8_t NONE =
    0u;

  // pointer types
  using RawPtr =
    industrial_msgs::msg::DebugLevel_<ContainerAllocator> *;
  using ConstRawPtr =
    const industrial_msgs::msg::DebugLevel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::DebugLevel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      industrial_msgs::msg::DebugLevel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__industrial_msgs__msg__DebugLevel
    std::shared_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__industrial_msgs__msg__DebugLevel
    std::shared_ptr<industrial_msgs::msg::DebugLevel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DebugLevel_ & other) const
  {
    if (this->val != other.val) {
      return false;
    }
    return true;
  }
  bool operator!=(const DebugLevel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DebugLevel_

// alias to use template instance with default allocator
using DebugLevel =
  industrial_msgs::msg::DebugLevel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::DEBUG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::INFO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::WARN;
#endif  // __cplusplus < 201703L
// guard against 'ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(ERROR)
#    pragma push_macro("ERROR")
#    undef ERROR
#  endif
#endif
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::ERROR;
#endif  // __cplusplus < 201703L
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("ERROR")
#endif
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::FATAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t DebugLevel_<ContainerAllocator>::NONE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace industrial_msgs

#endif  // INDUSTRIAL_MSGS__MSG__DETAIL__DEBUG_LEVEL__STRUCT_HPP_
