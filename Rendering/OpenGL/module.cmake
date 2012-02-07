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
  DEFAULT ON)
