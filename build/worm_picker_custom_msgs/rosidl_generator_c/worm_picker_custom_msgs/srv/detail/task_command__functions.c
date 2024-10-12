// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from worm_picker_custom_msgs:srv/TaskCommand.idl
// generated code does not contain a copyright notice
#include "worm_picker_custom_msgs/srv/detail/task_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `command`
#include "rosidl_runtime_c/string_functions.h"

bool
worm_picker_custom_msgs__srv__TaskCommand_Request__init(worm_picker_custom_msgs__srv__TaskCommand_Request * msg)
{
  if (!msg) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__init(&msg->command)) {
    worm_picker_custom_msgs__srv__TaskCommand_Request__fini(msg);
    return false;
  }
  return true;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Request__fini(worm_picker_custom_msgs__srv__TaskCommand_Request * msg)
{
  if (!msg) {
    return;
  }
  // command
  rosidl_runtime_c__String__fini(&msg->command);
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Request__are_equal(const worm_picker_custom_msgs__srv__TaskCommand_Request * lhs, const worm_picker_custom_msgs__srv__TaskCommand_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->command), &(rhs->command)))
  {
    return false;
  }
  return true;
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Request__copy(
  const worm_picker_custom_msgs__srv__TaskCommand_Request * input,
  worm_picker_custom_msgs__srv__TaskCommand_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__copy(
      &(input->command), &(output->command)))
  {
    return false;
  }
  return true;
}

worm_picker_custom_msgs__srv__TaskCommand_Request *
worm_picker_custom_msgs__srv__TaskCommand_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Request * msg = (worm_picker_custom_msgs__srv__TaskCommand_Request *)allocator.allocate(sizeof(worm_picker_custom_msgs__srv__TaskCommand_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(worm_picker_custom_msgs__srv__TaskCommand_Request));
  bool success = worm_picker_custom_msgs__srv__TaskCommand_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Request__destroy(worm_picker_custom_msgs__srv__TaskCommand_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    worm_picker_custom_msgs__srv__TaskCommand_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__init(worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Request * data = NULL;

  if (size) {
    data = (worm_picker_custom_msgs__srv__TaskCommand_Request *)allocator.zero_allocate(size, sizeof(worm_picker_custom_msgs__srv__TaskCommand_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = worm_picker_custom_msgs__srv__TaskCommand_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        worm_picker_custom_msgs__srv__TaskCommand_Request__fini(&data[i - 1]);
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
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__fini(worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * array)
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
      worm_picker_custom_msgs__srv__TaskCommand_Request__fini(&array->data[i]);
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

worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence *
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * array = (worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence *)allocator.allocate(sizeof(worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__destroy(worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__are_equal(const worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * lhs, const worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!worm_picker_custom_msgs__srv__TaskCommand_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence__copy(
  const worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * input,
  worm_picker_custom_msgs__srv__TaskCommand_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(worm_picker_custom_msgs__srv__TaskCommand_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    worm_picker_custom_msgs__srv__TaskCommand_Request * data =
      (worm_picker_custom_msgs__srv__TaskCommand_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!worm_picker_custom_msgs__srv__TaskCommand_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          worm_picker_custom_msgs__srv__TaskCommand_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!worm_picker_custom_msgs__srv__TaskCommand_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
worm_picker_custom_msgs__srv__TaskCommand_Response__init(worm_picker_custom_msgs__srv__TaskCommand_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Response__fini(worm_picker_custom_msgs__srv__TaskCommand_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Response__are_equal(const worm_picker_custom_msgs__srv__TaskCommand_Response * lhs, const worm_picker_custom_msgs__srv__TaskCommand_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Response__copy(
  const worm_picker_custom_msgs__srv__TaskCommand_Response * input,
  worm_picker_custom_msgs__srv__TaskCommand_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

worm_picker_custom_msgs__srv__TaskCommand_Response *
worm_picker_custom_msgs__srv__TaskCommand_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Response * msg = (worm_picker_custom_msgs__srv__TaskCommand_Response *)allocator.allocate(sizeof(worm_picker_custom_msgs__srv__TaskCommand_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(worm_picker_custom_msgs__srv__TaskCommand_Response));
  bool success = worm_picker_custom_msgs__srv__TaskCommand_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Response__destroy(worm_picker_custom_msgs__srv__TaskCommand_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    worm_picker_custom_msgs__srv__TaskCommand_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__init(worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Response * data = NULL;

  if (size) {
    data = (worm_picker_custom_msgs__srv__TaskCommand_Response *)allocator.zero_allocate(size, sizeof(worm_picker_custom_msgs__srv__TaskCommand_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = worm_picker_custom_msgs__srv__TaskCommand_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        worm_picker_custom_msgs__srv__TaskCommand_Response__fini(&data[i - 1]);
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
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__fini(worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * array)
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
      worm_picker_custom_msgs__srv__TaskCommand_Response__fini(&array->data[i]);
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

worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence *
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * array = (worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence *)allocator.allocate(sizeof(worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__destroy(worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__are_equal(const worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * lhs, const worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!worm_picker_custom_msgs__srv__TaskCommand_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence__copy(
  const worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * input,
  worm_picker_custom_msgs__srv__TaskCommand_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(worm_picker_custom_msgs__srv__TaskCommand_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    worm_picker_custom_msgs__srv__TaskCommand_Response * data =
      (worm_picker_custom_msgs__srv__TaskCommand_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!worm_picker_custom_msgs__srv__TaskCommand_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          worm_picker_custom_msgs__srv__TaskCommand_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!worm_picker_custom_msgs__srv__TaskCommand_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
