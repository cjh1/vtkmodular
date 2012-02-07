vtk_module(vtkFiltersHybrid
  DEPENDS
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkImagingCore
    vtkRenderingOpenGL
    vtkFiltersGeneral
  COMPILE_DEPENDS
    vtkUtilitiesEncodeString
  DEFAULT ON)
