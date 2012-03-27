vtk_module(vtkInteractionWidgets
  DEPENDS
   vtkRenderingAnnotation
   vtkRenderingText
   vtkRenderingVolume
   vtkFiltersModeling
   vtkFiltersHybrid
  TEST_DEPENDS
    vtkRenderingCore
    vtkTestingRendering
    vtkInteractionStyle
    vtkFiltersModeling
    vtkRenderingLOD
  DEFAULT OFF)
