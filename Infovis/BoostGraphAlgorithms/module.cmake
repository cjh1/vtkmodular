vtk_module(vtkInfovisBoostGraphAlgorithms
  DEPENDS
    vtkInfovisCore
    vtkCommonExecutionModel
  TEST_DEPENDS
    # vtkViewsInfovis
    vtkRenderingCore
    vtkTestingRendering
    vtkIOInfovis
  DEFAULT OFF)
