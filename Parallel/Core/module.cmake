vtk_module(vtkParallelCore
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkIOCore
    vtkIOGeometry
  COMPILE_DEPENDS
    vtkUtilitiesHashSource
  DEFAULT ON)
