vtk_module(vtkFiltersExtraction
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonMisc
    vtkCommonTransforms
    vtkCommonMath
    vtkFiltersCore
    vtkFiltersGeneral
  TEST_DEPENDS
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
