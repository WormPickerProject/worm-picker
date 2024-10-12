// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/ErrorInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'datetime'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__ErrorInfo __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__ErrorInfo __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ErrorInfo_
{
  using Type = ErrorInfo_<ContainerAllocator>;

  explicit ErrorInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : datetime(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = 0ul;
      this->message = "";
      this->sub_code = 0l;
    }
  }

  explicit ErrorInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    datetime(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = 0ul;
      this->message = "";
      this->sub_code = 0l;
    }
  }

  // field types and members
  using _number_type =
    uint32_t;
  _number_type number;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _sub_code_type =
    int32_t;
  _sub_code_type sub_code;
  using _datetime_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _datetime_type datetime;

  // setters for named parameter idiom
  Type & set__number(
    const uint32_t & _arg)
  {
    this->number = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__sub_code(
    const int32_t & _arg)
  {
    this->sub_code = _arg;
    return *this;
  }
  Type & set__datetime(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->datetime = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__ErrorInfo
    std::shared_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__ErrorInfo
    std::shared_ptr<motoros2_interfaces::msg::ErrorInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ErrorInfo_ & other) const
  {
    if (this->number != other.number) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->sub_code != other.sub_code) {
      return false;
    }
    if (this->datetime != other.datetime) {
      return false;
    }
    return true;
  }
  bool operator!=(const ErrorInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ErrorInfo_

// alias to use template instance with default allocator
using ErrorInfo =
  motoros2_interfaces::msg::ErrorInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ERROR_INFO__STRUCT_HPP_
