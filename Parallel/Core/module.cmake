vtk_module(vtkParallelCore
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkIOCore
    vtkIOGeometry
  COMPILE_DEPENDS
    HashSource
  DEFAULT ON)
