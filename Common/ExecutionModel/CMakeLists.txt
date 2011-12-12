
SET(Kit_SRCS
  vtkAlgorithm.cxx
  vtkAlgorithmOutput.cxx
  vtkAnnotationLayersAlgorithm.cxx
  vtkArrayDataAlgorithm.cxx
  vtkCachedStreamingDemandDrivenPipeline.cxx
  vtkCastToConcrete.cxx
  vtkCompositeDataPipeline.cxx
  vtkCompositeDataSetAlgorithm.cxx
  vtkComputingResources.cxx
  vtkDataObjectAlgorithm.cxx
  vtkDataSetAlgorithm.cxx
  vtkDemandDrivenPipeline.cxx
  vtkDirectedGraphAlgorithm.cxx
  vtkExecutionScheduler.cxx
  vtkExecutionSchedulerManager.cxx
  vtkExecutiveCollection.cxx
  vtkExecutive.cxx
  vtkExtentSplitter.cxx
  vtkExtentTranslator.cxx
  vtkFilteringInformationKeyManager.cxx
  vtkGraphAlgorithm.cxx
  vtkHierarchicalBoxDataSetAlgorithm.cxx
  vtkHyperOctreeAlgorithm.cxx
  vtkImageAlgorithm.cxx
  vtkImageInPlaceFilter.cxx
  vtkImageProgressIterator.cxx
  vtkImageToStructuredGrid.cxx
  vtkImageToStructuredPoints.cxx
  vtkInformationExecutivePortKey.cxx
  vtkInformationExecutivePortVectorKey.cxx
  vtkMultiBlockDataSetAlgorithm.cxx
  vtkOnePieceExtentTranslator.cxx
  vtkPassInputTypeAlgorithm.cxx
  vtkPiecewiseFunctionAlgorithm.cxx
  vtkPiecewiseFunctionShiftScale.cxx
  vtkPointSetAlgorithm.cxx
  vtkPolyDataAlgorithm.cxx
  vtkRectilinearGridAlgorithm.cxx
  vtkScalarTree.cxx
  vtkSimpleImageToImageFilter.cxx
  vtkSimpleScalarTree.cxx
  vtkStreamingDemandDrivenPipeline.cxx
  vtkStructuredGridAlgorithm.cxx
  vtkTableAlgorithm.cxx
  vtkTableExtentTranslator.cxx
  vtkTemporalDataSetAlgorithm.cxx
  vtkThreadedImageAlgorithm.cxx
  vtkThreadedStreamingPipeline.cxx
  vtkTreeAlgorithm.cxx
  vtkTrivialProducer.cxx
  vtkUndirectedGraphAlgorithm.cxx
  vtkUnstructuredGridAlgorithm.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR} 
#  ${VTK_SOURCE_DIR}/Common/Core
#  ${VTK_SOURCE_DIR}/Common/Math
  ${VTK_SOURCE_DIR}/Common/DataModel
  ${VTK_SOURCE_DIR}/Common/Misc
  ${VTK_SOURCE_DIR}/Common/System
  )

#SET_SOURCE_FILES_PROPERTIES(
#ABSTRACT
#)

#SET_SOURCE_FILES_PROPERTIES(
#  vtkFilteringInformationKeyManager.cxx
#  WRAP_EXCLUDE
#)

#SET_SOURCE_FILES_PROPERTIES(
#  PROPERTIES WRAP_SPECIAL 1
#)

vtk_add_library(vtkCommonExecutionModel ${Kit_SRCS})
target_link_libraries(vtkCommonExecutionModel vtkCommonDataModel)
