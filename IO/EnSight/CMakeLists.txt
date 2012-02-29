set(Kit_SRCS
  vtkEnSight6BinaryReader.cxx
  vtkEnSight6Reader.cxx
  vtkEnSightGoldBinaryReader.cxx
  vtkEnSightGoldReader.cxx
  vtkEnSightMasterServerReader.cxx
  vtkEnSightReader.cxx
  vtkGenericEnSightReader.cxx
)

SET_SOURCE_FILES_PROPERTIES(
  vtkEnSightReader
  ABSTRACT
)


vtk_module_library(vtkIOEnSight ${Kit_SRCS})
