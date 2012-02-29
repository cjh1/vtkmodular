vtk_module(vtkIONetCDF
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkIOCore
    vtksys
  COMPILE_DEPENDS
    vtknetcdf
  DEFAULT ON)
