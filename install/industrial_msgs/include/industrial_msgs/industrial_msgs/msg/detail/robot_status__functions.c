// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from industrial_msgs:msg/RobotStatus.idl
// generated code does not contain a copyright notice
#include "industrial_msgs/msg/detail/robot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `mode`
#include "industrial_msgs/msg/detail/robot_mode__functions.h"
// Member `e_stopped`
// Member `drives_powered`
// Member `motion_possible`
// Member `in_motion`
// Member `in_error`
#include "industrial_msgs/msg/detail/tri_state__functions.h"
// Member `error_codes`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
industrial_msgs__msg__RobotStatus__init(industrial_msgs__msg__RobotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // mode
  if (!industrial_msgs__msg__RobotMode__init(&msg->mode)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // e_stopped
  if (!industrial_msgs__msg__TriState__init(&msg->e_stopped)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // drives_powered
  if (!industrial_msgs__msg__TriState__init(&msg->drives_powered)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // motion_possible
  if (!industrial_msgs__msg__TriState__init(&msg->motion_possible)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // in_motion
  if (!industrial_msgs__msg__TriState__init(&msg->in_motion)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // in_error
  if (!industrial_msgs__msg__TriState__init(&msg->in_error)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  // error_codes
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->error_codes, 0)) {
    industrial_msgs__msg__RobotStatus__fini(msg);
    return false;
  }
  return true;
}

void
industrial_msgs__msg__RobotStatus__fini(industrial_msgs__msg__RobotStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // mode
  industrial_msgs__msg__RobotMode__fini(&msg->mode);
  // e_stopped
  industrial_msgs__msg__TriState__fini(&msg->e_stopped);
  // drives_powered
  industrial_msgs__msg__TriState__fini(&msg->drives_powered);
  // motion_possible
  industrial_msgs__msg__TriState__fini(&msg->motion_possible);
  // in_motion
  industrial_msgs__msg__TriState__fini(&msg->in_motion);
  // in_error
  industrial_msgs__msg__TriState__fini(&msg->in_error);
  // error_codes
  rosidl_runtime_c__int32__Sequence__fini(&msg->error_codes);
}

bool
industrial_msgs__msg__RobotStatus__are_equal(const industrial_msgs__msg__RobotStatus * lhs, const industrial_msgs__msg__RobotStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // mode
  if (!industrial_msgs__msg__RobotMode__are_equal(
      &(lhs->mode), &(rhs->mode)))
  {
    return false;
  }
  // e_stopped
  if (!industrial_msgs__msg__TriState__are_equal(
      &(lhs->e_stopped), &(rhs->e_stopped)))
  {
    return false;
  }
  // drives_powered
  if (!industrial_msgs__msg__TriState__are_equal(
      &(lhs->drives_powered), &(rhs->drives_powered)))
  {
    return false;
  }
  // motion_possible
  if (!industrial_msgs__msg__TriState__are_equal(
      &(lhs->motion_possible), &(rhs->motion_possible)))
  {
    return false;
  }
  // in_motion
  if (!industrial_msgs__msg__TriState__are_equal(
      &(lhs->in_motion), &(rhs->in_motion)))
  {
    return false;
  }
  // in_error
  if (!industrial_msgs__msg__TriState__are_equal(
      &(lhs->in_error), &(rhs->in_error)))
  {
    return false;
  }
  // error_codes
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->error_codes), &(rhs->error_codes)))
  {
    return false;
  }
  return true;
}

bool
industrial_msgs__msg__RobotStatus__copy(
  const industrial_msgs__msg__RobotStatus * input,
  industrial_msgs__msg__RobotStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // mode
  if (!industrial_msgs__msg__RobotMode__copy(
      &(input->mode), &(output->mode)))
  {
    return false;
  }
  // e_stopped
  if (!industrial_msgs__msg__TriState__copy(
      &(input->e_stopped), &(output->e_stopped)))
  {
    return false;
  }
  // drives_powered
  if (!industrial_msgs__msg__TriState__copy(
      &(input->drives_powered), &(output->drives_powered)))
  {
    return false;
  }
  // motion_possible
  if (!industrial_msgs__msg__TriState__copy(
      &(input->motion_possible), &(output->motion_possible)))
  {
    return false;
  }
  // in_motion
  if (!industrial_msgs__msg__TriState__copy(
      &(input->in_motion), &(output->in_motion)))
  {
    return false;
  }
  // in_error
  if (!industrial_msgs__msg__TriState__copy(
      &(input->in_error), &(output->in_error)))
  {
    return false;
  }
  // error_codes
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->error_codes), &(output->error_codes)))
  {
    return false;
  }
  return true;
}

industrial_msgs__msg__RobotStatus *
industrial_msgs__msg__RobotStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotStatus * msg = (industrial_msgs__msg__RobotStatus *)allocator.allocate(sizeof(industrial_msgs__msg__RobotStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(industrial_msgs__msg__RobotStatus));
  bool success = industrial_msgs__msg__RobotStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
industrial_msgs__msg__RobotStatus__destroy(industrial_msgs__msg__RobotStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    industrial_msgs__msg__RobotStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
industrial_msgs__msg__RobotStatus__Sequence__init(industrial_msgs__msg__RobotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotStatus * data = NULL;

  if (size) {
    data = (industrial_msgs__msg__RobotStatus *)allocator.zero_allocate(size, sizeof(industrial_msgs__msg__RobotStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = industrial_msgs__msg__RobotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        industrial_msgs__msg__RobotStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
industrial_msgs__msg__RobotStatus__Sequence__fini(industrial_msgs__msg__RobotStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      industrial_msgs__msg__RobotStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

industrial_msgs__msg__RobotStatus__Sequence *
industrial_msgs__msg__RobotStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotStatus__Sequence * array = (industrial_msgs__msg__RobotStatus__Sequence *)allocator.allocate(sizeof(industrial_msgs__msg__RobotStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = industrial_msgs__msg__RobotStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
industrial_msgs__msg__RobotStatus__Sequence__destroy(industrial_msgs__msg__RobotStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    industrial_msgs__msg__RobotStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
industrial_msgs__msg__RobotStatus__Sequence__are_equal(const industrial_msgs__msg__RobotStatus__Sequence * lhs, const industrial_msgs__msg__RobotStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!industrial_msgs__msg__RobotStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
industrial_msgs__msg__RobotStatus__Sequence__copy(
  const industrial_msgs__msg__RobotStatus__Sequence * input,
  industrial_msgs__msg__RobotStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(industrial_msgs__msg__RobotStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    industrial_msgs__msg__RobotStatus * data =
      (industrial_msgs__msg__RobotStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!industrial_msgs__msg__RobotStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          industrial_msgs__msg__RobotStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!industrial_msgs__msg__RobotStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
