// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from motoros2_interfaces:srv/QueueTrajPoint.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/srv/detail/queue_traj_point__rosidl_typesupport_fastrtps_cpp.hpp"
#include "motoros2_interfaces/srv/detail/queue_traj_point__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace trajectory_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const trajectory_msgs::msg::JointTrajectoryPoint &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  trajectory_msgs::msg::JointTrajectoryPoint &);
size_t get_serialized_size(
  const trajectory_msgs::msg::JointTrajectoryPoint &,
  size_t current_alignment);
size_t
max_serialized_size_JointTrajectoryPoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace trajectory_msgs


namespace motoros2_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_serialize(
  const motoros2_interfaces::srv::QueueTrajPoint_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: joint_names
  {
    cdr << ros_message.joint_names;
  }
  // Member: point
  trajectory_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.point,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  motoros2_interfaces::srv::QueueTrajPoint_Request & ros_message)
{
  // Member: joint_names
  {
    cdr >> ros_message.joint_names;
  }

  // Member: point
  trajectory_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.point);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
get_serialized_size(
  const motoros2_interfaces::srv::QueueTrajPoint_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: joint_names
  {
    size_t array_size = ros_message.joint_names.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (ros_message.joint_names[index].size() + 1);
    }
  }
  // Member: point

  current_alignment +=
    trajectory_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.point, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
max_serialized_size_QueueTrajPoint_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: joint_names
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: point
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        trajectory_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_JointTrajectoryPoint(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = motoros2_interfaces::srv::QueueTrajPoint_Request;
    is_plain =
      (
      offsetof(DataType, point) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _QueueTrajPoint_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::srv::QueueTrajPoint_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _QueueTrajPoint_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<motoros2_interfaces::srv::QueueTrajPoint_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _QueueTrajPoint_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::srv::QueueTrajPoint_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _QueueTrajPoint_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_QueueTrajPoint_Request(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _QueueTrajPoint_Request__callbacks = {
  "motoros2_interfaces::srv",
  "QueueTrajPoint_Request",
  _QueueTrajPoint_Request__cdr_serialize,
  _QueueTrajPoint_Request__cdr_deserialize,
  _QueueTrajPoint_Request__get_serialized_size,
  _QueueTrajPoint_Request__max_serialized_size
};

static rosidl_message_type_support_t _QueueTrajPoint_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_QueueTrajPoint_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace motoros2_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::srv::QueueTrajPoint_Request>()
{
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, srv, QueueTrajPoint_Request)() {
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace motoros2_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const motoros2_interfaces::msg::QueueResultEnum &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  motoros2_interfaces::msg::QueueResultEnum &);
size_t get_serialized_size(
  const motoros2_interfaces::msg::QueueResultEnum &,
  size_t current_alignment);
size_t
max_serialized_size_QueueResultEnum(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace motoros2_interfaces


namespace motoros2_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_serialize(
  const motoros2_interfaces::srv::QueueTrajPoint_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: result_code
  motoros2_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.result_code,
    cdr);
  // Member: message
  cdr << ros_message.message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  motoros2_interfaces::srv::QueueTrajPoint_Response & ros_message)
{
  // Member: result_code
  motoros2_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.result_code);

  // Member: message
  cdr >> ros_message.message;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
get_serialized_size(
  const motoros2_interfaces::srv::QueueTrajPoint_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: result_code

  current_alignment +=
    motoros2_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.result_code, current_alignment);
  // Member: message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_motoros2_interfaces
max_serialized_size_QueueTrajPoint_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: result_code
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        motoros2_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_QueueResultEnum(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: message
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = motoros2_interfaces::srv::QueueTrajPoint_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _QueueTrajPoint_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::srv::QueueTrajPoint_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _QueueTrajPoint_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<motoros2_interfaces::srv::QueueTrajPoint_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _QueueTrajPoint_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const motoros2_interfaces::srv::QueueTrajPoint_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _QueueTrajPoint_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_QueueTrajPoint_Response(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _QueueTrajPoint_Response__callbacks = {
  "motoros2_interfaces::srv",
  "QueueTrajPoint_Response",
  _QueueTrajPoint_Response__cdr_serialize,
  _QueueTrajPoint_Response__cdr_deserialize,
  _QueueTrajPoint_Response__get_serialized_size,
  _QueueTrajPoint_Response__max_serialized_size
};

static rosidl_message_type_support_t _QueueTrajPoint_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_QueueTrajPoint_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace motoros2_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_motoros2_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<motoros2_interfaces::srv::QueueTrajPoint_Response>()
{
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, srv, QueueTrajPoint_Response)() {
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace motoros2_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _QueueTrajPoint__callbacks = {
  "motoros2_interfaces::srv",
  "QueueTrajPoint",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, srv, QueueTrajPoint_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, srv, QueueTrajPoint_Response)(),
};

static rosidl_service_type_support_t _QueueTrajPoint__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_QueueTrajPoint__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace motoros2_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_motoros2_interfaces
const rosidl_service_type_support_t *
get_service_type_support_handle<motoros2_interfaces::srv::QueueTrajPoint>()
{
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, motoros2_interfaces, srv, QueueTrajPoint)() {
  return &motoros2_interfaces::srv::typesupport_fastrtps_cpp::_QueueTrajPoint__handle;
}

#ifdef __cplusplus
}
#endif
