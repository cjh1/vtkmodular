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

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Utilities
  )

vtk_add_library(vtkFiltersGeometry ${Kit_SRCS})
