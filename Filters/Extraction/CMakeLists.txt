set(Kit_SRCS
  vtkConvertSelection.cxx
  vtkExtractArraysOverTime.cxx
  vtkExtractBlock.cxx
  vtkExtractCells.cxx
  vtkExtractDataOverTime.cxx
  vtkExtractDataSets.cxx
  vtkExtractEdges.cxx
  vtkExtractGeometry.cxx
  vtkExtractGrid.cxx
  vtkExtractLevel.cxx
  vtkExtractPolyDataGeometry.cxx
  vtkExtractRectilinearGrid.cxx
  vtkExtractSelectedBlock.cxx
  vtkExtractSelectedFrustum.cxx
  vtkExtractSelectedIds.cxx
  vtkExtractSelectedLocations.cxx
  vtkExtractSelectedPolyDataIds.cxx
  vtkExtractSelectedRows.cxx
  vtkExtractSelectedThresholds.cxx
  vtkExtractSelectionBase.cxx
  vtkExtractSelection.cxx
  vtkExtractTemporalFieldData.cxx
  vtkExtractTensorComponents.cxx
  vtkExtractUnstructuredGrid.cxx
  vtkExtractVectorComponents.cxx

  vtkProbeSelectedLocations.cxx
  vtkHierarchicalDataExtractDataSets.cxx
  vtkHierarchicalDataExtractLevel.cxx
  vtkLinearExtractor.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Utilities
  )

vtk_add_library(vtkFiltersExtraction ${Kit_SRCS})
