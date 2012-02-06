
SET(Kit_SRCS
  vtkConvertSelectionDomain.cxx
  vtkDataRepresentation.cxx
  vtkEmptyRepresentation.cxx
  vtkRenderViewBase.cxx
  vtkView.cxx
  vtkViewUpdater.cxx
  vtkRenderView.cxx
  )

vtk_add_library(vtkViewsCore ${Kit_SRCS})
