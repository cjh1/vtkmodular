vtk_module(vtkFiltersGeometry
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkFiltersCore
  TEST_DEPENDS
    vtkIOXML
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
