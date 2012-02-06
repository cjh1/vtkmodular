set(Kit_SRCS
  vtkPLY.cxx
  vtkPLYReader.cxx
  vtkPLYWriter.cxx
)

SET_SOURCE_FILES_PROPERTIES(
  vtkPLY
  WRAP_EXCLUDE
)

vtk_add_library(vtkIOPLY ${Kit_SRCS})
