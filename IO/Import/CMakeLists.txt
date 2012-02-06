set(Kit_SRCS
  vtk3DSImporter.cxx
  vtkImporter.cxx
  vtkVRMLImporter.cxx
)

vtk_add_library(vtkIOImport ${Kit_SRCS})
