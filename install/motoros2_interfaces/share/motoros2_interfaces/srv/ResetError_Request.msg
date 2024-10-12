# SPDX-FileCopyrightText: 2022-2023, Yaskawa America, Inc.
# SPDX-FileCopyrightText: 2022-2023, Delft University of Technology
#
# SPDX-License-Identifier: Apache-2.0

# Attempts to reset active alarms and errors on the robot. This also clears any
# active errors internal to MotoROS2.
#
# This service will fail if the active alarm number is less than 8000. These
# alarms cannot be reset remotely and usually indicate a hardware or setting fault.

