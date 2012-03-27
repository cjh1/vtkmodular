vtk_module(vtkIOMySQL
  DEPENDS
    vtkCommonDataModel
    vtkIOSQL
  TEST_DEPENDS
    vtkTestingIOSQL
    vtkIOMySQL
  DEFAULT OFF)
