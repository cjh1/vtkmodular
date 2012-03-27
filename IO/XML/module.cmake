vtk_module(vtkIOXML
  DEPENDS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonSystem
    vtkCommonMisc
    vtkIOCore
    vtkIOGeometry
    vtkexpat
    vtksys
  TEST_DEPENDS
    vtkImagingCore
    vtkFiltersSources
    vtkFiltersCore
  DEFAULT ON)
