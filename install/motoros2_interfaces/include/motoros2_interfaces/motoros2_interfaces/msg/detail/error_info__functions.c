// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motoros2_interfaces:msg/ErrorInfo.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/msg/detail/error_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `datetime`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
motoros2_interfaces__msg__ErrorInfo__init(motoros2_interfaces__msg__ErrorInfo * msg)
{
  if (!msg) {
    return false;
  }
  // number
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    motoros2_interfaces__msg__ErrorInfo__fini(msg);
    return false;
  }
  // sub_code
  // datetime
  if (!builtin_interfaces__msg__Time__init(&msg->datetime)) {
    motoros2_interfaces__msg__ErrorInfo__fini(msg);
    return false;
  }
  return true;
}

void
motoros2_interfaces__msg__ErrorInfo__fini(motoros2_interfaces__msg__ErrorInfo * msg)
{
  if (!msg) {
    return;
  }
  // number
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // sub_code
  // datetime
  builtin_interfaces__msg__Time__fini(&msg->datetime);
}

bool
motoros2_interfaces__msg__ErrorInfo__are_equal(const motoros2_interfaces__msg__ErrorInfo * lhs, const motoros2_interfaces__msg__ErrorInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // number
  if (lhs->number != rhs->number) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // sub_code
  if (lhs->sub_code != rhs->sub_code) {
    return false;
  }
  // datetime
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->datetime), &(rhs->datetime)))
  {
    return false;
  }
  return true;
}

bool
motoros2_interfaces__msg__ErrorInfo__copy(
  const motoros2_interfaces__msg__ErrorInfo * input,
  motoros2_interfaces__msg__ErrorInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // number
  output->number = input->number;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // sub_code
  output->sub_code = input->sub_code;
  // datetime
  if (!builtin_interfaces__msg__Time__copy(
      &(input->datetime), &(output->datetime)))
  {
    return false;
  }
  return true;
}

motoros2_interfaces__msg__ErrorInfo *
motoros2_interfaces__msg__ErrorInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__ErrorInfo * msg = (motoros2_interfaces__msg__ErrorInfo *)allocator.allocate(sizeof(motoros2_interfaces__msg__ErrorInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motoros2_interfaces__msg__ErrorInfo));
  bool success = motoros2_interfaces__msg__ErrorInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motoros2_interfaces__msg__ErrorInfo__destroy(motoros2_interfaces__msg__ErrorInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motoros2_interfaces__msg__ErrorInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motoros2_interfaces__msg__ErrorInfo__Sequence__init(motoros2_interfaces__msg__ErrorInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__ErrorInfo * data = NULL;

  if (size) {
    data = (motoros2_interfaces__msg__ErrorInfo *)allocator.zero_allocate(size, sizeof(motoros2_interfaces__msg__ErrorInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motoros2_interfaces__msg__ErrorInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motoros2_interfaces__msg__ErrorInfo__fini(&data[i - 1]);
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
motoros2_interfaces__msg__ErrorInfo__Sequence__fini(motoros2_interfaces__msg__ErrorInfo__Sequence * array)
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
      motoros2_interfaces__msg__ErrorInfo__fini(&array->data[i]);
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

motoros2_interfaces__msg__ErrorInfo__Sequence *
motoros2_interfaces__msg__ErrorInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__ErrorInfo__Sequence * array = (motoros2_interfaces__msg__ErrorInfo__Sequence *)allocator.allocate(sizeof(motoros2_interfaces__msg__ErrorInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motoros2_interfaces__msg__ErrorInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motoros2_interfaces__msg__ErrorInfo__Sequence__destroy(motoros2_interfaces__msg__ErrorInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motoros2_interfaces__msg__ErrorInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motoros2_interfaces__msg__ErrorInfo__Sequence__are_equal(const motoros2_interfaces__msg__ErrorInfo__Sequence * lhs, const motoros2_interfaces__msg__ErrorInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motoros2_interfaces__msg__ErrorInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motoros2_interfaces__msg__ErrorInfo__Sequence__copy(
  const motoros2_interfaces__msg__ErrorInfo__Sequence * input,
  motoros2_interfaces__msg__ErrorInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motoros2_interfaces__msg__ErrorInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motoros2_interfaces__msg__ErrorInfo * data =
      (motoros2_interfaces__msg__ErrorInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motoros2_interfaces__msg__ErrorInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motoros2_interfaces__msg__ErrorInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motoros2_interfaces__msg__ErrorInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
