vtk_module(vtkCommonDataModel
  DEPENDS
    vtkCommonCore
    vtkCommonSystem
    vtkCommonMath
    vtkCommonMisc
    vtkCommonTransforms
    vtksys
  TEST_DEPENDS
    vtkTestingCore
    vtkCommonExecutionModel
    vtkIOGeometry
    vtkRenderingCore
  DEFAULT ON)
