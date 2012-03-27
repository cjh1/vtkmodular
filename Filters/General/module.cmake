vtk_module(vtkFiltersGeneral
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkCommonSystem
    vtkCommonMisc
    vtkCommonTransforms
    vtkCommonMath
    vtkCommonComputationalGeometry
    vtkFiltersCore
  TEST_DEPENDS
    vtkRenderingCore
    vtkRenderingAnnotation
    vtkTestingRendering
  DEFAULT ON)
