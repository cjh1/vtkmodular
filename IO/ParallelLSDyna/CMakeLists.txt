set(Kit_SRCS
  vtkPLSDynaReader.cxx
  )

include_directories(
  ${vtkIOLSDyn_SOURCE_DIR}/private
  ${vtkIOLSDyn_BINARY_DIR}/private
  )

vtk_add_library(vtkIOParallelLSDyn ${Kit_SRCS})
