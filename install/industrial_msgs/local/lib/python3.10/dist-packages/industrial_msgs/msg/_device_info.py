# generated from rosidl_generator_py/resource/_idl.py.em
# with input from industrial_msgs:msg/DeviceInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DeviceInfo(type):
    """Metaclass of message 'DeviceInfo'."""

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
            module = import_type_support('industrial_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'industrial_msgs.msg.DeviceInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__device_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__device_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__device_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__device_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__device_info

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class DeviceInfo(metaclass=Metaclass_DeviceInfo):
    """Message class 'DeviceInfo'."""

    __slots__ = [
        '_model',
        '_serial_number',
        '_hw_version',
        '_sw_version',
        '_address',
    ]

    _fields_and_field_types = {
        'model': 'string',
        'serial_number': 'string',
        'hw_version': 'string',
        'sw_version': 'string',
        'address': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.model = kwargs.get('model', str())
        self.serial_number = kwargs.get('serial_number', str())
        self.hw_version = kwargs.get('hw_version', str())
        self.sw_version = kwargs.get('sw_version', str())
        self.address = kwargs.get('address', str())

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
        if self.model != other.model:
            return False
        if self.serial_number != other.serial_number:
            return False
        if self.hw_version != other.hw_version:
            return False
        if self.sw_version != other.sw_version:
            return False
        if self.address != other.address:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def model(self):
        """Message field 'model'."""
        return self._model

    @model.setter
    def model(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'model' field must be of type 'str'"
        self._model = value

    @builtins.property
    def serial_number(self):
        """Message field 'serial_number'."""
        return self._serial_number

    @serial_number.setter
    def serial_number(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'serial_number' field must be of type 'str'"
        self._serial_number = value

    @builtins.property
    def hw_version(self):
        """Message field 'hw_version'."""
        return self._hw_version

    @hw_version.setter
    def hw_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'hw_version' field must be of type 'str'"
        self._hw_version = value

    @builtins.property
    def sw_version(self):
        """Message field 'sw_version'."""
        return self._sw_version

    @sw_version.setter
    def sw_version(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'sw_version' field must be of type 'str'"
        self._sw_version = value

    @builtins.property
    def address(self):
        """Message field 'address'."""
        return self._address

    @address.setter
    def address(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'address' field must be of type 'str'"
        self._address = value
