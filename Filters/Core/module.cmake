vtk_module(vtkFiltersCore
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkCommonSystem
    vtkCommonMisc
    vtkCommonTransforms
    vtkCommonMath
  TEST_DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkTestingRendering
    vtkIOXML
    vtkImagingCore
    vtkFiltersGeneral
    vtkRenderingCore
  DEFAULT ON)
