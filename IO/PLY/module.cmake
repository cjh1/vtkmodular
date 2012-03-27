vtk_module(vtkIOPLY
  DEPENDS
    vtkCommonCore
    vtkCommonMisc
    vtkCommonExecutionModel
    vtkIOGeometry
  TEST_DEPENDS
    vtkRenderingCore
    vtkIOImage
    vtkTestingRendering
  DEFAULT ON)
