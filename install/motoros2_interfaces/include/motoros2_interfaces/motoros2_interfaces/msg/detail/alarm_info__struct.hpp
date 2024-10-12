// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:msg/AlarmInfo.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__STRUCT_HPP_
#define MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__STRUCT_HPP_

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
// Member 'help'
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__msg__AlarmInfo __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__msg__AlarmInfo __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AlarmInfo_
{
  using Type = AlarmInfo_<ContainerAllocator>;

  explicit AlarmInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : datetime(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = 0ul;
      this->message = "";
      this->sub_code = 0l;
      this->contents = "";
      this->description = "";
    }
  }

  explicit AlarmInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    datetime(_alloc, _init),
    contents(_alloc),
    description(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->number = 0ul;
      this->message = "";
      this->sub_code = 0l;
      this->contents = "";
      this->description = "";
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
  using _contents_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _contents_type contents;
  using _description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _description_type description;
  using _help_type =
    std::vector<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>>;
  _help_type help;

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
  Type & set__contents(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->contents = _arg;
    return *this;
  }
  Type & set__description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->description = _arg;
    return *this;
  }
  Type & set__help(
    const std::vector<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<motoros2_interfaces::msg::AlarmCauseRemedy_<ContainerAllocator>>> & _arg)
  {
    this->help = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__msg__AlarmInfo
    std::shared_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__msg__AlarmInfo
    std::shared_ptr<motoros2_interfaces::msg::AlarmInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AlarmInfo_ & other) const
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
    if (this->contents != other.contents) {
      return false;
    }
    if (this->description != other.description) {
      return false;
    }
    if (this->help != other.help) {
      return false;
    }
    return true;
  }
  bool operator!=(const AlarmInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AlarmInfo_

// alias to use template instance with default allocator
using AlarmInfo =
  motoros2_interfaces::msg::AlarmInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__MSG__DETAIL__ALARM_INFO__STRUCT_HPP_
