# SPDX-FileCopyrightText: 2022-2023, Yaskawa America, Inc.
# SPDX-FileCopyrightText: 2022-2023, Delft University of Technology
#
# SPDX-License-Identifier: Apache-2.0

# Enable the robot and activate the point-queing motion mode. This service must
# be invoked prior to using the 'queue_traj_point' service.
#
# It is recommended to monitor the 'robot_status' topic prior to invoking this
# service. This service can only succeed if 'mode' == AUTO, 'e_stopped' == FALSE,
# and 'in_error' == FALSE. If there is an active error, it should be cleared with
# the 'reset_error' service.
#
# If this service is successful, the returned 'result_code' will indicate 'READY'.

