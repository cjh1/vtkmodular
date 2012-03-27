vtk_module(vtkIOGeometry
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonMisc
    vtkIOCore
    vtkzlib
    vtksys
  COMPILE_DEPENDS
    vtkUtilitiesMaterialLibrary
  TEST_DEPENDS
    vtkFiltersGeometry
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
