// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motoros2_interfaces:msg/AlarmCauseRemedy.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/msg/detail/alarm_cause_remedy__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `cause`
// Member `remedy`
#include "rosidl_runtime_c/string_functions.h"

bool
motoros2_interfaces__msg__AlarmCauseRemedy__init(motoros2_interfaces__msg__AlarmCauseRemedy * msg)
{
  if (!msg) {
    return false;
  }
  // cause
  if (!rosidl_runtime_c__String__init(&msg->cause)) {
    motoros2_interfaces__msg__AlarmCauseRemedy__fini(msg);
    return false;
  }
  // remedy
  if (!rosidl_runtime_c__String__init(&msg->remedy)) {
    motoros2_interfaces__msg__AlarmCauseRemedy__fini(msg);
    return false;
  }
  return true;
}

void
motoros2_interfaces__msg__AlarmCauseRemedy__fini(motoros2_interfaces__msg__AlarmCauseRemedy * msg)
{
  if (!msg) {
    return;
  }
  // cause
  rosidl_runtime_c__String__fini(&msg->cause);
  // remedy
  rosidl_runtime_c__String__fini(&msg->remedy);
}

bool
motoros2_interfaces__msg__AlarmCauseRemedy__are_equal(const motoros2_interfaces__msg__AlarmCauseRemedy * lhs, const motoros2_interfaces__msg__AlarmCauseRemedy * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // cause
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->cause), &(rhs->cause)))
  {
    return false;
  }
  // remedy
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->remedy), &(rhs->remedy)))
  {
    return false;
  }
  return true;
}

bool
motoros2_interfaces__msg__AlarmCauseRemedy__copy(
  const motoros2_interfaces__msg__AlarmCauseRemedy * input,
  motoros2_interfaces__msg__AlarmCauseRemedy * output)
{
  if (!input || !output) {
    return false;
  }
  // cause
  if (!rosidl_runtime_c__String__copy(
      &(input->cause), &(output->cause)))
  {
    return false;
  }
  // remedy
  if (!rosidl_runtime_c__String__copy(
      &(input->remedy), &(output->remedy)))
  {
    return false;
  }
  return true;
}

motoros2_interfaces__msg__AlarmCauseRemedy *
motoros2_interfaces__msg__AlarmCauseRemedy__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__AlarmCauseRemedy * msg = (motoros2_interfaces__msg__AlarmCauseRemedy *)allocator.allocate(sizeof(motoros2_interfaces__msg__AlarmCauseRemedy), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motoros2_interfaces__msg__AlarmCauseRemedy));
  bool success = motoros2_interfaces__msg__AlarmCauseRemedy__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motoros2_interfaces__msg__AlarmCauseRemedy__destroy(motoros2_interfaces__msg__AlarmCauseRemedy * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motoros2_interfaces__msg__AlarmCauseRemedy__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__init(motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__AlarmCauseRemedy * data = NULL;

  if (size) {
    data = (motoros2_interfaces__msg__AlarmCauseRemedy *)allocator.zero_allocate(size, sizeof(motoros2_interfaces__msg__AlarmCauseRemedy), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motoros2_interfaces__msg__AlarmCauseRemedy__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motoros2_interfaces__msg__AlarmCauseRemedy__fini(&data[i - 1]);
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
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__fini(motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * array)
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
      motoros2_interfaces__msg__AlarmCauseRemedy__fini(&array->data[i]);
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

motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * array = (motoros2_interfaces__msg__AlarmCauseRemedy__Sequence *)allocator.allocate(sizeof(motoros2_interfaces__msg__AlarmCauseRemedy__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__destroy(motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__are_equal(const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * lhs, const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motoros2_interfaces__msg__AlarmCauseRemedy__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motoros2_interfaces__msg__AlarmCauseRemedy__Sequence__copy(
  const motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * input,
  motoros2_interfaces__msg__AlarmCauseRemedy__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motoros2_interfaces__msg__AlarmCauseRemedy);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motoros2_interfaces__msg__AlarmCauseRemedy * data =
      (motoros2_interfaces__msg__AlarmCauseRemedy *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motoros2_interfaces__msg__AlarmCauseRemedy__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motoros2_interfaces__msg__AlarmCauseRemedy__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motoros2_interfaces__msg__AlarmCauseRemedy__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
