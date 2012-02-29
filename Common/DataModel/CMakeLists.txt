
# DataModel
set(Kit_SRCS
  vtkAbstractCellLocator.cxx
  vtkAbstractInterpolatedVelocityField.cxx
  vtkAbstractPointLocator.cxx
  vtkAdjacentVertexIterator.cxx
#  vtkAlgorithm.cxx
#  vtkAlgorithmOutput.cxx
  vtkAMRBox.cxx
  vtkAnimationScene.cxx
  vtkAnnotation.cxx
#  vtkAnnotationLayersAlgorithm.cxx
  vtkAnnotationLayers.cxx
#  vtkArrayDataAlgorithm.cxx
  vtkArrayData.cxx
  vtkAttributesErrorMetric.cxx
  vtkBiQuadraticQuad.cxx
  vtkBiQuadraticQuadraticHexahedron.cxx
  vtkBiQuadraticQuadraticWedge.cxx
  vtkBiQuadraticTriangle.cxx
  vtkBox.cxx
  vtkBSPCuts.cxx
  vtkBSPIntersections.cxx
#  vtkCachedStreamingDemandDrivenPipeline.cxx
#  vtkCastToConcrete.cxx
  vtkCell3D.cxx
  vtkCellArray.cxx
  vtkCell.cxx
  vtkCellData.cxx
  vtkCellLinks.cxx
  vtkCellLocator.cxx
  vtkCellTypes.cxx
  vtkCompositeDataIterator.cxx
#  vtkCompositeDataPipeline.cxx
#  vtkCompositeDataSetAlgorithm.cxx
  vtkCompositeDataSet.cxx
#  vtkComputingResources.cxx
  vtkCone.cxx
  vtkConvexPointSet.cxx
  vtkCubicLine.cxx
  vtkCylinder.cxx
#  vtkDataObjectAlgorithm.cxx
  vtkDataObjectCollection.cxx
  vtkDataObject.cxx
#  vtkDataObjectSource.cxx
  vtkDataObjectTypes.cxx
#  vtkDataSetAlgorithm.cxx
  vtkDataSetAttributes.cxx
  vtkDataSetCollection.cxx
  vtkDataSet.cxx
#  vtkDataSetSource.cxx
#  vtkDataSetToDataSetFilter.cxx
#  vtkDataSetToImageFilter.cxx
#  vtkDataSetToPolyDataFilter.cxx
#  vtkDataSetToStructuredGridFilter.cxx
#  vtkDataSetToStructuredPointsFilter.cxx
#  vtkDataSetToUnstructuredGridFilter.cxx
#  vtkDemandDrivenPipeline.cxx
  vtkDirectedAcyclicGraph.cxx
#  vtkDirectedGraphAlgorithm.cxx
  vtkDirectedGraph.cxx
  vtkDistributedGraphHelper.cxx
  vtkEdgeListIterator.cxx
  vtkEdgeTable.cxx
  vtkEmptyCell.cxx
#  vtkExecutionScheduler.cxx
#  vtkExecutionSchedulerManager.cxx
#  vtkExecutiveCollection.cxx
#  vtkExecutive.cxx
  vtkExplicitCell.cxx
#  vtkExtentSplitter.cxx
#  vtkExtentTranslator.cxx
  vtkFieldData.cxx
#  vtkFilteringInformationKeyManager.cxx
  vtkGenericAdaptorCell.cxx
  vtkGenericAttributeCollection.cxx
  vtkGenericAttribute.cxx
  vtkGenericCell.cxx
  vtkGenericCellIterator.cxx
  vtkGenericCellTessellator.cxx
#  vtkGenericDataSetAlgorithm.cxx
  vtkGenericDataSet.cxx
  vtkGenericEdgeTable.cxx
  vtkGenericInterpolatedVelocityField.cxx
  vtkGenericPointIterator.cxx
  vtkGenericSubdivisionErrorMetric.cxx
  vtkGeometricErrorMetric.cxx
#  vtkGraphAlgorithm.cxx
  vtkGraph.cxx
  vtkGraphEdge.cxx
  vtkGraphInternals.cxx
  vtkHexagonalPrism.cxx
  vtkHexahedron.cxx
  vtkHierarchicalBoxDataIterator.cxx
#  vtkHierarchicalBoxDataSetAlgorithm.cxx
  vtkHierarchicalBoxDataSet.cxx
#  vtkHyperOctreeAlgorithm.cxx
  vtkHyperOctreeCursor.cxx
  vtkHyperOctree.cxx
  vtkHyperOctreePointsGrabber.cxx
#  vtkImageAlgorithm.cxx
  vtkImageData.cxx
#  vtkImageInPlaceFilter.cxx
  vtkImageIterator.cxx
#  vtkImageMultipleInputFilter.cxx
#  vtkImageMultipleInputOutputFilter.cxx
#  vtkImageProgressIterator.cxx
#  vtkImageSource.cxx
#  vtkImageToImageFilter.cxx
#  vtkImageToStructuredGrid.cxx
#  vtkImageToStructuredPoints.cxx
#  vtkImageTwoInputFilter.cxx
  vtkImplicitBoolean.cxx
  vtkImplicitDataSet.cxx
  vtkImplicitFunctionCollection.cxx
  vtkImplicitFunction.cxx
  vtkImplicitHalo.cxx
  vtkImplicitSelectionLoop.cxx
  vtkImplicitSum.cxx
  vtkImplicitVolume.cxx
  vtkImplicitWindowFunction.cxx
  vtkIncrementalOctreeNode.cxx
  vtkIncrementalOctreePointLocator.cxx
  vtkIncrementalPointLocator.cxx
  vtkInEdgeIterator.cxx
#  vtkInformationExecutivePortKey.cxx
#  vtkInformationExecutivePortVectorKey.cxx
  vtkInformationQuadratureSchemeDefinitionVectorKey.cxx
  vtkInterpolatedVelocityField.cxx
  vtkIterativeClosestPointTransform.cxx
  vtkKdNode.cxx
  vtkKdTree.cxx
  vtkKdTreePointLocator.cxx
  vtkLine.cxx
  vtkLocator.cxx
  vtkMarchingSquaresLineCases.cxx
  vtkMarchingCubesTriangleCases.cxx
  vtkMeanValueCoordinatesInterpolator.cxx
  vtkMergePoints.cxx
#  vtkMultiBlockDataSetAlgorithm.cxx
  vtkMultiBlockDataSet.cxx
  vtkMultiPieceDataSet.cxx
  vtkMutableDirectedGraph.cxx
  vtkMutableUndirectedGraph.cxx
  vtkNonLinearCell.cxx
  vtkNonMergingPointLocator.cxx
  vtkOctreePointLocator.cxx
  vtkOctreePointLocatorNode.cxx
#  vtkOnePieceExtentTranslator.cxx
  vtkOrderedTriangulator.cxx
  vtkOutEdgeIterator.cxx
#  vtkPassInputTypeAlgorithm.cxx
  vtkPentagonalPrism.cxx
  vtkPerlinNoise.cxx
#  vtkPiecewiseFunctionAlgorithm.cxx
  vtkPiecewiseFunction.cxx
#  vtkPiecewiseFunctionShiftScale.cxx
  vtkPixel.cxx
  vtkPlaneCollection.cxx
  vtkPlane.cxx
  vtkPlanes.cxx
  vtkPlanesIntersection.cxx
  vtkPointData.cxx
  vtkPointLocator.cxx
#  vtkPointSetAlgorithm.cxx
  vtkPointSet.cxx
#  vtkPointSetSource.cxx
#  vtkPointSetToPointSetFilter.cxx
  vtkPointsProjectedHull.cxx
#  vtkPolyDataAlgorithm.cxx
  vtkPolyDataCollection.cxx
  vtkPolyData.cxx
#  vtkPolyDataSource.cxx
#  vtkPolyDataToPolyDataFilter.cxx
  vtkPolygon.cxx
  vtkPolyhedron.cxx
  vtkPolyLine.cxx
  vtkPolyPlane.cxx
  vtkPolyVertex.cxx
#  vtkProcessObject.cxx
  vtkPyramid.cxx
  vtkQuad.cxx
  vtkQuadraticEdge.cxx
  vtkQuadraticHexahedron.cxx
  vtkQuadraticLinearQuad.cxx
  vtkQuadraticLinearWedge.cxx
  vtkQuadraticPyramid.cxx
  vtkQuadraticQuad.cxx
  vtkQuadraticTetra.cxx
  vtkQuadraticTriangle.cxx
  vtkQuadraticWedge.cxx
  vtkQuadratureSchemeDefinition.cxx
  vtkQuadric.cxx
#  vtkRectilinearGridAlgorithm.cxx
  vtkRectilinearGrid.cxx
#  vtkRectilinearGridSource.cxx
#  vtkRectilinearGridToPolyDataFilter.cxx
  vtkReebGraph.cxx
  vtkReebGraphSimplificationMetric.cxx
#  vtkScalarTree.cxx
  vtkSelection.cxx
  vtkSelectionNode.cxx
  vtkSimpleCellTessellator.cxx
#  vtkSimpleImageToImageFilter.cxx
#  vtkSimpleScalarTree.cxx
  vtkSmoothErrorMetric.cxx
#  vtkSource.cxx
  vtkSphere.cxx
  vtkSpline.cxx
#  vtkStreamingDemandDrivenPipeline.cxx
  vtkStructuredData.cxx
  vtkStructuredExtent.cxx
#  vtkStructuredGridAlgorithm.cxx
  vtkStructuredGrid.cxx
#  vtkStructuredGridSource.cxx
#  vtkStructuredGridToPolyDataFilter.cxx
#  vtkStructuredGridToStructuredGridFilter.cxx
  vtkStructuredPointsCollection.cxx
  vtkStructuredPoints.cxx
#  vtkStructuredPointsSource.cxx
#  vtkStructuredPointsToPolyDataFilter.cxx
#  vtkStructuredPointsToStructuredPointsFilter.cxx
#  vtkStructuredPointsToUnstructuredGridFilter.cxx
  vtkStructuredVisibilityConstraint.cxx
  vtkSuperquadric.cxx
#  vtkTableAlgorithm.cxx
  vtkTable.cxx
#  vtkTableExtentTranslator.cxx
#  vtkTemporalDataSetAlgorithm.cxx
  vtkTemporalDataSet.cxx
  vtkTensor.cxx
  vtkTetra.cxx
#  vtkThreadedImageAlgorithm.cxx
#  vtkThreadedStreamingPipeline.cxx
#  vtkTreeAlgorithm.cxx
  vtkTreeBFSIterator.cxx
  vtkTree.cxx
  vtkTreeDFSIterator.cxx
  vtkTriangle.cxx
  vtkTriangleStrip.cxx
  vtkTriQuadraticHexahedron.cxx
#  vtkTrivialProducer.cxx
#  vtkUndirectedGraphAlgorithm.cxx
  vtkUndirectedGraph.cxx
  vtkUniformGrid.cxx
#  vtkUnstructuredGridAlgorithm.cxx
  vtkUnstructuredGrid.cxx
#  vtkUnstructuredGridSource.cxx
#  vtkUnstructuredGridToPolyDataFilter.cxx
#  vtkUnstructuredGridToUnstructuredGridFilter.cxx
  vtkVertex.cxx
  vtkVertexListIterator.cxx
  vtkVoxel.cxx
  vtkWedge.cxx
  vtkXMLDataElement.cxx
  vtkTreeIterator.cxx
  )

include_directories(
  ${vtkCommonExecutionModel_SOURCE_DIR}
  ${vtkCommonExecutionModel_BINARY_DIR}
  )

set_source_files_properties(
  vtkAbstractCellLocator
  vtkAbstractInterpolatedVelocityField
  vtkAbstractPointLocator
  vtkCell
  vtkCell3D
  vtkCompositeDataIterator
  vtkCompositeDataSet
  ABSTRACT
  )

set_source_files_properties(
  vtkAMRBox.cxx
  vtkExecutionScheduler.cxx
  vtkExecutionSchedulerManager.cxx
  vtkFilteringInformationKeyManager.cxx
  WRAP_EXCLUDE
  )

vtk_module_library(vtkCommonDataModel ${Kit_SRCS})
