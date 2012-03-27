vtk_module(vtkImagingCore
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonTransforms
    vtkCommonMath
    vtkCommonComputationalGeometry
    vtkCommonExecutionModel
  TEST_DEPENDS
    vtkFiltersCore
    vtkFiltersModeling
    vtkFiltersGeneral
    vtkFiltersHybrid
    vtkRenderingCore
    vtkTestingRendering
    vtkInteractionStyle
  DEFAULT ON)
