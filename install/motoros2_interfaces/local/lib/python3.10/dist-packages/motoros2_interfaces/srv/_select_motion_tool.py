# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:srv/SelectMotionTool.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SelectMotionTool_Request(type):
    """Metaclass of message 'SelectMotionTool_Request'."""

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
                'motoros2_interfaces.srv.SelectMotionTool_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__select_motion_tool__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__select_motion_tool__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__select_motion_tool__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__select_motion_tool__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__select_motion_tool__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SelectMotionTool_Request(metaclass=Metaclass_SelectMotionTool_Request):
    """Message class 'SelectMotionTool_Request'."""

    __slots__ = [
        '_group_number',
        '_tool_number',
    ]

    _fields_and_field_types = {
        'group_number': 'uint32',
        'tool_number': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.group_number = kwargs.get('group_number', int())
        self.tool_number = kwargs.get('tool_number', int())

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
        if self.group_number != other.group_number:
            return False
        if self.tool_number != other.tool_number:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def group_number(self):
        """Message field 'group_number'."""
        return self._group_number

    @group_number.setter
    def group_number(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'group_number' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'group_number' field must be an unsigned integer in [0, 4294967295]"
        self._group_number = value

    @builtins.property
    def tool_number(self):
        """Message field 'tool_number'."""
        return self._tool_number

    @tool_number.setter
    def tool_number(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'tool_number' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'tool_number' field must be an unsigned integer in [0, 4294967295]"
        self._tool_number = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SelectMotionTool_Response(type):
    """Metaclass of message 'SelectMotionTool_Response'."""

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
                'motoros2_interfaces.srv.SelectMotionTool_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__select_motion_tool__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__select_motion_tool__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__select_motion_tool__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__select_motion_tool__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__select_motion_tool__response

            from motoros2_interfaces.msg import SelectionResultCodes
            if SelectionResultCodes.__class__._TYPE_SUPPORT is None:
                SelectionResultCodes.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SelectMotionTool_Response(metaclass=Metaclass_SelectMotionTool_Response):
    """Message class 'SelectMotionTool_Response'."""

    __slots__ = [
        '_result_code',
        '_message',
        '_success',
    ]

    _fields_and_field_types = {
        'result_code': 'motoros2_interfaces/SelectionResultCodes',
        'message': 'string',
        'success': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['motoros2_interfaces', 'msg'], 'SelectionResultCodes'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from motoros2_interfaces.msg import SelectionResultCodes
        self.result_code = kwargs.get('result_code', SelectionResultCodes())
        self.message = kwargs.get('message', str())
        self.success = kwargs.get('success', bool())

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
        if self.success != other.success:
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
            from motoros2_interfaces.msg import SelectionResultCodes
            assert \
                isinstance(value, SelectionResultCodes), \
                "The 'result_code' field must be a sub message of type 'SelectionResultCodes'"
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

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value


class Metaclass_SelectMotionTool(type):
    """Metaclass of service 'SelectMotionTool'."""

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
                'motoros2_interfaces.srv.SelectMotionTool')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__select_motion_tool

            from motoros2_interfaces.srv import _select_motion_tool
            if _select_motion_tool.Metaclass_SelectMotionTool_Request._TYPE_SUPPORT is None:
                _select_motion_tool.Metaclass_SelectMotionTool_Request.__import_type_support__()
            if _select_motion_tool.Metaclass_SelectMotionTool_Response._TYPE_SUPPORT is None:
                _select_motion_tool.Metaclass_SelectMotionTool_Response.__import_type_support__()


class SelectMotionTool(metaclass=Metaclass_SelectMotionTool):
    from motoros2_interfaces.srv._select_motion_tool import SelectMotionTool_Request as Request
    from motoros2_interfaces.srv._select_motion_tool import SelectMotionTool_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
