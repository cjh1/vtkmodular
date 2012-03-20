if(VTK_WRAP_JAVA)
  set(VTK_WRAP_JAVA3_INIT_DIR "${VTK_SOURCE_DIR}/Wrapping")
  find_package(Java)
  find_package(JNI)
  include(vtkWrapJava)
  
  IF(JAVA_AWT_LIBRARY)
  FOREACH(__java_library ${JAVA_AWT_LIBRARY})
    GET_FILENAME_COMPONENT(JAVA_LIB_DIR ${__java_library} PATH)
    IF(EXISTS ${JAVA_LIB_DIR}/xawt)
      LINK_DIRECTORIES(${JAVA_LIB_DIR}/xawt)
    ENDIF(EXISTS ${JAVA_LIB_DIR}/xawt)
    IF(EXISTS ${JAVA_LIB_DIR}/client)
      LINK_DIRECTORIES(${JAVA_LIB_DIR}/client)
    ENDIF(EXISTS ${JAVA_LIB_DIR}/client)
    IF(EXISTS ${JAVA_LIB_DIR}/server)
      LINK_DIRECTORIES(${JAVA_LIB_DIR}/server)
    ENDIF(EXISTS ${JAVA_LIB_DIR}/server)
  ENDFOREACH(__java_library)
  ENDIF(JAVA_AWT_LIBRARY)
  
  include_directories(
    ${JAVA_INCLUDE_PATH})
endif()

function(vtk_add_java_wrapping module_name)
  message("vtk_add_java_wrapping: ${module_name}")
  
  get_target_property(module_srcs ${module_name} SOURCES)
  string(REGEX REPLACE "^vtk" "" wrap_name "${module_name}")

  vtk_wrap_java3(vtk${wrap_name}Java ModuleJava_SRCS "${module_srcs};${Kit_JAVA_EXTRA_WRAP_SRCS}")
  
  add_library(vtk${wrap_name}Java SHARED ${ModuleJava_SRCS} ${Kit_JAVA_EXTRA_SRCS})
  # Force JavaClasses to build in the right order by adding a depenency.
  add_dependencies(vtk${wrap_name}JavaJavaClasses vtk${wrap_name}Java)
#  SET(KIT_LIBRARY_TARGETS ${KIT_LIBRARY_TARGETS} vtk${wrap_name}Java)
  target_link_libraries(vtk${wrap_name}Java ${module_name} vtkWrappingJavaCore)
# What this install stuff ...  
#  IF(NOT VTK_INSTALL_NO_LIBRARIES)
#    INSTALL(TARGETS vtk${wrap_name}Java
#      EXPORT ${VTK_INSTALL_EXPORT_NAME}
#      RUNTIME DESTINATION ${VTK_INSTALL_BIN_DIR_CM24} COMPONENT RuntimeLibraries
#      LIBRARY DESTINATION ${VTK_INSTALL_LIB_DIR_CM24} COMPONENT RuntimeLibraries
#      ARCHIVE DESTINATION ${VTK_INSTALL_LIB_DIR_CM24} COMPONENT Development)
#  ENDIF(NOT VTK_INSTALL_NO_LIBRARIES)
  add_dependencies(vtk${wrap_name}Java vtk${wrap_name})
#  IF(KIT_JAVA_DEPS)
#    ADD_DEPENDENCIES(vtk${wrap_name}Java ${KIT_JAVA_DEPS})
#  ENDIF(KIT_JAVA_DEPS)
endfunction()
