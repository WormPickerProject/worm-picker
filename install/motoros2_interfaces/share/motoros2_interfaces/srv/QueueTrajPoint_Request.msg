# SPDX-FileCopyrightText: 2022-2023, Yaskawa America, Inc.
# SPDX-FileCopyrightText: 2022-2023, Delft University of Technology
#
# SPDX-License-Identifier: Apache-2.0

# Submit a trajectory point to the continuous motion queue.
#
# The start_point_queue_mode service must have been invoked first

string[] joint_names
trajectory_msgs/JointTrajectoryPoint point

