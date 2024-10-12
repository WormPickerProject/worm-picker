# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/MotionReadyEnum.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotionReadyEnum(type):
    """Metaclass of message 'MotionReadyEnum'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'READY': 1,
        'READY_STR': 'Ready',
        'NOT_READY_UNSPECIFIED': 100,
        'NOT_READY_UNSPECIFIED_STR': 'Unspecified',
        'NOT_READY_ALARM': 101,
        'NOT_READY_ALARM_STR': 'The controller has an active Alarm',
        'NOT_READY_ERROR': 102,
        'NOT_READY_ERROR_STR': 'The controller has an active Error',
        'NOT_READY_ESTOP': 103,
        'NOT_READY_ESTOP_STR': 'The controller is in E-Stop',
        'NOT_READY_NOT_PLAY': 104,
        'NOT_READY_NOT_PLAY_STR': 'The teach pendant must not be in TEACH mode',
        'NOT_READY_NOT_REMOTE': 105,
        'NOT_READY_NOT_REMOTE_STR': 'The teach pendant must be in REMOTE mode',
        'NOT_READY_SERVO_OFF': 106,
        'NOT_READY_SERVO_OFF_STR': 'Servo power is OFF. Please call start_traj_mode or start_point_queue_mode service',
        'NOT_READY_HOLD': 107,
        'NOT_READY_HOLD_STR': 'The controller is in HOLD',
        'NOT_READY_JOB_NOT_STARTED': 108,
        'NOT_READY_JOB_NOT_STARTED_STR': 'The INIT_ROS job has not started. Please call start_traj_mode or start_point_queue_mode service',
        'NOT_READY_NOT_ON_WAIT_CMD': 109,
        'NOT_READY_NOT_ON_WAIT_CMD_STR': 'INFORM job is not on a WAIT command. Check the format of INIT_ROS',
        'NOT_READY_PFL_ACTIVE': 111,
        'NOT_READY_PFL_ACTIVE_STR': 'A PFL event has occurred. Please return the robot to a safe state',
        'NOT_READY_INC_MOVE_ERROR': 112,
        'NOT_READY_INC_MOVE_ERROR_STR': 'The controller is in an error state. Please call reset_error to attempt to clear the error',
        'NOT_READY_OTHER_PROGRAM_RUNNING': 113,
        'NOT_READY_OTHER_PROGRAM_RUNNING_STR': 'Controller is running another job',
        'NOT_READY_OTHER_TRAJ_MODE_ACTIVE': 114,
        'NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR': 'Another trajectory mode is already active. Please call stop_traj_mode service',
        'NOT_READY_NOT_CONT_CYCLE_MODE': 115,
        'NOT_READY_NOT_CONT_CYCLE_MODE_STR': 'AUTO cycle mode not set. Please set the cycle mode to AUTO',
        'NOT_READY_MAJOR_ALARM': 116,
        'NOT_READY_MAJOR_ALARM_STR': "Major Alarms can't be reset. Please check the teach pendant",
        'NOT_READY_ECO_MODE': 117,
        'NOT_READY_ECO_MODE_STR': "Couldn't disable eco mode",
        'NOT_READY_SERVO_ON_TIMEOUT': 118,
        'NOT_READY_SERVO_ON_TIMEOUT_STR': 'Timed out while waiting for servo on',
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
                'motoros2_interfaces.msg.MotionReadyEnum')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motion_ready_enum
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motion_ready_enum
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motion_ready_enum
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motion_ready_enum
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motion_ready_enum

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'READY': cls.__constants['READY'],
            'READY_STR': cls.__constants['READY_STR'],
            'NOT_READY_UNSPECIFIED': cls.__constants['NOT_READY_UNSPECIFIED'],
            'NOT_READY_UNSPECIFIED_STR': cls.__constants['NOT_READY_UNSPECIFIED_STR'],
            'NOT_READY_ALARM': cls.__constants['NOT_READY_ALARM'],
            'NOT_READY_ALARM_STR': cls.__constants['NOT_READY_ALARM_STR'],
            'NOT_READY_ERROR': cls.__constants['NOT_READY_ERROR'],
            'NOT_READY_ERROR_STR': cls.__constants['NOT_READY_ERROR_STR'],
            'NOT_READY_ESTOP': cls.__constants['NOT_READY_ESTOP'],
            'NOT_READY_ESTOP_STR': cls.__constants['NOT_READY_ESTOP_STR'],
            'NOT_READY_NOT_PLAY': cls.__constants['NOT_READY_NOT_PLAY'],
            'NOT_READY_NOT_PLAY_STR': cls.__constants['NOT_READY_NOT_PLAY_STR'],
            'NOT_READY_NOT_REMOTE': cls.__constants['NOT_READY_NOT_REMOTE'],
            'NOT_READY_NOT_REMOTE_STR': cls.__constants['NOT_READY_NOT_REMOTE_STR'],
            'NOT_READY_SERVO_OFF': cls.__constants['NOT_READY_SERVO_OFF'],
            'NOT_READY_SERVO_OFF_STR': cls.__constants['NOT_READY_SERVO_OFF_STR'],
            'NOT_READY_HOLD': cls.__constants['NOT_READY_HOLD'],
            'NOT_READY_HOLD_STR': cls.__constants['NOT_READY_HOLD_STR'],
            'NOT_READY_JOB_NOT_STARTED': cls.__constants['NOT_READY_JOB_NOT_STARTED'],
            'NOT_READY_JOB_NOT_STARTED_STR': cls.__constants['NOT_READY_JOB_NOT_STARTED_STR'],
            'NOT_READY_NOT_ON_WAIT_CMD': cls.__constants['NOT_READY_NOT_ON_WAIT_CMD'],
            'NOT_READY_NOT_ON_WAIT_CMD_STR': cls.__constants['NOT_READY_NOT_ON_WAIT_CMD_STR'],
            'NOT_READY_PFL_ACTIVE': cls.__constants['NOT_READY_PFL_ACTIVE'],
            'NOT_READY_PFL_ACTIVE_STR': cls.__constants['NOT_READY_PFL_ACTIVE_STR'],
            'NOT_READY_INC_MOVE_ERROR': cls.__constants['NOT_READY_INC_MOVE_ERROR'],
            'NOT_READY_INC_MOVE_ERROR_STR': cls.__constants['NOT_READY_INC_MOVE_ERROR_STR'],
            'NOT_READY_OTHER_PROGRAM_RUNNING': cls.__constants['NOT_READY_OTHER_PROGRAM_RUNNING'],
            'NOT_READY_OTHER_PROGRAM_RUNNING_STR': cls.__constants['NOT_READY_OTHER_PROGRAM_RUNNING_STR'],
            'NOT_READY_OTHER_TRAJ_MODE_ACTIVE': cls.__constants['NOT_READY_OTHER_TRAJ_MODE_ACTIVE'],
            'NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR': cls.__constants['NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR'],
            'NOT_READY_NOT_CONT_CYCLE_MODE': cls.__constants['NOT_READY_NOT_CONT_CYCLE_MODE'],
            'NOT_READY_NOT_CONT_CYCLE_MODE_STR': cls.__constants['NOT_READY_NOT_CONT_CYCLE_MODE_STR'],
            'NOT_READY_MAJOR_ALARM': cls.__constants['NOT_READY_MAJOR_ALARM'],
            'NOT_READY_MAJOR_ALARM_STR': cls.__constants['NOT_READY_MAJOR_ALARM_STR'],
            'NOT_READY_ECO_MODE': cls.__constants['NOT_READY_ECO_MODE'],
            'NOT_READY_ECO_MODE_STR': cls.__constants['NOT_READY_ECO_MODE_STR'],
            'NOT_READY_SERVO_ON_TIMEOUT': cls.__constants['NOT_READY_SERVO_ON_TIMEOUT'],
            'NOT_READY_SERVO_ON_TIMEOUT_STR': cls.__constants['NOT_READY_SERVO_ON_TIMEOUT_STR'],
        }

    @property
    def READY(self):
        """Message constant 'READY'."""
        return Metaclass_MotionReadyEnum.__constants['READY']

    @property
    def READY_STR(self):
        """Message constant 'READY_STR'."""
        return Metaclass_MotionReadyEnum.__constants['READY_STR']

    @property
    def NOT_READY_UNSPECIFIED(self):
        """Message constant 'NOT_READY_UNSPECIFIED'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_UNSPECIFIED']

    @property
    def NOT_READY_UNSPECIFIED_STR(self):
        """Message constant 'NOT_READY_UNSPECIFIED_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_UNSPECIFIED_STR']

    @property
    def NOT_READY_ALARM(self):
        """Message constant 'NOT_READY_ALARM'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ALARM']

    @property
    def NOT_READY_ALARM_STR(self):
        """Message constant 'NOT_READY_ALARM_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ALARM_STR']

    @property
    def NOT_READY_ERROR(self):
        """Message constant 'NOT_READY_ERROR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ERROR']

    @property
    def NOT_READY_ERROR_STR(self):
        """Message constant 'NOT_READY_ERROR_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ERROR_STR']

    @property
    def NOT_READY_ESTOP(self):
        """Message constant 'NOT_READY_ESTOP'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ESTOP']

    @property
    def NOT_READY_ESTOP_STR(self):
        """Message constant 'NOT_READY_ESTOP_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ESTOP_STR']

    @property
    def NOT_READY_NOT_PLAY(self):
        """Message constant 'NOT_READY_NOT_PLAY'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_PLAY']

    @property
    def NOT_READY_NOT_PLAY_STR(self):
        """Message constant 'NOT_READY_NOT_PLAY_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_PLAY_STR']

    @property
    def NOT_READY_NOT_REMOTE(self):
        """Message constant 'NOT_READY_NOT_REMOTE'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_REMOTE']

    @property
    def NOT_READY_NOT_REMOTE_STR(self):
        """Message constant 'NOT_READY_NOT_REMOTE_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_REMOTE_STR']

    @property
    def NOT_READY_SERVO_OFF(self):
        """Message constant 'NOT_READY_SERVO_OFF'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_SERVO_OFF']

    @property
    def NOT_READY_SERVO_OFF_STR(self):
        """Message constant 'NOT_READY_SERVO_OFF_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_SERVO_OFF_STR']

    @property
    def NOT_READY_HOLD(self):
        """Message constant 'NOT_READY_HOLD'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_HOLD']

    @property
    def NOT_READY_HOLD_STR(self):
        """Message constant 'NOT_READY_HOLD_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_HOLD_STR']

    @property
    def NOT_READY_JOB_NOT_STARTED(self):
        """Message constant 'NOT_READY_JOB_NOT_STARTED'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_JOB_NOT_STARTED']

    @property
    def NOT_READY_JOB_NOT_STARTED_STR(self):
        """Message constant 'NOT_READY_JOB_NOT_STARTED_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_JOB_NOT_STARTED_STR']

    @property
    def NOT_READY_NOT_ON_WAIT_CMD(self):
        """Message constant 'NOT_READY_NOT_ON_WAIT_CMD'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_ON_WAIT_CMD']

    @property
    def NOT_READY_NOT_ON_WAIT_CMD_STR(self):
        """Message constant 'NOT_READY_NOT_ON_WAIT_CMD_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_ON_WAIT_CMD_STR']

    @property
    def NOT_READY_PFL_ACTIVE(self):
        """Message constant 'NOT_READY_PFL_ACTIVE'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_PFL_ACTIVE']

    @property
    def NOT_READY_PFL_ACTIVE_STR(self):
        """Message constant 'NOT_READY_PFL_ACTIVE_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_PFL_ACTIVE_STR']

    @property
    def NOT_READY_INC_MOVE_ERROR(self):
        """Message constant 'NOT_READY_INC_MOVE_ERROR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_INC_MOVE_ERROR']

    @property
    def NOT_READY_INC_MOVE_ERROR_STR(self):
        """Message constant 'NOT_READY_INC_MOVE_ERROR_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_INC_MOVE_ERROR_STR']

    @property
    def NOT_READY_OTHER_PROGRAM_RUNNING(self):
        """Message constant 'NOT_READY_OTHER_PROGRAM_RUNNING'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_OTHER_PROGRAM_RUNNING']

    @property
    def NOT_READY_OTHER_PROGRAM_RUNNING_STR(self):
        """Message constant 'NOT_READY_OTHER_PROGRAM_RUNNING_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_OTHER_PROGRAM_RUNNING_STR']

    @property
    def NOT_READY_OTHER_TRAJ_MODE_ACTIVE(self):
        """Message constant 'NOT_READY_OTHER_TRAJ_MODE_ACTIVE'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_OTHER_TRAJ_MODE_ACTIVE']

    @property
    def NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR(self):
        """Message constant 'NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR']

    @property
    def NOT_READY_NOT_CONT_CYCLE_MODE(self):
        """Message constant 'NOT_READY_NOT_CONT_CYCLE_MODE'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_CONT_CYCLE_MODE']

    @property
    def NOT_READY_NOT_CONT_CYCLE_MODE_STR(self):
        """Message constant 'NOT_READY_NOT_CONT_CYCLE_MODE_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_NOT_CONT_CYCLE_MODE_STR']

    @property
    def NOT_READY_MAJOR_ALARM(self):
        """Message constant 'NOT_READY_MAJOR_ALARM'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_MAJOR_ALARM']

    @property
    def NOT_READY_MAJOR_ALARM_STR(self):
        """Message constant 'NOT_READY_MAJOR_ALARM_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_MAJOR_ALARM_STR']

    @property
    def NOT_READY_ECO_MODE(self):
        """Message constant 'NOT_READY_ECO_MODE'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ECO_MODE']

    @property
    def NOT_READY_ECO_MODE_STR(self):
        """Message constant 'NOT_READY_ECO_MODE_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_ECO_MODE_STR']

    @property
    def NOT_READY_SERVO_ON_TIMEOUT(self):
        """Message constant 'NOT_READY_SERVO_ON_TIMEOUT'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_SERVO_ON_TIMEOUT']

    @property
    def NOT_READY_SERVO_ON_TIMEOUT_STR(self):
        """Message constant 'NOT_READY_SERVO_ON_TIMEOUT_STR'."""
        return Metaclass_MotionReadyEnum.__constants['NOT_READY_SERVO_ON_TIMEOUT_STR']


class MotionReadyEnum(metaclass=Metaclass_MotionReadyEnum):
    """
    Message class 'MotionReadyEnum'.

    Constants:
      READY
      READY_STR
      NOT_READY_UNSPECIFIED
      NOT_READY_UNSPECIFIED_STR
      NOT_READY_ALARM
      NOT_READY_ALARM_STR
      NOT_READY_ERROR
      NOT_READY_ERROR_STR
      NOT_READY_ESTOP
      NOT_READY_ESTOP_STR
      NOT_READY_NOT_PLAY
      NOT_READY_NOT_PLAY_STR
      NOT_READY_NOT_REMOTE
      NOT_READY_NOT_REMOTE_STR
      NOT_READY_SERVO_OFF
      NOT_READY_SERVO_OFF_STR
      NOT_READY_HOLD
      NOT_READY_HOLD_STR
      NOT_READY_JOB_NOT_STARTED
      NOT_READY_JOB_NOT_STARTED_STR
      NOT_READY_NOT_ON_WAIT_CMD
      NOT_READY_NOT_ON_WAIT_CMD_STR
      NOT_READY_PFL_ACTIVE
      NOT_READY_PFL_ACTIVE_STR
      NOT_READY_INC_MOVE_ERROR
      NOT_READY_INC_MOVE_ERROR_STR
      NOT_READY_OTHER_PROGRAM_RUNNING
      NOT_READY_OTHER_PROGRAM_RUNNING_STR
      NOT_READY_OTHER_TRAJ_MODE_ACTIVE
      NOT_READY_OTHER_TRAJ_MODE_ACTIVE_STR
      NOT_READY_NOT_CONT_CYCLE_MODE
      NOT_READY_NOT_CONT_CYCLE_MODE_STR
      NOT_READY_MAJOR_ALARM
      NOT_READY_MAJOR_ALARM_STR
      NOT_READY_ECO_MODE
      NOT_READY_ECO_MODE_STR
      NOT_READY_SERVO_ON_TIMEOUT
      NOT_READY_SERVO_ON_TIMEOUT_STR
    """

    __slots__ = [
        '_value',
    ]

    _fields_and_field_types = {
        'value': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
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
            assert value >= 0 and value < 65536, \
                "The 'value' field must be an unsigned integer in [0, 65535]"
        self._value = value
