set(Kit_SRCS
  vtkPLSDynaReader.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${vtkIOLSDyna_SOURCE_DIR}/private
  ${vtkIOLSDyna_BINARY_DIR}/private
  )

vtk_add_library(vtkIOParallelLSDyna ${Kit_SRCS})
