// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__InformJobCrudResultCodes __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__InformJobCrudResultCodes __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct InformJobCrudResultCodes_
{
  using Type = InformJobCrudResultCodes_<ContainerAllocator>;

  explicit InformJobCrudResultCodes_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit InformJobCrudResultCodes_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint32_t RC_OK =
    1u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_OK;
  static constexpr uint32_t RC_ERR_REFRESHING_JOB_LIST =
    10u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_ERR_REFRESHING_JOB_LIST;
  static constexpr uint32_t RC_ERR_RETRIEVING_FILE_COUNT =
    11u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_ERR_RETRIEVING_FILE_COUNT;
  static constexpr uint32_t RC_ERR_TOO_MANY_JOBS =
    12u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_ERR_TOO_MANY_JOBS;
  static constexpr uint32_t RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST =
    13u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST;
  static constexpr uint32_t RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE =
    14u;
  static const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE;

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__InformJobCrudResultCodes
    std::shared_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__InformJobCrudResultCodes
    std::shared_ptr<motoros2_interfaces::msg::InformJobCrudResultCodes_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const InformJobCrudResultCodes_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const InformJobCrudResultCodes_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct InformJobCrudResultCodes_

// alias to use template instance with default allocator
using InformJobCrudResultCodes =
  motoros2_interfaces::msg::InformJobCrudResultCodes_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_OK;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_OK = "Success";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_ERR_REFRESHING_JOB_LIST;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_ERR_REFRESHING_JOB_LIST = "Error refreshing job list";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_ERR_RETRIEVING_FILE_COUNT;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_ERR_RETRIEVING_FILE_COUNT = "Error retrieving file count";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_ERR_TOO_MANY_JOBS;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_ERR_TOO_MANY_JOBS = "Too many jobs";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST = "Failed retrieving job name from list";
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint32_t InformJobCrudResultCodes_<ContainerAllocator>::RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE;
#endif  // __cplusplus < 201703L
template<typename ContainerAllocator>
const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>
InformJobCrudResultCodes_<ContainerAllocator>::STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE = "Error adding job name to service response";

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__INFORM_JOB_CRUD_RESULT_CODES__STRUCT_HPP_
