vtk_module(vtkIOGeometry
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonMisc
    vtkIOCore
    vtkzlib
    kwsys
  COMPILE_DEPENDS
    MaterialLibrary
  DEFAULT ON)
