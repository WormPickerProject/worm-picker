# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_motoros2_client_interface_dependencies_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED motoros2_client_interface_dependencies_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(motoros2_client_interface_dependencies_FOUND FALSE)
  elseif(NOT motoros2_client_interface_dependencies_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(motoros2_client_interface_dependencies_FOUND FALSE)
  endif()
  return()
endif()
set(_motoros2_client_interface_dependencies_CONFIG_INCLUDED TRUE)

# output package information
if(NOT motoros2_client_interface_dependencies_FIND_QUIETLY)
  message(STATUS "Found motoros2_client_interface_dependencies: 0.1.0 (${motoros2_client_interface_dependencies_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'motoros2_client_interface_dependencies' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${motoros2_client_interface_dependencies_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(motoros2_client_interface_dependencies_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${motoros2_client_interface_dependencies_DIR}/${_extra}")
endforeach()
