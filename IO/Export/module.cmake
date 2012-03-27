vtk_module(vtkIOExport
  DEPENDS
    vtkCommonCore
    vtkRenderingCore
    vtkRenderingText
    vtkImagingCore
    vtkIOCore
    vtkgl2ps
  TEST_DEPENDS
    vtkTestingRendering
  DEFAULT ON)
