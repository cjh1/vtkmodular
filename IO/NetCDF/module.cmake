vtk_module(vtkIONetCDF
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkIOCore
    vtksys
  COMPILE_DEPENDS
    vtknetcdf
  TEST_DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkRenderingCore
    vtkTestingRendering
  DEFAULT ON)
