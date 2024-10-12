# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:srv/GetActiveAlarmInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetActiveAlarmInfo_Request(type):
    """Metaclass of message 'GetActiveAlarmInfo_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('motoros2_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'motoros2_interfaces.srv.GetActiveAlarmInfo_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_active_alarm_info__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_active_alarm_info__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_active_alarm_info__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_active_alarm_info__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_active_alarm_info__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetActiveAlarmInfo_Request(metaclass=Metaclass_GetActiveAlarmInfo_Request):
    """Message class 'GetActiveAlarmInfo_Request'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetActiveAlarmInfo_Response(type):
    """Metaclass of message 'GetActiveAlarmInfo_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('motoros2_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'motoros2_interfaces.srv.GetActiveAlarmInfo_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_active_alarm_info__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_active_alarm_info__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_active_alarm_info__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_active_alarm_info__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_active_alarm_info__response

            from motoros2_interfaces.msg import AlarmInfo
            if AlarmInfo.__class__._TYPE_SUPPORT is None:
                AlarmInfo.__class__.__import_type_support__()

            from motoros2_interfaces.msg import ErrorInfo
            if ErrorInfo.__class__._TYPE_SUPPORT is None:
                ErrorInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetActiveAlarmInfo_Response(metaclass=Metaclass_GetActiveAlarmInfo_Response):
    """Message class 'GetActiveAlarmInfo_Response'."""

    __slots__ = [
        '_result_code',
        '_result_message',
        '_alarms',
        '_errors',
    ]

    _fields_and_field_types = {
        'result_code': 'uint32',
        'result_message': 'string',
        'alarms': 'sequence<motoros2_interfaces/AlarmInfo>',
        'errors': 'sequence<motoros2_interfaces/ErrorInfo>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['motoros2_interfaces', 'msg'], 'AlarmInfo')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['motoros2_interfaces', 'msg'], 'ErrorInfo')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.result_code = kwargs.get('result_code', int())
        self.result_message = kwargs.get('result_message', str())
        self.alarms = kwargs.get('alarms', [])
        self.errors = kwargs.get('errors', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.result_code != other.result_code:
            return False
        if self.result_message != other.result_message:
            return False
        if self.alarms != other.alarms:
            return False
        if self.errors != other.errors:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def result_code(self):
        """Message field 'result_code'."""
        return self._result_code

    @result_code.setter
    def result_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'result_code' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'result_code' field must be an unsigned integer in [0, 4294967295]"
        self._result_code = value

    @builtins.property
    def result_message(self):
        """Message field 'result_message'."""
        return self._result_message

    @result_message.setter
    def result_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'result_message' field must be of type 'str'"
        self._result_message = value

    @builtins.property
    def alarms(self):
        """Message field 'alarms'."""
        return self._alarms

    @alarms.setter
    def alarms(self, value):
        if __debug__:
            from motoros2_interfaces.msg import AlarmInfo
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, AlarmInfo) for v in value) and
                 True), \
                "The 'alarms' field must be a set or sequence and each value of type 'AlarmInfo'"
        self._alarms = value

    @builtins.property
    def errors(self):
        """Message field 'errors'."""
        return self._errors

    @errors.setter
    def errors(self, value):
        if __debug__:
            from motoros2_interfaces.msg import ErrorInfo
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, ErrorInfo) for v in value) and
                 True), \
                "The 'errors' field must be a set or sequence and each value of type 'ErrorInfo'"
        self._errors = value


class Metaclass_GetActiveAlarmInfo(type):
    """Metaclass of service 'GetActiveAlarmInfo'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('motoros2_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'motoros2_interfaces.srv.GetActiveAlarmInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_active_alarm_info

            from motoros2_interfaces.srv import _get_active_alarm_info
            if _get_active_alarm_info.Metaclass_GetActiveAlarmInfo_Request._TYPE_SUPPORT is None:
                _get_active_alarm_info.Metaclass_GetActiveAlarmInfo_Request.__import_type_support__()
            if _get_active_alarm_info.Metaclass_GetActiveAlarmInfo_Response._TYPE_SUPPORT is None:
                _get_active_alarm_info.Metaclass_GetActiveAlarmInfo_Response.__import_type_support__()


class GetActiveAlarmInfo(metaclass=Metaclass_GetActiveAlarmInfo):
    from motoros2_interfaces.srv._get_active_alarm_info import GetActiveAlarmInfo_Request as Request
    from motoros2_interfaces.srv._get_active_alarm_info import GetActiveAlarmInfo_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
