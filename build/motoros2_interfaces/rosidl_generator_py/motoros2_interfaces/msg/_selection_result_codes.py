# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/SelectionResultCodes.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SelectionResultCodes(type):
    """Metaclass of message 'SelectionResultCodes'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'OK': 0,
        'OK_STR': '',
        'INVALID_CONTROLLER_STATE': 400,
        'INVALID_CONTROLLER_STATE_STR': 'Pendant is not in REMOTE mode',
        'INVALID_CONTROL_GROUP': 401,
        'INVALID_CONTROL_GROUP_STR': 'Invalid control group',
        'INVALID_SELECTION_INDEX': 402,
        'INVALID_SELECTION_INDEX_STR': 'Invalid tool selection',
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
                'motoros2_interfaces.msg.SelectionResultCodes')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__selection_result_codes
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__selection_result_codes
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__selection_result_codes
            cls._TYPE_SUPPORT = module.type_support_msg__msg__selection_result_codes
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__selection_result_codes

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'OK': cls.__constants['OK'],
            'OK_STR': cls.__constants['OK_STR'],
            'INVALID_CONTROLLER_STATE': cls.__constants['INVALID_CONTROLLER_STATE'],
            'INVALID_CONTROLLER_STATE_STR': cls.__constants['INVALID_CONTROLLER_STATE_STR'],
            'INVALID_CONTROL_GROUP': cls.__constants['INVALID_CONTROL_GROUP'],
            'INVALID_CONTROL_GROUP_STR': cls.__constants['INVALID_CONTROL_GROUP_STR'],
            'INVALID_SELECTION_INDEX': cls.__constants['INVALID_SELECTION_INDEX'],
            'INVALID_SELECTION_INDEX_STR': cls.__constants['INVALID_SELECTION_INDEX_STR'],
        }

    @property
    def OK(self):
        """Message constant 'OK'."""
        return Metaclass_SelectionResultCodes.__constants['OK']

    @property
    def OK_STR(self):
        """Message constant 'OK_STR'."""
        return Metaclass_SelectionResultCodes.__constants['OK_STR']

    @property
    def INVALID_CONTROLLER_STATE(self):
        """Message constant 'INVALID_CONTROLLER_STATE'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_CONTROLLER_STATE']

    @property
    def INVALID_CONTROLLER_STATE_STR(self):
        """Message constant 'INVALID_CONTROLLER_STATE_STR'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_CONTROLLER_STATE_STR']

    @property
    def INVALID_CONTROL_GROUP(self):
        """Message constant 'INVALID_CONTROL_GROUP'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_CONTROL_GROUP']

    @property
    def INVALID_CONTROL_GROUP_STR(self):
        """Message constant 'INVALID_CONTROL_GROUP_STR'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_CONTROL_GROUP_STR']

    @property
    def INVALID_SELECTION_INDEX(self):
        """Message constant 'INVALID_SELECTION_INDEX'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_SELECTION_INDEX']

    @property
    def INVALID_SELECTION_INDEX_STR(self):
        """Message constant 'INVALID_SELECTION_INDEX_STR'."""
        return Metaclass_SelectionResultCodes.__constants['INVALID_SELECTION_INDEX_STR']


class SelectionResultCodes(metaclass=Metaclass_SelectionResultCodes):
    """
    Message class 'SelectionResultCodes'.

    Constants:
      OK
      OK_STR
      INVALID_CONTROLLER_STATE
      INVALID_CONTROLLER_STATE_STR
      INVALID_CONTROL_GROUP
      INVALID_CONTROL_GROUP_STR
      INVALID_SELECTION_INDEX
      INVALID_SELECTION_INDEX_STR
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value = kwargs.get('value', int())

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
        if self.value != other.value:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def value(self):
        """Message field 'value'."""
        return self._value

    @value.setter
    def value(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'value' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'value' field must be an unsigned integer in [0, 4294967295]"
        self._value = value
