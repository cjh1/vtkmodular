
SET(Kit_SRCS

  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/Common/Math
  )

#SET_SOURCE_FILES_PROPERTIES(
#ABSTRACT
#)

#SET_SOURCE_FILES_PROPERTIES(
#  WRAP_EXCLUDE
#)

#SET_SOURCE_FILES_PROPERTIES(
#  PROPERTIES WRAP_SPECIAL 1
#)

add_library(vtkCommonExecutionModel ${Kit_SRCS})

target_link_libraries(vtkCommonExecutionModel vtkCommonCore vtkCommonMath)
