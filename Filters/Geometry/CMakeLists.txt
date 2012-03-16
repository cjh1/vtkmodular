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

  vtkAbstractGridConnectivity.cxx
  vtkDataSetGhostGenerator.cxx
  vtkRectilinearGridPartitioner.cxx
  vtkStructuredGridConnectivity.cxx
  vtkStructuredGridGhostDataGenerator.cxx
  vtkStructuredGridPartitioner.cxx
  vtkStructuredNeighbor.cxx
  vtkUniformGridGhostDataGenerator.cxx
  )

vtk_module_library(vtkFiltersGeometry ${Kit_SRCS})
