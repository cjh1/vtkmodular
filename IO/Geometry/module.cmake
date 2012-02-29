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
  DEFAULT ON)
