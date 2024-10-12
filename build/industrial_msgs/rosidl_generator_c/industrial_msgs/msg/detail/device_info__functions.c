// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from industrial_msgs:msg/DeviceInfo.idl
// generated code does not contain a copyright notice
#include "industrial_msgs/msg/detail/device_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `model`
// Member `serial_number`
// Member `hw_version`
// Member `sw_version`
// Member `address`
#include "rosidl_runtime_c/string_functions.h"

bool
industrial_msgs__msg__DeviceInfo__init(industrial_msgs__msg__DeviceInfo * msg)
{
  if (!msg) {
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__init(&msg->model)) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
    return false;
  }
  // serial_number
  if (!rosidl_runtime_c__String__init(&msg->serial_number)) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
    return false;
  }
  // hw_version
  if (!rosidl_runtime_c__String__init(&msg->hw_version)) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
    return false;
  }
  // sw_version
  if (!rosidl_runtime_c__String__init(&msg->sw_version)) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
    return false;
  }
  // address
  if (!rosidl_runtime_c__String__init(&msg->address)) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
    return false;
  }
  return true;
}

void
industrial_msgs__msg__DeviceInfo__fini(industrial_msgs__msg__DeviceInfo * msg)
{
  if (!msg) {
    return;
  }
  // model
  rosidl_runtime_c__String__fini(&msg->model);
  // serial_number
  rosidl_runtime_c__String__fini(&msg->serial_number);
  // hw_version
  rosidl_runtime_c__String__fini(&msg->hw_version);
  // sw_version
  rosidl_runtime_c__String__fini(&msg->sw_version);
  // address
  rosidl_runtime_c__String__fini(&msg->address);
}

bool
industrial_msgs__msg__DeviceInfo__are_equal(const industrial_msgs__msg__DeviceInfo * lhs, const industrial_msgs__msg__DeviceInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->model), &(rhs->model)))
  {
    return false;
  }
  // serial_number
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->serial_number), &(rhs->serial_number)))
  {
    return false;
  }
  // hw_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->hw_version), &(rhs->hw_version)))
  {
    return false;
  }
  // sw_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->sw_version), &(rhs->sw_version)))
  {
    return false;
  }
  // address
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->address), &(rhs->address)))
  {
    return false;
  }
  return true;
}

bool
industrial_msgs__msg__DeviceInfo__copy(
  const industrial_msgs__msg__DeviceInfo * input,
  industrial_msgs__msg__DeviceInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // model
  if (!rosidl_runtime_c__String__copy(
      &(input->model), &(output->model)))
  {
    return false;
  }
  // serial_number
  if (!rosidl_runtime_c__String__copy(
      &(input->serial_number), &(output->serial_number)))
  {
    return false;
  }
  // hw_version
  if (!rosidl_runtime_c__String__copy(
      &(input->hw_version), &(output->hw_version)))
  {
    return false;
  }
  // sw_version
  if (!rosidl_runtime_c__String__copy(
      &(input->sw_version), &(output->sw_version)))
  {
    return false;
  }
  // address
  if (!rosidl_runtime_c__String__copy(
      &(input->address), &(output->address)))
  {
    return false;
  }
  return true;
}

industrial_msgs__msg__DeviceInfo *
industrial_msgs__msg__DeviceInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__DeviceInfo * msg = (industrial_msgs__msg__DeviceInfo *)allocator.allocate(sizeof(industrial_msgs__msg__DeviceInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(industrial_msgs__msg__DeviceInfo));
  bool success = industrial_msgs__msg__DeviceInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
industrial_msgs__msg__DeviceInfo__destroy(industrial_msgs__msg__DeviceInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    industrial_msgs__msg__DeviceInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
industrial_msgs__msg__DeviceInfo__Sequence__init(industrial_msgs__msg__DeviceInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__DeviceInfo * data = NULL;

  if (size) {
    data = (industrial_msgs__msg__DeviceInfo *)allocator.zero_allocate(size, sizeof(industrial_msgs__msg__DeviceInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = industrial_msgs__msg__DeviceInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        industrial_msgs__msg__DeviceInfo__fini(&data[i - 1]);
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
industrial_msgs__msg__DeviceInfo__Sequence__fini(industrial_msgs__msg__DeviceInfo__Sequence * array)
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
      industrial_msgs__msg__DeviceInfo__fini(&array->data[i]);
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

industrial_msgs__msg__DeviceInfo__Sequence *
industrial_msgs__msg__DeviceInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  industrial_msgs__msg__DeviceInfo__Sequence * array = (industrial_msgs__msg__DeviceInfo__Sequence *)allocator.allocate(sizeof(industrial_msgs__msg__DeviceInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = industrial_msgs__msg__DeviceInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
industrial_msgs__msg__DeviceInfo__Sequence__destroy(industrial_msgs__msg__DeviceInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    industrial_msgs__msg__DeviceInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
industrial_msgs__msg__DeviceInfo__Sequence__are_equal(const industrial_msgs__msg__DeviceInfo__Sequence * lhs, const industrial_msgs__msg__DeviceInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!industrial_msgs__msg__DeviceInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
industrial_msgs__msg__DeviceInfo__Sequence__copy(
  const industrial_msgs__msg__DeviceInfo__Sequence * input,
  industrial_msgs__msg__DeviceInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(industrial_msgs__msg__DeviceInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    industrial_msgs__msg__DeviceInfo * data =
      (industrial_msgs__msg__DeviceInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!industrial_msgs__msg__DeviceInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          industrial_msgs__msg__DeviceInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!industrial_msgs__msg__DeviceInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
