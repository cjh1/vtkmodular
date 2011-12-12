# The commands in this directory are intended to be executed as
# the end of the whole configuration process, as a "last step".
# This directory is typically the last add_subdirectory in the main CMakeLists.txt.
# It enable the above commands to use variables that might have been configured
# in previous add_subdirectory. This is especially important when it comes to
# the CONFIGURE_FILE command, since in IMMEDIATE mode that command will
# use the current values of CMake variables instead of waiting until the
# end of CMakeLists processing, i.e. instead of waiting until some variables
# are configured in add_subdirectory commands.

#-----------------------------------------------------------------------------
get_property(VTK_TARGETS GLOBAL PROPERTY VTK_TARGETS)
get_property(VTK_TPL_TARGETS GLOBAL PROPERTY VTK_TPL_TARGETS)
export(TARGETS ${VTK_TARGETS} ${VTK_TPL_TARGETS} FILE ${VTK_BINARY_DIR}/VTKTargets.cmake)
#install(EXPORT ${VTK_INSTALL_EXPORT_NAME} DESTINATION ${VTK_INSTALL_LIB_DIR_CM24})
get_property(VTK_LIBRARIES GLOBAL PROPERTY VTK_LIBRARIES)
#-----------------------------------------------------------------------------
# Create the VTKConfig.cmake file containing the VTK configuration.
# Since it might generate configuration file depending
include(${VTK_SOURCE_DIR}/vtkGenerateVTKConfig.cmake)
