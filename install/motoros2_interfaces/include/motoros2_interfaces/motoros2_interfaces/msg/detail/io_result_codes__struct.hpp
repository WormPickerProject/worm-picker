// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/IoResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__IoResultCodes __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__IoResultCodes __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct IoResultCodes_
{
  using Type = IoResultCodes_<ContainerAllocator>;

  explicit IoResultCodes_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit IoResultCodes_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations
  static constexpr uint32_t OK =
    0u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> OK_STR;
  static constexpr uint32_t READ_ADDRESS_INVALID =
    1001u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> READ_ADDRESS_INVALID_STR;
  static constexpr uint32_t WRITE_ADDRESS_INVALID =
    1002u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> WRITE_ADDRESS_INVALID_STR;
  static constexpr uint32_t WRITE_VALUE_INVALID =
    1003u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> WRITE_VALUE_INVALID_STR;
  static constexpr uint32_t READ_API_ERROR =
    1004u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> READ_API_ERROR_STR;
  static constexpr uint32_t WRITE_API_ERROR =
    1005u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> WRITE_API_ERROR_STR;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> UNKNOWN_API_ERROR_STR;

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__IoResultCodes
    std::shared_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__IoResultCodes
    std::shared_ptr<motoros2_interfaces::msg::IoResultCodes_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IoResultCodes_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const IoResultCodes_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IoResultCodes_

// alias to use template instance with default allocator
using IoResultCodes =
  motoros2_interfaces::msg::IoResultCodes_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::OK;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::OK_STR = "Success";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::READ_ADDRESS_INVALID;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::READ_ADDRESS_INVALID_STR = "Address cannot be read from (out of readable range)";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::WRITE_ADDRESS_INVALID;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::WRITE_ADDRESS_INVALID_STR = "Address cannot be written to (out of writable range)";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::WRITE_VALUE_INVALID;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::WRITE_VALUE_INVALID_STR = "Illegal value for the type of IO element addressed";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::READ_API_ERROR;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::READ_API_ERROR_STR = "The MotoPlus function mpReadIO returned -1. No further information is available";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t IoResultCodes_<ContainerAllocator>::WRITE_API_ERROR;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::WRITE_API_ERROR_STR = "The MotoPlus function mpWriteIO returned -1. No further information is available";
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
IoResultCodes_<ContainerAllocator>::UNKNOWN_API_ERROR_STR = "Unknown error accessing I/O. No further information is available";

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__IO_RESULT_CODES__STRUCT_HPP_
