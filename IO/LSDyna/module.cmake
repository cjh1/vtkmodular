vtk_module(vtkIOLSDyna
  DEPENDS
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkIOXML
  COMPILE_DEPENDS
    vtkCommonCore
  TEST_DEPENDS
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
