vtk_module(vtkIONetCDF
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkIOCore
    kwsys
  COMPILE_DEPENDS
    vtknetcdf
  DEFAULT ON)
