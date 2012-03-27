vtk_module(vtkInfovisLayout
  DEPENDS
    vtkCommonCore
    vtkCommonExecutionModel
    vtkImagingCore
    vtkFiltersSources
    vtkInfovisCore
  TEST_DEPENDS
    vtkRenderingLabel
    vtkRenderingCore
    vtkTestingRendering
    vtkIOInfovis
  DEFAULT ON)
