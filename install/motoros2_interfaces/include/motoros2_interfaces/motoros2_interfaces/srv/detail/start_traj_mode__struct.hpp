// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motoros2_interfaces:srv/StartTrajMode.idl
// generated code does not contain a copyright notice

#ifndef MOTOROS2_INTERFACES__SRV__DETAIL__START_TRAJ_MODE__STRUCT_HPP_
#define MOTOROS2_INTERFACES__SRV__DETAIL__START_TRAJ_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Request __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Request __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct StartTrajMode_Request_
{
  using Type = StartTrajMode_Request_<ContainerAllocator>;

  explicit StartTrajMode_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit StartTrajMode_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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

  // pointer types
  using RawPtr =
    motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Request
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Request
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StartTrajMode_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const StartTrajMode_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StartTrajMode_Request_

// alias to use template instance with default allocator
using StartTrajMode_Request =
  motoros2_interfaces::srv::StartTrajMode_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace motoros2_interfaces


// Include directives for member types
// Member 'result_code'
#include "motoros2_interfaces/msg/detail/motion_ready_enum__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Response __attribute__((deprecated))
#else
# define DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Response __declspec(deprecated)
#endif

namespace motoros2_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct StartTrajMode_Response_
{
  using Type = StartTrajMode_Response_<ContainerAllocator>;

  explicit StartTrajMode_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result_code(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  explicit StartTrajMode_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result_code(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  // field types and members
  using _result_code_type =
    motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator>;
  _result_code_type result_code;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__result_code(
    const motoros2_interfaces::msg::MotionReadyEnum_<ContainerAllocator> & _arg)
  {
    this->result_code = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Response
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motoros2_interfaces__srv__StartTrajMode_Response
    std::shared_ptr<motoros2_interfaces::srv::StartTrajMode_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StartTrajMode_Response_ & other) const
  {
    if (this->result_code != other.result_code) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const StartTrajMode_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StartTrajMode_Response_

// alias to use template instance with default allocator
using StartTrajMode_Response =
  motoros2_interfaces::srv::StartTrajMode_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace motoros2_interfaces

namespace motoros2_interfaces
{

namespace srv
{

struct StartTrajMode
{
  using Request = motoros2_interfaces::srv::StartTrajMode_Request;
  using Response = motoros2_interfaces::srv::StartTrajMode_Response;
};

}  // namespace srv

}  // namespace motoros2_interfaces

#endif  // MOTOROS2_INTERFACES__SRV__DETAIL__START_TRAJ_MODE__STRUCT_HPP_
