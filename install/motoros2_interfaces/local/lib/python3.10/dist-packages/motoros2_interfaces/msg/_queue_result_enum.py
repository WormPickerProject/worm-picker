# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/QueueResultEnum.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_QueueResultEnum(type):
    """Metaclass of message 'QueueResultEnum'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'SUCCESS': 1,
        'SUCCESS_STR': '',
        'WRONG_MODE': 2,
        'WRONG_MODE_STR': 'Must call start_point_queue_mode service',
        'INIT_FAILURE': 3,
        'INIT_FAILURE_STR': 'Failed to initialize the streaming trajectory',
        'BUSY': 4,
        'BUSY_STR': 'Busy processing the previous trajectory point. Please resend the next point shortly',
        'INVALID_JOINT_LIST': 5,
        'INVALID_JOINT_LIST_STR': 'Point must contain data for all joints',
        'UNABLE_TO_PROCESS_POINT': 6,
        'UNABLE_TO_PROCESS_POINT_STR': 'Error while processing the trajectory point. Check debug log for more details',
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
                'motoros2_interfaces.msg.QueueResultEnum')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__queue_result_enum
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__queue_result_enum
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__queue_result_enum
            cls._TYPE_SUPPORT = module.type_support_msg__msg__queue_result_enum
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__queue_result_enum

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'SUCCESS': cls.__constants['SUCCESS'],
            'SUCCESS_STR': cls.__constants['SUCCESS_STR'],
            'WRONG_MODE': cls.__constants['WRONG_MODE'],
            'WRONG_MODE_STR': cls.__constants['WRONG_MODE_STR'],
            'INIT_FAILURE': cls.__constants['INIT_FAILURE'],
            'INIT_FAILURE_STR': cls.__constants['INIT_FAILURE_STR'],
            'BUSY': cls.__constants['BUSY'],
            'BUSY_STR': cls.__constants['BUSY_STR'],
            'INVALID_JOINT_LIST': cls.__constants['INVALID_JOINT_LIST'],
            'INVALID_JOINT_LIST_STR': cls.__constants['INVALID_JOINT_LIST_STR'],
            'UNABLE_TO_PROCESS_POINT': cls.__constants['UNABLE_TO_PROCESS_POINT'],
            'UNABLE_TO_PROCESS_POINT_STR': cls.__constants['UNABLE_TO_PROCESS_POINT_STR'],
        }

    @property
    def SUCCESS(self):
        """Message constant 'SUCCESS'."""
        return Metaclass_QueueResultEnum.__constants['SUCCESS']

    @property
    def SUCCESS_STR(self):
        """Message constant 'SUCCESS_STR'."""
        return Metaclass_QueueResultEnum.__constants['SUCCESS_STR']

    @property
    def WRONG_MODE(self):
        """Message constant 'WRONG_MODE'."""
        return Metaclass_QueueResultEnum.__constants['WRONG_MODE']

    @property
    def WRONG_MODE_STR(self):
        """Message constant 'WRONG_MODE_STR'."""
        return Metaclass_QueueResultEnum.__constants['WRONG_MODE_STR']

    @property
    def INIT_FAILURE(self):
        """Message constant 'INIT_FAILURE'."""
        return Metaclass_QueueResultEnum.__constants['INIT_FAILURE']

    @property
    def INIT_FAILURE_STR(self):
        """Message constant 'INIT_FAILURE_STR'."""
        return Metaclass_QueueResultEnum.__constants['INIT_FAILURE_STR']

    @property
    def BUSY(self):
        """Message constant 'BUSY'."""
        return Metaclass_QueueResultEnum.__constants['BUSY']

    @property
    def BUSY_STR(self):
        """Message constant 'BUSY_STR'."""
        return Metaclass_QueueResultEnum.__constants['BUSY_STR']

    @property
    def INVALID_JOINT_LIST(self):
        """Message constant 'INVALID_JOINT_LIST'."""
        return Metaclass_QueueResultEnum.__constants['INVALID_JOINT_LIST']

    @property
    def INVALID_JOINT_LIST_STR(self):
        """Message constant 'INVALID_JOINT_LIST_STR'."""
        return Metaclass_QueueResultEnum.__constants['INVALID_JOINT_LIST_STR']

    @property
    def UNABLE_TO_PROCESS_POINT(self):
        """Message constant 'UNABLE_TO_PROCESS_POINT'."""
        return Metaclass_QueueResultEnum.__constants['UNABLE_TO_PROCESS_POINT']

    @property
    def UNABLE_TO_PROCESS_POINT_STR(self):
        """Message constant 'UNABLE_TO_PROCESS_POINT_STR'."""
        return Metaclass_QueueResultEnum.__constants['UNABLE_TO_PROCESS_POINT_STR']


class QueueResultEnum(metaclass=Metaclass_QueueResultEnum):
    """
    Message class 'QueueResultEnum'.

    Constants:
      SUCCESS
      SUCCESS_STR
      WRONG_MODE
      WRONG_MODE_STR
      INIT_FAILURE
      INIT_FAILURE_STR
      BUSY
      BUSY_STR
      INVALID_JOINT_LIST
      INVALID_JOINT_LIST_STR
      UNABLE_TO_PROCESS_POINT
      UNABLE_TO_PROCESS_POINT_STR
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
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
            assert value >= 0 and value < 256, \
                "The 'value' field must be an unsigned integer in [0, 255]"
        self._value = value
