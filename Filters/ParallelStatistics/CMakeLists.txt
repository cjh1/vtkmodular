
SET(Kit_SRCS
  vtkPContingencyStatistics.h
  vtkPContingencyStatistics.cxx
  vtkPCorrelativeStatistics.h
  vtkPCorrelativeStatistics.cxx
  vtkPDescriptiveStatistics.h
  vtkPDescriptiveStatistics.cxx
  vtkPKMeansStatistics.h
  vtkPKMeansStatistics.cxx
  vtkPMultiCorrelativeStatistics.h
  vtkPMultiCorrelativeStatistics.cxx
  vtkPOrderStatistics.h
  vtkPOrderStatistics.cxx
  vtkPPCAStatistics.h
  vtkPPCAStatistics.cxx
  )

vtk_add_library(vtkFiltersParallelStatistics ${Kit_SRCS})
