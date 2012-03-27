vtk_module(vtkFiltersSources
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkCommonTransforms
    vtkCommonMath
    vtkCommonComputationalGeometry
    vtkFiltersCore
    vtkFiltersGeneral
  TEST_DEPENDS
    vtkIOXML
  DEFAULT ON)
