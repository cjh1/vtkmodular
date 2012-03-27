create_test_sourcelist(Tests ${vtk-module}CxxTests.cxx
  # TestAxisActor3D.cxx # todo (may not be in vtk in the first place)
  TestBarChartActor.cxx
  TestCubeAxes2DMode.cxx
  TestCubeAxes3.cxx             # todo (unsatistfied deps)
  TestCubeAxesWithGridLines.cxx # todo (unsatistfied deps)
  TestCubeAxesWithXInnerGrids.cxx # todo (unsatistfied deps)
  TestCubeAxesWithXInnerPolys.cxx # todo (unsatistfied deps)
  TestCubeAxesWithXLines.cxx    # todo (unsatistfied deps)
  TestCubeAxesWithYInnerGrids.cxx # todo (unsatistfied deps)
  TestCubeAxesWithYInnerPolys.cxx # todo (unsatistfied deps)
  TestCubeAxesWithYLines.cxx      # todo (unsatistfied deps)
  TestCubeAxesWithZInnerGrids.cxx # todo (unsatistfied deps)
  TestCubeAxesWithZInnerPolys.cxx # todo (unsatistfied deps)
  TestCubeAxesWithZLines.cxx # todo (unsatistfied deps)
  TestLegendBoxActor.cxx
  TestLegendScaleActor.cxx
  TestPieChartActor.cxx
  TestPolarAxes.cxx
  TestSpiderPlotActor.cxx

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
