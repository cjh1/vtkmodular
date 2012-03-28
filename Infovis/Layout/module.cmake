vtk_module(vtkInfovisLayout
  DEPENDS
    vtkCommonCore
    vtkCommonExecutionModel
    vtkImagingCore
    vtkFiltersModeling
    vtkInfovisCore
  TEST_DEPENDS
    vtkRenderingLabel
    vtkRenderingCore
    vtkTestingRendering
    vtkIOInfovis
  DEFAULT ON)
