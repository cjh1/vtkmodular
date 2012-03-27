vtk_module(vtkIOInfovis
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonMisc
    vtkIOCore
    vtkInfovisCore
    vtklibxml2
    vtksys
  TEST_DEPENDS
    vtkInfovisLayout
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
