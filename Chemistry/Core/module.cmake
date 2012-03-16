vtk_module(vtkChemistryCore
  DEPENDS 
    vtkCommonDataModel
    vtkIOXML
    vtkRenderingCore
  TEST_DEPENDS
    vtkTestingCore
    vtkTestingRendering
    vtkInteractionStyle
    vtkRenderingOpenGL
  DEFAULT ON)
