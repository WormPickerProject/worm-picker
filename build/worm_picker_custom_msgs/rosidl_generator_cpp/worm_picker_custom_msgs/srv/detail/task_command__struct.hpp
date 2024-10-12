// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from worm_picker_custom_msgs:srv/TaskCommand.idl
// generated code does not contain a copyright notice

#ifndef WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__STRUCT_HPP_
#define WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Request __attribute__((deprecated))
#else
# define DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Request __declspec(deprecated)
#endif

namespace worm_picker_custom_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TaskCommand_Request_
{
  using Type = TaskCommand_Request_<ContainerAllocator>;

  explicit TaskCommand_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  explicit TaskCommand_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : command(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  // field types and members
  using _command_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _command_type command;

  // setters for named parameter idiom
  Type & set__command(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->command = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Request
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Request
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TaskCommand_Request_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    return true;
  }
  bool operator!=(const TaskCommand_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TaskCommand_Request_

// alias to use template instance with default allocator
using TaskCommand_Request =
  worm_picker_custom_msgs::srv::TaskCommand_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace worm_picker_custom_msgs


#ifndef _WIN32
# define DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Response __attribute__((deprecated))
#else
# define DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Response __declspec(deprecated)
#endif

namespace worm_picker_custom_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TaskCommand_Response_
{
  using Type = TaskCommand_Response_<ContainerAllocator>;

  explicit TaskCommand_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit TaskCommand_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Response
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__worm_picker_custom_msgs__srv__TaskCommand_Response
    std::shared_ptr<worm_picker_custom_msgs::srv::TaskCommand_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TaskCommand_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const TaskCommand_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TaskCommand_Response_

// alias to use template instance with default allocator
using TaskCommand_Response =
  worm_picker_custom_msgs::srv::TaskCommand_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace worm_picker_custom_msgs

namespace worm_picker_custom_msgs
{

namespace srv
{

struct TaskCommand
{
  using Request = worm_picker_custom_msgs::srv::TaskCommand_Request;
  using Response = worm_picker_custom_msgs::srv::TaskCommand_Response;
};

}  // namespace srv

}  // namespace worm_picker_custom_msgs

#endif  // WORM_PICKER_CUSTOM_MSGS__SRV__DETAIL__TASK_COMMAND__STRUCT_HPP_
