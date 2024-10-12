# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/IoResultCodes.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_IoResultCodes(type):
    """Metaclass of message 'IoResultCodes'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'OK': 0,
        'OK_STR': 'Success',
        'READ_ADDRESS_INVALID': 1001,
        'READ_ADDRESS_INVALID_STR': 'Address cannot be read from (out of readable range)',
        'WRITE_ADDRESS_INVALID': 1002,
        'WRITE_ADDRESS_INVALID_STR': 'Address cannot be written to (out of writable range)',
        'WRITE_VALUE_INVALID': 1003,
        'WRITE_VALUE_INVALID_STR': 'Illegal value for the type of IO element addressed',
        'READ_API_ERROR': 1004,
        'READ_API_ERROR_STR': 'The MotoPlus function mpReadIO returned -1. No further information is available',
        'WRITE_API_ERROR': 1005,
        'WRITE_API_ERROR_STR': 'The MotoPlus function mpWriteIO returned -1. No further information is available',
        'UNKNOWN_API_ERROR_STR': 'Unknown error accessing I/O. No further information is available',
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
                'motoros2_interfaces.msg.IoResultCodes')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__io_result_codes
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__io_result_codes
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__io_result_codes
            cls._TYPE_SUPPORT = module.type_support_msg__msg__io_result_codes
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__io_result_codes

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'OK': cls.__constants['OK'],
            'OK_STR': cls.__constants['OK_STR'],
            'READ_ADDRESS_INVALID': cls.__constants['READ_ADDRESS_INVALID'],
            'READ_ADDRESS_INVALID_STR': cls.__constants['READ_ADDRESS_INVALID_STR'],
            'WRITE_ADDRESS_INVALID': cls.__constants['WRITE_ADDRESS_INVALID'],
            'WRITE_ADDRESS_INVALID_STR': cls.__constants['WRITE_ADDRESS_INVALID_STR'],
            'WRITE_VALUE_INVALID': cls.__constants['WRITE_VALUE_INVALID'],
            'WRITE_VALUE_INVALID_STR': cls.__constants['WRITE_VALUE_INVALID_STR'],
            'READ_API_ERROR': cls.__constants['READ_API_ERROR'],
            'READ_API_ERROR_STR': cls.__constants['READ_API_ERROR_STR'],
            'WRITE_API_ERROR': cls.__constants['WRITE_API_ERROR'],
            'WRITE_API_ERROR_STR': cls.__constants['WRITE_API_ERROR_STR'],
            'UNKNOWN_API_ERROR_STR': cls.__constants['UNKNOWN_API_ERROR_STR'],
        }

    @property
    def OK(self):
        """Message constant 'OK'."""
        return Metaclass_IoResultCodes.__constants['OK']

    @property
    def OK_STR(self):
        """Message constant 'OK_STR'."""
        return Metaclass_IoResultCodes.__constants['OK_STR']

    @property
    def READ_ADDRESS_INVALID(self):
        """Message constant 'READ_ADDRESS_INVALID'."""
        return Metaclass_IoResultCodes.__constants['READ_ADDRESS_INVALID']

    @property
    def READ_ADDRESS_INVALID_STR(self):
        """Message constant 'READ_ADDRESS_INVALID_STR'."""
        return Metaclass_IoResultCodes.__constants['READ_ADDRESS_INVALID_STR']

    @property
    def WRITE_ADDRESS_INVALID(self):
        """Message constant 'WRITE_ADDRESS_INVALID'."""
        return Metaclass_IoResultCodes.__constants['WRITE_ADDRESS_INVALID']

    @property
    def WRITE_ADDRESS_INVALID_STR(self):
        """Message constant 'WRITE_ADDRESS_INVALID_STR'."""
        return Metaclass_IoResultCodes.__constants['WRITE_ADDRESS_INVALID_STR']

    @property
    def WRITE_VALUE_INVALID(self):
        """Message constant 'WRITE_VALUE_INVALID'."""
        return Metaclass_IoResultCodes.__constants['WRITE_VALUE_INVALID']

    @property
    def WRITE_VALUE_INVALID_STR(self):
        """Message constant 'WRITE_VALUE_INVALID_STR'."""
        return Metaclass_IoResultCodes.__constants['WRITE_VALUE_INVALID_STR']

    @property
    def READ_API_ERROR(self):
        """Message constant 'READ_API_ERROR'."""
        return Metaclass_IoResultCodes.__constants['READ_API_ERROR']

    @property
    def READ_API_ERROR_STR(self):
        """Message constant 'READ_API_ERROR_STR'."""
        return Metaclass_IoResultCodes.__constants['READ_API_ERROR_STR']

    @property
    def WRITE_API_ERROR(self):
        """Message constant 'WRITE_API_ERROR'."""
        return Metaclass_IoResultCodes.__constants['WRITE_API_ERROR']

    @property
    def WRITE_API_ERROR_STR(self):
        """Message constant 'WRITE_API_ERROR_STR'."""
        return Metaclass_IoResultCodes.__constants['WRITE_API_ERROR_STR']

    @property
    def UNKNOWN_API_ERROR_STR(self):
        """Message constant 'UNKNOWN_API_ERROR_STR'."""
        return Metaclass_IoResultCodes.__constants['UNKNOWN_API_ERROR_STR']


class IoResultCodes(metaclass=Metaclass_IoResultCodes):
    """
    Message class 'IoResultCodes'.

    Constants:
      OK
      OK_STR
      READ_ADDRESS_INVALID
      READ_ADDRESS_INVALID_STR
      WRITE_ADDRESS_INVALID
      WRITE_ADDRESS_INVALID_STR
      WRITE_VALUE_INVALID
      WRITE_VALUE_INVALID_STR
      READ_API_ERROR
      READ_API_ERROR_STR
      WRITE_API_ERROR
      WRITE_API_ERROR_STR
      UNKNOWN_API_ERROR_STR
    """

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
