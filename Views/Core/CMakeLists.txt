
SET(Kit_SRCS
  vtkConvertSelectionDomain.cxx
  vtkDataRepresentation.cxx
  vtkEmptyRepresentation.cxx
  vtkRenderViewBase.cxx
  vtkView.cxx
#  vtkViewUpdater.cxx
  vtkViewTheme.cxx
#  vtkRenderView.cxx
  )

vtk_module_library(vtkViewsCore ${Kit_SRCS})
