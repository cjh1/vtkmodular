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
  DEFAULT ON)
