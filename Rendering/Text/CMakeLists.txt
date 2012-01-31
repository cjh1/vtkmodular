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
  )

vtk_add_library(vtkRenderingText ${Kit_SRCS})

