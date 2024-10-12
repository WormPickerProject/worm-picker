# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/AlarmInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AlarmInfo(type):
    """Metaclass of message 'AlarmInfo'."""

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
                'motoros2_interfaces.msg.AlarmInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__alarm_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__alarm_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__alarm_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__alarm_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__alarm_info

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

            from motoros2_interfaces.msg import AlarmCauseRemedy
            if AlarmCauseRemedy.__class__._TYPE_SUPPORT is None:
                AlarmCauseRemedy.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class AlarmInfo(metaclass=Metaclass_AlarmInfo):
    """Message class 'AlarmInfo'."""

    __slots__ = [
        '_number',
        '_message',
        '_sub_code',
        '_datetime',
        '_contents',
        '_description',
        '_help',
    ]

    _fields_and_field_types = {
        'number': 'uint32',
        'message': 'string',
        'sub_code': 'int32',
        'datetime': 'builtin_interfaces/Time',
        'contents': 'string',
        'description': 'string',
        'help': 'sequence<motoros2_interfaces/AlarmCauseRemedy>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['motoros2_interfaces', 'msg'], 'AlarmCauseRemedy')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.number = kwargs.get('number', int())
        self.message = kwargs.get('message', str())
        self.sub_code = kwargs.get('sub_code', int())
        from builtin_interfaces.msg import Time
        self.datetime = kwargs.get('datetime', Time())
        self.contents = kwargs.get('contents', str())
        self.description = kwargs.get('description', str())
        self.help = kwargs.get('help', [])

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
        if self.number != other.number:
            return False
        if self.message != other.message:
            return False
        if self.sub_code != other.sub_code:
            return False
        if self.datetime != other.datetime:
            return False
        if self.contents != other.contents:
            return False
        if self.description != other.description:
            return False
        if self.help != other.help:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def number(self):
        """Message field 'number'."""
        return self._number

    @number.setter
    def number(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'number' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'number' field must be an unsigned integer in [0, 4294967295]"
        self._number = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value

    @builtins.property
    def sub_code(self):
        """Message field 'sub_code'."""
        return self._sub_code

    @sub_code.setter
    def sub_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sub_code' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'sub_code' field must be an integer in [-2147483648, 2147483647]"
        self._sub_code = value

    @builtins.property
    def datetime(self):
        """Message field 'datetime'."""
        return self._datetime

    @datetime.setter
    def datetime(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'datetime' field must be a sub message of type 'Time'"
        self._datetime = value

    @builtins.property
    def contents(self):
        """Message field 'contents'."""
        return self._contents

    @contents.setter
    def contents(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'contents' field must be of type 'str'"
        self._contents = value

    @builtins.property
    def description(self):
        """Message field 'description'."""
        return self._description

    @description.setter
    def description(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'description' field must be of type 'str'"
        self._description = value

    @builtins.property  # noqa: A003
    def help(self):  # noqa: A003
        """Message field 'help'."""
        return self._help

    @help.setter  # noqa: A003
    def help(self, value):  # noqa: A003
        if __debug__:
            from motoros2_interfaces.msg import AlarmCauseRemedy
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
                 all(isinstance(v, AlarmCauseRemedy) for v in value) and
                 True), \
                "The 'help' field must be a set or sequence and each value of type 'AlarmCauseRemedy'"
        self._help = value
