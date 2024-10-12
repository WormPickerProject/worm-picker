// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
// generated code does not contain a copyright notice
#include "motoros2_interfaces/msg/detail/inform_job_crud_result_codes__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motoros2_interfaces__msg__InformJobCrudResultCodes__init(motoros2_interfaces__msg__InformJobCrudResultCodes * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
motoros2_interfaces__msg__InformJobCrudResultCodes__fini(motoros2_interfaces__msg__InformJobCrudResultCodes * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
motoros2_interfaces__msg__InformJobCrudResultCodes__are_equal(const motoros2_interfaces__msg__InformJobCrudResultCodes * lhs, const motoros2_interfaces__msg__InformJobCrudResultCodes * rhs)
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
motoros2_interfaces__msg__InformJobCrudResultCodes__copy(
  const motoros2_interfaces__msg__InformJobCrudResultCodes * input,
  motoros2_interfaces__msg__InformJobCrudResultCodes * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

motoros2_interfaces__msg__InformJobCrudResultCodes *
motoros2_interfaces__msg__InformJobCrudResultCodes__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__InformJobCrudResultCodes * msg = (motoros2_interfaces__msg__InformJobCrudResultCodes *)allocator.allocate(sizeof(motoros2_interfaces__msg__InformJobCrudResultCodes), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motoros2_interfaces__msg__InformJobCrudResultCodes));
  bool success = motoros2_interfaces__msg__InformJobCrudResultCodes__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motoros2_interfaces__msg__InformJobCrudResultCodes__destroy(motoros2_interfaces__msg__InformJobCrudResultCodes * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motoros2_interfaces__msg__InformJobCrudResultCodes__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__init(motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__InformJobCrudResultCodes * data = NULL;

  if (size) {
    data = (motoros2_interfaces__msg__InformJobCrudResultCodes *)allocator.zero_allocate(size, sizeof(motoros2_interfaces__msg__InformJobCrudResultCodes), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motoros2_interfaces__msg__InformJobCrudResultCodes__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motoros2_interfaces__msg__InformJobCrudResultCodes__fini(&data[i - 1]);
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
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__fini(motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * array)
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
      motoros2_interfaces__msg__InformJobCrudResultCodes__fini(&array->data[i]);
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

motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence *
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * array = (motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence *)allocator.allocate(sizeof(motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__destroy(motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__are_equal(const motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * lhs, const motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motoros2_interfaces__msg__InformJobCrudResultCodes__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence__copy(
  const motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * input,
  motoros2_interfaces__msg__InformJobCrudResultCodes__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motoros2_interfaces__msg__InformJobCrudResultCodes);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motoros2_interfaces__msg__InformJobCrudResultCodes * data =
      (motoros2_interfaces__msg__InformJobCrudResultCodes *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motoros2_interfaces__msg__InformJobCrudResultCodes__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motoros2_interfaces__msg__InformJobCrudResultCodes__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motoros2_interfaces__msg__InformJobCrudResultCodes__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
