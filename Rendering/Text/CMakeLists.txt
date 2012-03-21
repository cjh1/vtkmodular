set(Kit_SRCS
  vtkScaledTextActor.cxx
  vtkTextActor3D.cxx
  vtkTextActor.cxx
  vtkTextMapper.cxx
  vtkTextProperty.cxx
  vtkVectorText.cxx
  vtkFreeTypeStringToImage.cxx
  vtkFreeTypeUtilities.cxx
  vtkFreeTypeTools.cxx
  vtkStringToImage.cxx
  )

set_source_files_properties(
  vtkFreeTypeTools
  vtkFreeTypeUtilities
  WRAP_EXCLUDE
  )

set_source_files_properties(
  vtkStringToImage.cxx
  ABSTRACT
  )

vtk_module_library(vtkRenderingText ${Kit_SRCS})
