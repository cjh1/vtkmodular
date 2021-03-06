set(Kit_SRCS
  vtkAnnotationLink.cxx
  vtkAppendCompositeDataLeaves.cxx
  vtkAppendPoints.cxx
  vtkApproximatingSubdivisionFilter.cxx
  vtkAreaContourSpectrumFilter.cxx
  vtkAxes.cxx
  vtkBlankStructuredGrid.cxx
  vtkBlankStructuredGridWithImage.cxx
  vtkBlockIdScalars.cxx
  vtkBoxClipDataSet.cxx
  vtkBrownianPoints.cxx
  vtkCellCenters.cxx
  vtkCellDerivatives.cxx
  vtkClipClosedSurface.cxx
  vtkClipConvexPolyData.cxx
  vtkClipDataSet.cxx
  vtkClipVolume.cxx
  vtkCoincidentPoints.cxx
  vtkCursor2D.cxx
  vtkCursor3D.cxx
  vtkCurvatures.cxx
  vtkDashedStreamLine.cxx
  vtkDataSetGradient.cxx
  vtkDataSetGradientPrecompute.cxx
  vtkDataSetTriangleFilter.cxx
  vtkDensifyPolyData.cxx
  vtkDicer.cxx
  vtkDiscreteMarchingCubes.cxx
  vtkEdgePoints.cxx
  vtkGradientFilter.cxx
  vtkGraphLayoutFilter.cxx
  vtkGraphToPoints.cxx
  vtkHierarchicalDataLevelFilter.cxx
  vtkHyperStreamline.cxx
  vtkIconGlyphFilter.cxx
  vtkImageMarchingCubes.cxx
  vtkInterpolateDataSetAttributes.cxx
  vtkInterpolatingSubdivisionFilter.cxx
  vtkKdTreeSelector.cxx
  vtkLevelIdScalars.cxx
  vtkLinkEdgels.cxx
  vtkMergeCells.cxx
  vtkModelMetadata.cxx
  vtkMultiBlockDataGroupFilter.cxx
  vtkMultiBlockMergeFilter.cxx
  vtkMultiThreshold.cxx
  vtkOBBDicer.cxx
  vtkOBBTree.cxx
  vtkPassThrough.cxx
  vtkPolyDataStreamer.cxx
  vtkPolyDataToReebGraphFilter.cxx
  vtkProbePolyhedron.cxx
  vtkQuadraturePointInterpolator.cxx
  vtkQuadraturePointsGenerator.cxx
  vtkQuadratureSchemeDictionaryGenerator.cxx
  vtkQuantizePolyDataPoints.cxx
  vtkRandomAttributeGenerator.cxx
  vtkRectilinearGridClip.cxx
  vtkRectilinearGridToTetrahedra.cxx
  vtkRecursiveDividingCubes.cxx
  vtkReflectionFilter.cxx
  vtkRotationFilter.cxx
  vtkSCurveSpline.cxx
  vtkShrinkFilter.cxx
  vtkShrinkPolyData.cxx
  vtkSpatialRepresentationFilter.cxx
  vtkSplineFilter.cxx
  vtkSplitField.cxx
  vtkStructuredGridClip.cxx
  vtkSubPixelPositionEdgels.cxx
  vtkTableBasedClipDataSet.cxx
  vtkTableToPolyData.cxx
  vtkTableToStructuredGrid.cxx
  vtkTemporalPathLineFilter.cxx
  vtkTemporalStatistics.cxx
  vtkTessellatorFilter.cxx
  vtkTimeSourceExample.cxx
  vtkTransformFilter.cxx
  vtkTransformPolyDataFilter.cxx
  vtkUncertaintyTubeFilter.cxx
  vtkVertexGlyphFilter.cxx
  vtkVolumeContourSpectrumFilter.cxx
  vtkVoxelContoursToSurfaceFilter.cxx
  vtkWarpLens.cxx
  vtkWarpScalar.cxx
  vtkWarpTo.cxx
  vtkWarpVector.cxx
  vtkYoungsMaterialInterface.cxx

  vtkMarchingContourFilter.cxx

  # Depend upon FiltersSources
  #vtkStreamTracer.cxx # Needs vtkModifiedBSPTree
  #vtkModifiedBSPTree.cxx # Needs vtkCubeSource.h
  #vtkCellLocatorInterpolatedVelocityField.cxx # Needs vtkModifiedBSPTree
  #vtkGraphToPolyData.cxx # Needs vtkGlyphSource2D
  #vtkOutlineCornerFilter.cxx # Needs vtkOutlineCornerSource

  # Depend upon IO/Image
  #vtkSliceCubes.cxx # Needs vtkVolumeReader

  # Move to FiltersGeometry
  #vtkDataSetSurfaceFilter.cxx # Needs vtkStructuredGridGeometryFilter - Geometry

  vtkRectilinearGridToPointSet.cxx
  vtkGraphWeightEuclideanDistanceFilter.cxx
  vtkGraphWeightFilter.cxx
  vtkImageSincInterpolator.cxx
  vtkGraphAnnotationLayersFilter.cxx
  vtkImageDataToPointSet.cxx
  vtkIntersectionPolyDataFilter.cxx
  vtkBooleanOperationPolyDataFilter.cxx
  vtkDistancePolyDataFilter.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Utilities
  )

vtk_add_library(vtkFiltersGeneral ${Kit_SRCS})
