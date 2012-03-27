vtk_module(vtkRenderingOpenGL
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonMath
    vtkCommonTransforms
    vtkCommonSystem
    vtkFiltersCore
    vtkRenderingCore
    vtkIOXML
    vtkIOImage # For vtkImageExport
    vtkImagingCore # For vtkSampleFunction
  COMPILE_DEPENDS
    vtkParseOGLExt
    vtkUtilitiesEncodeString
  TEST_DEPENDS
    vtkRenderingText
    vtkInteractionStyle
    vtkTestingRendering
    vtkIOExport
    vtkRenderingLOD
  DEFAULT ON)
