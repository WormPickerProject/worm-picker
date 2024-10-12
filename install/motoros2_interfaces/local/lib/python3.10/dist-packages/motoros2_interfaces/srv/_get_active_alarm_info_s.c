// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.h"
#include "motoros2_interfaces/srv/detail/get_active_alarm_info__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool motoros2_interfaces__srv__get_active_alarm_info__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[74];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("motoros2_interfaces.srv._get_active_alarm_info.GetActiveAlarmInfo_Request", full_classname_dest, 73) == 0);
  }
  motoros2_interfaces__srv__GetActiveAlarmInfo_Request * ros_message = _ros_message;
  ros_message->structure_needs_at_least_one_member = 0;

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * motoros2_interfaces__srv__get_active_alarm_info__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetActiveAlarmInfo_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("motoros2_interfaces.srv._get_active_alarm_info");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetActiveAlarmInfo_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  (void)raw_ros_message;

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__struct.h"
// already included above
// #include "motoros2_interfaces/srv/detail/get_active_alarm_info__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "motoros2_interfaces/msg/detail/alarm_info__functions.h"
#include "motoros2_interfaces/msg/detail/error_info__functions.h"
// end nested array functions include
bool motoros2_interfaces__msg__alarm_info__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * motoros2_interfaces__msg__alarm_info__convert_to_py(void * raw_ros_message);
bool motoros2_interfaces__msg__error_info__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * motoros2_interfaces__msg__error_info__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool motoros2_interfaces__srv__get_active_alarm_info__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[75];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("motoros2_interfaces.srv._get_active_alarm_info.GetActiveAlarmInfo_Response", full_classname_dest, 74) == 0);
  }
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response * ros_message = _ros_message;
  {  // result_code
    PyObject * field = PyObject_GetAttrString(_pymsg, "result_code");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->result_code = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // result_message
    PyObject * field = PyObject_GetAttrString(_pymsg, "result_message");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->result_message, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // alarms
    PyObject * field = PyObject_GetAttrString(_pymsg, "alarms");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'alarms'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!motoros2_interfaces__msg__AlarmInfo__Sequence__init(&(ros_message->alarms), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create motoros2_interfaces__msg__AlarmInfo__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    motoros2_interfaces__msg__AlarmInfo * dest = ros_message->alarms.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!motoros2_interfaces__msg__alarm_info__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // errors
    PyObject * field = PyObject_GetAttrString(_pymsg, "errors");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'errors'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!motoros2_interfaces__msg__ErrorInfo__Sequence__init(&(ros_message->errors), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create motoros2_interfaces__msg__ErrorInfo__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    motoros2_interfaces__msg__ErrorInfo * dest = ros_message->errors.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!motoros2_interfaces__msg__error_info__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * motoros2_interfaces__srv__get_active_alarm_info__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GetActiveAlarmInfo_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("motoros2_interfaces.srv._get_active_alarm_info");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GetActiveAlarmInfo_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  motoros2_interfaces__srv__GetActiveAlarmInfo_Response * ros_message = (motoros2_interfaces__srv__GetActiveAlarmInfo_Response *)raw_ros_message;
  {  // result_code
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->result_code);
    {
      int rc = PyObject_SetAttrString(_pymessage, "result_code", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // result_message
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->result_message.data,
      strlen(ros_message->result_message.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "result_message", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // alarms
    PyObject * field = NULL;
    size_t size = ros_message->alarms.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    motoros2_interfaces__msg__AlarmInfo * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->alarms.data[i]);
      PyObject * pyitem = motoros2_interfaces__msg__alarm_info__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "alarms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // errors
    PyObject * field = NULL;
    size_t size = ros_message->errors.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    motoros2_interfaces__msg__ErrorInfo * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->errors.data[i]);
      PyObject * pyitem = motoros2_interfaces__msg__error_info__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "errors", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
