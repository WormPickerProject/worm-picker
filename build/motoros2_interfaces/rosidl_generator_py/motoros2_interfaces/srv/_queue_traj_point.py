# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:srv/QueueTrajPoint.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_QueueTrajPoint_Request(type):
    """Metaclass of message 'QueueTrajPoint_Request'."""

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
                'motoros2_interfaces.srv.QueueTrajPoint_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__queue_traj_point__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__queue_traj_point__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__queue_traj_point__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__queue_traj_point__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__queue_traj_point__request

            from trajectory_msgs.msg import JointTrajectoryPoint
            if JointTrajectoryPoint.__class__._TYPE_SUPPORT is None:
                JointTrajectoryPoint.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class QueueTrajPoint_Request(metaclass=Metaclass_QueueTrajPoint_Request):
    """Message class 'QueueTrajPoint_Request'."""

    __slots__ = [
        '_joint_names',
        '_point',
    ]

    _fields_and_field_types = {
        'joint_names': 'sequence<string>',
        'point': 'trajectory_msgs/JointTrajectoryPoint',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['trajectory_msgs', 'msg'], 'JointTrajectoryPoint'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.joint_names = kwargs.get('joint_names', [])
        from trajectory_msgs.msg import JointTrajectoryPoint
        self.point = kwargs.get('point', JointTrajectoryPoint())

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
        if self.joint_names != other.joint_names:
            return False
        if self.point != other.point:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def joint_names(self):
        """Message field 'joint_names'."""
        return self._joint_names

    @joint_names.setter
    def joint_names(self, value):
        if __debug__:
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
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'joint_names' field must be a set or sequence and each value of type 'str'"
        self._joint_names = value

    @builtins.property
    def point(self):
        """Message field 'point'."""
        return self._point

    @point.setter
    def point(self, value):
        if __debug__:
            from trajectory_msgs.msg import JointTrajectoryPoint
            assert \
                isinstance(value, JointTrajectoryPoint), \
                "The 'point' field must be a sub message of type 'JointTrajectoryPoint'"
        self._point = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_QueueTrajPoint_Response(type):
    """Metaclass of message 'QueueTrajPoint_Response'."""

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
                'motoros2_interfaces.srv.QueueTrajPoint_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__queue_traj_point__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__queue_traj_point__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__queue_traj_point__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__queue_traj_point__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__queue_traj_point__response

            from motoros2_interfaces.msg import QueueResultEnum
            if QueueResultEnum.__class__._TYPE_SUPPORT is None:
                QueueResultEnum.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class QueueTrajPoint_Response(metaclass=Metaclass_QueueTrajPoint_Response):
    """Message class 'QueueTrajPoint_Response'."""

    __slots__ = [
        '_result_code',
        '_message',
    ]

    _fields_and_field_types = {
        'result_code': 'motoros2_interfaces/QueueResultEnum',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['motoros2_interfaces', 'msg'], 'QueueResultEnum'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from motoros2_interfaces.msg import QueueResultEnum
        self.result_code = kwargs.get('result_code', QueueResultEnum())
        self.message = kwargs.get('message', str())

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
        if self.message != other.message:
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
            from motoros2_interfaces.msg import QueueResultEnum
            assert \
                isinstance(value, QueueResultEnum), \
                "The 'result_code' field must be a sub message of type 'QueueResultEnum'"
        self._result_code = value

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


class Metaclass_QueueTrajPoint(type):
    """Metaclass of service 'QueueTrajPoint'."""

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
                'motoros2_interfaces.srv.QueueTrajPoint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__queue_traj_point

            from motoros2_interfaces.srv import _queue_traj_point
            if _queue_traj_point.Metaclass_QueueTrajPoint_Request._TYPE_SUPPORT is None:
                _queue_traj_point.Metaclass_QueueTrajPoint_Request.__import_type_support__()
            if _queue_traj_point.Metaclass_QueueTrajPoint_Response._TYPE_SUPPORT is None:
                _queue_traj_point.Metaclass_QueueTrajPoint_Response.__import_type_support__()


class QueueTrajPoint(metaclass=Metaclass_QueueTrajPoint):
    from motoros2_interfaces.srv._queue_traj_point import QueueTrajPoint_Request as Request
    from motoros2_interfaces.srv._queue_traj_point import QueueTrajPoint_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
