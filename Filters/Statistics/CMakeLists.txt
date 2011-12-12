
SET(Kit_SRCS
  vtkBivariateLinearTableThreshold.cxx
  vtkContingencyStatistics.cxx
  vtkCorrelativeStatistics.cxx
  vtkDescriptiveStatistics.cxx
  vtkKMeansDistanceFunctorCalculator.cxx
  vtkKMeansDistanceFunctor.cxx
  vtkKMeansStatistics.cxx
  vtkMultiCorrelativeStatistics.cxx
  vtkOrderStatistics.cxx
  vtkPCAStatistics.cxx
  vtkStatisticsAlgorithm.cxx
  vtkStrahlerMetric.cxx
  vtkStreamingStatistics.cxx
  )

vtk_add_library(vtkFiltersStatistics ${Kit_SRCS})
