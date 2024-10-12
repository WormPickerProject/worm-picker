

# Result of the service invocation. Values other than zero (0) signal failure.
#
# Refer to SelectionResultCodes.msg for defined values
SelectionResultCodes result_code

# A human-readable error message, or an empty string if there was no error.
string message

# true IFF invocation of the MotoROS service was successful.
#
# NOTE: this is independent of whether the ROS service invocation was
#       successful. In absence of any ROS middleware failures, a failed MotoROS
#       service invocation will result in 'success' here being set to 'false',
#       but a successful ROS service invocation.
bool success
