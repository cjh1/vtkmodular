create_test_sourcelist(Tests ${vtk-module}CxxTests.cxx
  BoxWidget.cxx
  BoxWidget2.cxx
  # ImagePlaneWidget.cxx # todo (unsatisfied deps)
  # ScaledBoxWidget2.cxx # may not have been included in original
  TerrainPolylineEditor.cxx # todo (unsatisfied deps)
  TestAffineWidget.cxx
  TestAngleWidget2D.cxx
  TestAngleWidget3D.cxx
  TestAxesTransformWidget.cxx
  TestBalloonWidget.cxx
  TestBiDimensionalWidget.cxx
  TestBorderWidget.cxx
  # TestBrokenLineWidget.cxx # todo (unsatisfied deps)
  # TestButtonWidget.cxx # todo (unsatistfied deps)
  TestCameraWidget.cxx
  TestCaptionWidget.cxx
  TestCellCentersPointPlacer.cxx
  TestCenteredSliderWidget2D.cxx # todo (unsatisfied deps)
  TestCheckerboardWidget.cxx
  TestConstrainedHandleWidget.cxx
  TestContourWidget2.cxx
  TestDijkstraGraphGeodesicPath.cxx # todo (unsatistfied deps)
  TestDijkstraImageGeodesicPath.cxx
  TestDistanceWidget.cxx
  TestDistanceWidget3D.cxx
  TestFixedSizeHandleRepresentation3D.cxx
  TestFocalPlaneContour.cxx
  TestHandleWidget.cxx # todo (unsatistfied deps)
  TestHandleWidget2D.cxx
  # TestImageActorContourWidget.cxx # todo(unsatistfied deps)
  TestImageTracerWidget.cxx
  TestImplicitPlaneWidget.cxx # todo (unsatistfied deps)
  TestImplicitPlaneWidget2.cxx # todo (unsatistfied deps)
  TestImplicitPlaneWidget2LockNormalToCamera.cxx # todo (unsatistfied deps)
  TestImplicitPlaneWidget2b.cxx # todo (unsatistfied deps)
  TestLineWidget.cxx
  TestLineWidget2.cxx
  TestLogoWidget.cxx
  TestLogoWidgetAlphaBlending.cxx
  TestLogoWidgetDepthPeeling.cxx
  TestOrientationMarkerWidget.cxx
  TestOrientedGlyphContour.cxx
  # TestOrthoPlanes.cxx # todo (unsatistfied deps)
  TestParallelopipedWidget.cxx
  TestPlaneWidget.cxx
  TestPlaybackWidget.cxx
  TestPointHandleRepresentation3D.cxx
  TestPointWidget.cxx
  TestPolyPlane.cxx
  TestPolygonalHandleRepresentations.cxx #todo (unsatistfied deps)
  TestPolygonalRepresentationHandleWidget.cxx # todo (unsatistfied deps)
  TestPolygonalSurfaceConstrainedDistanceWidget.cxx # todo (unsatistfied deps)
  TestProgrammaticPlacement.cxx
  TestRectilinearWipeWidget.cxx
  # TestResliceCursorWidget2.cxx # todo (unsatistfied deps)
  # TestResliceCursorWidget3.cxx # todo (unsatistfied deps)
  TestScalarBarWidget.cxx
  TestSeedWidget.cxx
  TestSeedWidget2.cxx
  TestSeedWidgetNonUniformRepresentations.cxx
  TestSliderWidget.cxx # todo (unsatistfied deps)
  TestSliderWidget2D.cxx #todo (unsatistfied deps)
  TestSphereHandleWidget.cxx # todo (unsatistfied deps)
  # TestSplineWidget.cxx # todo (unsatistfied deps)
  TestSurfaceConstrainedHandleWidget.cxx # todo (unsatistfied deps)
  TestTensorProbeWidget.cxx
  TestTextWidget.cxx
  vtkAngleRepresentation2DTest1.cxx
  vtkAngleRepresentation3DTest1.cxx
  vtkAngleWidgetTest1.cxx
  vtkBalloonRepresentationTest1.cxx
  vtkBalloonWidgetTest1.cxx
  vtkBiDimensionalRepresentation2DTest1.cxx
  vtkBiDimensionalWidgetTest1.cxx
  vtkBorderWidgetTest1.cxx
  vtkCaptionRepresentationTest1.cxx
  vtkCaptionWidgetTest1.cxx
  # vtkConstrainedPointHandleRepresentationTest1.cxx # fixme
  vtkHoverWidgetTest1.cxx
  # vtkImplicitPlaneRepresentationTest1.cxx # fixme
  # vtkImplicitPlaneWidget2Test1.cxx # todo (unsatistfied deps)
  vtkLineRepresentationTest1.cxx
  vtkLineWidget2Test1.cxx
  # vtkOrientedPolygonalHandleRepresentation3DTest1.cxx # fixme
  # vtkPointHandleRepresentation2DTest1.cxx  # fixme
  # vtkPointHandleRepresentation3DTest1.cxx # fixme
  # vtkPolygonalHandleRepresentation3DTest1.cxx # fixme
  vtkSeedRepresentationTest1.cxx
  vtkSeedWidgetTest1.cxx
  # vtkSphereHandleRepresentationTest1.cxx # fixme
  vtkSplineRepresentationTest1.cxx
  vtkSplineWidget2Test1.cxx
  vtkTextRepresentationTest1.cxx
  vtkTextWidgetTest1.cxx

  EXTRA_INCLUDE vtkTestDriver.h
)

vtk_add_test_executable(${vtk-module}CxxTests ${Tests})

set(TestsToRun ${Tests})
list(REMOVE_ITEM TestsToRun ${vtk-module}CxxTests.cxx)

# Add all the executables
foreach(test ${TestsToRun})
  get_filename_component(TName ${test} NAME_WE)
  if(VTK_DATA_ROOT)
    add_test(NAME ${vtk-module}Cxx-${TName}
            COMMAND ${vtk-module}CxxTests ${TName}
                                          -D ${VTK_DATA_ROOT}
                                          -T ${VTK_BINARY_DIR}/Testing/Temporary
                                          -V Baseline/${vtk-module}/${TName}.png)
  else()
    add_test(NAME ${vtk-module}Cxx-${TName} COMMAND ${vtk-module}CxxTests ${TName})
  endif()
endforeach()
