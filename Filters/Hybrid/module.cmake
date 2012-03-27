vtk_module(vtkFiltersHybrid
  DEPENDS
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkImagingCore
    vtkRenderingOpenGL
    vtkFiltersGeneral
  COMPILE_DEPENDS
    vtkUtilitiesEncodeString
  TEST_DEPENDS
    vtkImagingCore
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
