// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motoros2_interfaces:srv/StartTrajMode.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/srv/detail/start_traj_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
motoros2_interfaces__srv__StartTrajMode_Request__init(motoros2_interfaces__srv__StartTrajMode_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
motoros2_interfaces__srv__StartTrajMode_Request__fini(motoros2_interfaces__srv__StartTrajMode_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
motoros2_interfaces__srv__StartTrajMode_Request__are_equal(const motoros2_interfaces__srv__StartTrajMode_Request * lhs, const motoros2_interfaces__srv__StartTrajMode_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
motoros2_interfaces__srv__StartTrajMode_Request__copy(
  const motoros2_interfaces__srv__StartTrajMode_Request * input,
  motoros2_interfaces__srv__StartTrajMode_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

motoros2_interfaces__srv__StartTrajMode_Request *
motoros2_interfaces__srv__StartTrajMode_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Request * msg = (motoros2_interfaces__srv__StartTrajMode_Request *)allocator.allocate(sizeof(motoros2_interfaces__srv__StartTrajMode_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motoros2_interfaces__srv__StartTrajMode_Request));
  bool success = motoros2_interfaces__srv__StartTrajMode_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motoros2_interfaces__srv__StartTrajMode_Request__destroy(motoros2_interfaces__srv__StartTrajMode_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motoros2_interfaces__srv__StartTrajMode_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__init(motoros2_interfaces__srv__StartTrajMode_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Request * data = NULL;

  if (size) {
    data = (motoros2_interfaces__srv__StartTrajMode_Request *)allocator.zero_allocate(size, sizeof(motoros2_interfaces__srv__StartTrajMode_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motoros2_interfaces__srv__StartTrajMode_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motoros2_interfaces__srv__StartTrajMode_Request__fini(&data[i - 1]);
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
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__fini(motoros2_interfaces__srv__StartTrajMode_Request__Sequence * array)
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
      motoros2_interfaces__srv__StartTrajMode_Request__fini(&array->data[i]);
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

motoros2_interfaces__srv__StartTrajMode_Request__Sequence *
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Request__Sequence * array = (motoros2_interfaces__srv__StartTrajMode_Request__Sequence *)allocator.allocate(sizeof(motoros2_interfaces__srv__StartTrajMode_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motoros2_interfaces__srv__StartTrajMode_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__destroy(motoros2_interfaces__srv__StartTrajMode_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motoros2_interfaces__srv__StartTrajMode_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__are_equal(const motoros2_interfaces__srv__StartTrajMode_Request__Sequence * lhs, const motoros2_interfaces__srv__StartTrajMode_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motoros2_interfaces__srv__StartTrajMode_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motoros2_interfaces__srv__StartTrajMode_Request__Sequence__copy(
  const motoros2_interfaces__srv__StartTrajMode_Request__Sequence * input,
  motoros2_interfaces__srv__StartTrajMode_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motoros2_interfaces__srv__StartTrajMode_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motoros2_interfaces__srv__StartTrajMode_Request * data =
      (motoros2_interfaces__srv__StartTrajMode_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motoros2_interfaces__srv__StartTrajMode_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motoros2_interfaces__srv__StartTrajMode_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motoros2_interfaces__srv__StartTrajMode_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result_code`
#include "motoros2_interfaces/msg/detail/motion_ready_enum__functions.h"
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
motoros2_interfaces__srv__StartTrajMode_Response__init(motoros2_interfaces__srv__StartTrajMode_Response * msg)
{
  if (!msg) {
    return false;
  }
  // result_code
  if (!motoros2_interfaces__msg__MotionReadyEnum__init(&msg->result_code)) {
    motoros2_interfaces__srv__StartTrajMode_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    motoros2_interfaces__srv__StartTrajMode_Response__fini(msg);
    return false;
  }
  return true;
}

void
motoros2_interfaces__srv__StartTrajMode_Response__fini(motoros2_interfaces__srv__StartTrajMode_Response * msg)
{
  if (!msg) {
    return;
  }
  // result_code
  motoros2_interfaces__msg__MotionReadyEnum__fini(&msg->result_code);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
motoros2_interfaces__srv__StartTrajMode_Response__are_equal(const motoros2_interfaces__srv__StartTrajMode_Response * lhs, const motoros2_interfaces__srv__StartTrajMode_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result_code
  if (!motoros2_interfaces__msg__MotionReadyEnum__are_equal(
      &(lhs->result_code), &(rhs->result_code)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
motoros2_interfaces__srv__StartTrajMode_Response__copy(
  const motoros2_interfaces__srv__StartTrajMode_Response * input,
  motoros2_interfaces__srv__StartTrajMode_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // result_code
  if (!motoros2_interfaces__msg__MotionReadyEnum__copy(
      &(input->result_code), &(output->result_code)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

motoros2_interfaces__srv__StartTrajMode_Response *
motoros2_interfaces__srv__StartTrajMode_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Response * msg = (motoros2_interfaces__srv__StartTrajMode_Response *)allocator.allocate(sizeof(motoros2_interfaces__srv__StartTrajMode_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motoros2_interfaces__srv__StartTrajMode_Response));
  bool success = motoros2_interfaces__srv__StartTrajMode_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motoros2_interfaces__srv__StartTrajMode_Response__destroy(motoros2_interfaces__srv__StartTrajMode_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motoros2_interfaces__srv__StartTrajMode_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__init(motoros2_interfaces__srv__StartTrajMode_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Response * data = NULL;

  if (size) {
    data = (motoros2_interfaces__srv__StartTrajMode_Response *)allocator.zero_allocate(size, sizeof(motoros2_interfaces__srv__StartTrajMode_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motoros2_interfaces__srv__StartTrajMode_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motoros2_interfaces__srv__StartTrajMode_Response__fini(&data[i - 1]);
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
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__fini(motoros2_interfaces__srv__StartTrajMode_Response__Sequence * array)
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
      motoros2_interfaces__srv__StartTrajMode_Response__fini(&array->data[i]);
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

motoros2_interfaces__srv__StartTrajMode_Response__Sequence *
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__srv__StartTrajMode_Response__Sequence * array = (motoros2_interfaces__srv__StartTrajMode_Response__Sequence *)allocator.allocate(sizeof(motoros2_interfaces__srv__StartTrajMode_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motoros2_interfaces__srv__StartTrajMode_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__destroy(motoros2_interfaces__srv__StartTrajMode_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motoros2_interfaces__srv__StartTrajMode_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__are_equal(const motoros2_interfaces__srv__StartTrajMode_Response__Sequence * lhs, const motoros2_interfaces__srv__StartTrajMode_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motoros2_interfaces__srv__StartTrajMode_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motoros2_interfaces__srv__StartTrajMode_Response__Sequence__copy(
  const motoros2_interfaces__srv__StartTrajMode_Response__Sequence * input,
  motoros2_interfaces__srv__StartTrajMode_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motoros2_interfaces__srv__StartTrajMode_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motoros2_interfaces__srv__StartTrajMode_Response * data =
      (motoros2_interfaces__srv__StartTrajMode_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motoros2_interfaces__srv__StartTrajMode_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motoros2_interfaces__srv__StartTrajMode_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motoros2_interfaces__srv__StartTrajMode_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
