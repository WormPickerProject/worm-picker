# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motoros2_interfaces:msg/InformJobCrudResultCodes.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_InformJobCrudResultCodes(type):
    """Metaclass of message 'InformJobCrudResultCodes'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'RC_OK': 1,
        'STR_OK': 'Success',
        'RC_ERR_REFRESHING_JOB_LIST': 10,
        'STR_ERR_REFRESHING_JOB_LIST': 'Error refreshing job list',
        'RC_ERR_RETRIEVING_FILE_COUNT': 11,
        'STR_ERR_RETRIEVING_FILE_COUNT': 'Error retrieving file count',
        'RC_ERR_TOO_MANY_JOBS': 12,
        'STR_ERR_TOO_MANY_JOBS': 'Too many jobs',
        'RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST': 13,
        'STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST': 'Failed retrieving job name from list',
        'RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE': 14,
        'STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE': 'Error adding job name to service response',
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
                'motoros2_interfaces.msg.InformJobCrudResultCodes')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__inform_job_crud_result_codes
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__inform_job_crud_result_codes
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__inform_job_crud_result_codes
            cls._TYPE_SUPPORT = module.type_support_msg__msg__inform_job_crud_result_codes
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__inform_job_crud_result_codes

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'RC_OK': cls.__constants['RC_OK'],
            'STR_OK': cls.__constants['STR_OK'],
            'RC_ERR_REFRESHING_JOB_LIST': cls.__constants['RC_ERR_REFRESHING_JOB_LIST'],
            'STR_ERR_REFRESHING_JOB_LIST': cls.__constants['STR_ERR_REFRESHING_JOB_LIST'],
            'RC_ERR_RETRIEVING_FILE_COUNT': cls.__constants['RC_ERR_RETRIEVING_FILE_COUNT'],
            'STR_ERR_RETRIEVING_FILE_COUNT': cls.__constants['STR_ERR_RETRIEVING_FILE_COUNT'],
            'RC_ERR_TOO_MANY_JOBS': cls.__constants['RC_ERR_TOO_MANY_JOBS'],
            'STR_ERR_TOO_MANY_JOBS': cls.__constants['STR_ERR_TOO_MANY_JOBS'],
            'RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST': cls.__constants['RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST'],
            'STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST': cls.__constants['STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST'],
            'RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE': cls.__constants['RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'],
            'STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE': cls.__constants['STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'],
        }

    @property
    def RC_OK(self):
        """Message constant 'RC_OK'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_OK']

    @property
    def STR_OK(self):
        """Message constant 'STR_OK'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_OK']

    @property
    def RC_ERR_REFRESHING_JOB_LIST(self):
        """Message constant 'RC_ERR_REFRESHING_JOB_LIST'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_ERR_REFRESHING_JOB_LIST']

    @property
    def STR_ERR_REFRESHING_JOB_LIST(self):
        """Message constant 'STR_ERR_REFRESHING_JOB_LIST'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_ERR_REFRESHING_JOB_LIST']

    @property
    def RC_ERR_RETRIEVING_FILE_COUNT(self):
        """Message constant 'RC_ERR_RETRIEVING_FILE_COUNT'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_ERR_RETRIEVING_FILE_COUNT']

    @property
    def STR_ERR_RETRIEVING_FILE_COUNT(self):
        """Message constant 'STR_ERR_RETRIEVING_FILE_COUNT'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_ERR_RETRIEVING_FILE_COUNT']

    @property
    def RC_ERR_TOO_MANY_JOBS(self):
        """Message constant 'RC_ERR_TOO_MANY_JOBS'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_ERR_TOO_MANY_JOBS']

    @property
    def STR_ERR_TOO_MANY_JOBS(self):
        """Message constant 'STR_ERR_TOO_MANY_JOBS'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_ERR_TOO_MANY_JOBS']

    @property
    def RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST(self):
        """Message constant 'RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST']

    @property
    def STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST(self):
        """Message constant 'STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST']

    @property
    def RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE(self):
        """Message constant 'RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'."""
        return Metaclass_InformJobCrudResultCodes.__constants['RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE']

    @property
    def STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE(self):
        """Message constant 'STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE'."""
        return Metaclass_InformJobCrudResultCodes.__constants['STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE']


class InformJobCrudResultCodes(metaclass=Metaclass_InformJobCrudResultCodes):
    """
    Message class 'InformJobCrudResultCodes'.

    Constants:
      RC_OK
      STR_OK
      RC_ERR_REFRESHING_JOB_LIST
      STR_ERR_REFRESHING_JOB_LIST
      RC_ERR_RETRIEVING_FILE_COUNT
      STR_ERR_RETRIEVING_FILE_COUNT
      RC_ERR_TOO_MANY_JOBS
      STR_ERR_TOO_MANY_JOBS
      RC_ERR_RETRIEVING_JOB_NAME_FROM_LIST
      STR_ERR_RETRIEVING_JOB_NAME_FROM_LIST
      RC_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE
      STR_ERR_APPENDING_JOB_NAME_TO_SVC_RESPONSE
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
