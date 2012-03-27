vtk_module(vtkChartsCore
  DEPENDS
    vtkRenderingContext2D
    vtkInfovisCore # Needed for plot parallel coordinates vtkStringToCategory
  TEST_DEPENDS
    vtkTestingCore
    vtkTestingRendering
    vtkViewsContext2D
    vtkIOInfovis
  DEFAULT ON)
