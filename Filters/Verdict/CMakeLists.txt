set(Kit_SRCS
  vtkCellQuality.cxx
  vtkMatrixMathFilter.cxx
  vtkMeshQuality.cxx
)

vtk_module_library(vtkFiltersVerdict ${Kit_SRCS})
