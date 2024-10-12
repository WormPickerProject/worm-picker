// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/SelectionResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__SelectionResultCodes __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__SelectionResultCodes __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SelectionResultCodes_
{
  using Type = SelectionResultCodes_<ContainerAllocator>;

  explicit SelectionResultCodes_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0ul;
    }
  }

  explicit SelectionResultCodes_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0ul;
    }
  }

  // field types and members
  using _value_type =
    uint32_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint32_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint32_t OK =
    0u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> OK_STR;
  static constexpr uint32_t INVALID_CONTROLLER_STATE =
    400u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> INVALID_CONTROLLER_STATE_STR;
  static constexpr uint32_t INVALID_CONTROL_GROUP =
    401u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> INVALID_CONTROL_GROUP_STR;
  static constexpr uint32_t INVALID_SELECTION_INDEX =
    402u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> INVALID_SELECTION_INDEX_STR;

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__SelectionResultCodes
    std::shared_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__SelectionResultCodes
    std::shared_ptr<motoros2_interfaces::msg::SelectionResultCodes_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SelectionResultCodes_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const SelectionResultCodes_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SelectionResultCodes_

// alias to use template instance with default allocator
using SelectionResultCodes =
  motoros2_interfaces::msg::SelectionResultCodes_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SelectionResultCodes_<ContainerAllocator>::OK;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
SelectionResultCodes_<ContainerAllocator>::OK_STR = "";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SelectionResultCodes_<ContainerAllocator>::INVALID_CONTROLLER_STATE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
SelectionResultCodes_<ContainerAllocator>::INVALID_CONTROLLER_STATE_STR = "Pendant is not in REMOTE mode";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SelectionResultCodes_<ContainerAllocator>::INVALID_CONTROL_GROUP;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
SelectionResultCodes_<ContainerAllocator>::INVALID_CONTROL_GROUP_STR = "Invalid control group";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t SelectionResultCodes_<ContainerAllocator>::INVALID_SELECTION_INDEX;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
SelectionResultCodes_<ContainerAllocator>::INVALID_SELECTION_INDEX_STR = "Invalid tool selection";

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__SELECTION_RESULT_CODES__STRUCT_HPP_
