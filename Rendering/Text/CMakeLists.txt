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
include_directories(
  ${VTK_SOURCE_DIR}/TPL/ftgl/src
  ${VTK_SOURCE_DIR}/TPL
  ${VTK_SOURCE_DIR}/TPL/vtkfreetype/include
  ${VTK_SOURCE_DIR}/Rendering/FreeType
  )
vtk_add_library(vtkRenderingText ${Kit_SRCS})
