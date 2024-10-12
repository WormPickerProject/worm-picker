// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from industrial_msgs:msg/RobotMode.idl
// generated code does not contain a copyright notice
#include "industrial_msgs/msg/detail/robot_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
industrial_msgs__msg__RobotMode__init(industrial_msgs__msg__RobotMode * msg)
{
  if (!msg) {
    return false;
  }
  // val
  return true;
}

void
industrial_msgs__msg__RobotMode__fini(industrial_msgs__msg__RobotMode * msg)
{
  if (!msg) {
    return;
  }
  // val
}

bool
industrial_msgs__msg__RobotMode__are_equal(const industrial_msgs__msg__RobotMode * lhs, const industrial_msgs__msg__RobotMode * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // val
  if (lhs->val != rhs->val) {
    return false;
  }
  return true;
}

bool
industrial_msgs__msg__RobotMode__copy(
  const industrial_msgs__msg__RobotMode * input,
  industrial_msgs__msg__RobotMode * output)
{
  if (!input || !output) {
    return false;
  }
  // val
  output->val = input->val;
  return true;
}

industrial_msgs__msg__RobotMode *
industrial_msgs__msg__RobotMode__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotMode * msg = (industrial_msgs__msg__RobotMode *)allocator.allocate(sizeof(industrial_msgs__msg__RobotMode), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(industrial_msgs__msg__RobotMode));
  bool success = industrial_msgs__msg__RobotMode__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
industrial_msgs__msg__RobotMode__destroy(industrial_msgs__msg__RobotMode * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    industrial_msgs__msg__RobotMode__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
industrial_msgs__msg__RobotMode__Sequence__init(industrial_msgs__msg__RobotMode__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotMode * data = NULL;

  if (size) {
    data = (industrial_msgs__msg__RobotMode *)allocator.zero_allocate(size, sizeof(industrial_msgs__msg__RobotMode), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = industrial_msgs__msg__RobotMode__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        industrial_msgs__msg__RobotMode__fini(&data[i - 1]);
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
industrial_msgs__msg__RobotMode__Sequence__fini(industrial_msgs__msg__RobotMode__Sequence * array)
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
      industrial_msgs__msg__RobotMode__fini(&array->data[i]);
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

industrial_msgs__msg__RobotMode__Sequence *
industrial_msgs__msg__RobotMode__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__RobotMode__Sequence * array = (industrial_msgs__msg__RobotMode__Sequence *)allocator.allocate(sizeof(industrial_msgs__msg__RobotMode__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = industrial_msgs__msg__RobotMode__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
industrial_msgs__msg__RobotMode__Sequence__destroy(industrial_msgs__msg__RobotMode__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    industrial_msgs__msg__RobotMode__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
industrial_msgs__msg__RobotMode__Sequence__are_equal(const industrial_msgs__msg__RobotMode__Sequence * lhs, const industrial_msgs__msg__RobotMode__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!industrial_msgs__msg__RobotMode__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
industrial_msgs__msg__RobotMode__Sequence__copy(
  const industrial_msgs__msg__RobotMode__Sequence * input,
  industrial_msgs__msg__RobotMode__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(industrial_msgs__msg__RobotMode);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    industrial_msgs__msg__RobotMode * data =
      (industrial_msgs__msg__RobotMode *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!industrial_msgs__msg__RobotMode__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          industrial_msgs__msg__RobotMode__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!industrial_msgs__msg__RobotMode__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
