
set(VTK_WRAP_PYTHON_FIND_LIBS ON)
include(vtkWrapPython)

set(PythonCore_SRCS
  vtkPythonArgs.cxx
  vtkPythonOverload.cxx
  vtkPythonUtil.cxx
  PyVTKClass.cxx
  PyVTKMutableObject.cxx
  PyVTKObject.cxx
  PyVTKSpecialObject.cxx
  PyVTKTemplate.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_BINARY_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/Utilities
  ${VTK_BINARY_DIR}/Wrapping
  )

# SIP directory will be searched before other python dirs
if(VTK_WRAP_PYTHON_SIP)
  include_directories("${SIP_INCLUDE_DIR}")
endif()
include_directories("${PYTHON_INCLUDE_PATH}")

add_library(vtkWrappingPythonCore ${PythonCore_SRCS})

target_link_libraries(vtkWrappingPythonCore
  vtkCommonCore
  ${VTK_PYTHON_LIBRARIES})
target_link_libraries(vtkWrappingPythonCore
  LINK_INTERFACE_LIBRARIES ${VTK_PYTHON_LIBRARIES})
