vtk_module(vtkInfovisCore
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkFiltersCore
    vtkFiltersExtraction
  TEST_DEPENDS
    vtkInfovisLayout
    vtkRenderingCore
    vtkTestingRendering
    vtkIOInfovis
  DEFAULT ON)
