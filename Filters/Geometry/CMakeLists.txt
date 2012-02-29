set(Kit_SRCS
  vtkCompositeDataGeometryFilter.cxx
  vtkGeometryFilter.cxx
  vtkHierarchicalDataSetGeometryFilter.cxx
  vtkImageDataGeometryFilter.cxx
  vtkRectilinearGridGeometryFilter.cxx
  vtkStructuredGridGeometryFilter.cxx
  vtkStructuredPointsGeometryFilter.cxx
  vtkUnstructuredGridGeometryFilter.cxx

  vtkDataSetSurfaceFilter.cxx
  )

vtk_module_library(vtkFiltersGeometry ${Kit_SRCS})
