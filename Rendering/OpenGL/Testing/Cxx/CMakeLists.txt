SET(RenderingTests
  otherCoordinate.cxx
  TestPriorityStreaming.cxx
  )

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# For tests that actually use a vtkRenderWindow
SET(RenderingTestsWithArguments
  LoadOpenGLExtension.cxx
  TestActorLightingFlag.cxx
  TestAnimationScene.cxx
  TestBackfaceCulling.cxx
  TestBlurAndSobelPasses.cxx
  #TestDynamic2DLabelMapper.cxx
  TestFBO.cxx
  TestFollowerPicking.cxx
  TestGaussianBlurPass.cxx
  TestGlyph3DMapper.cxx
  TestGlyph3DMapperMasking.cxx
  TestGlyph3DMapperOrientationArray.cxx
  TestGlyph3DMapperPicking.cxx
  TestGPUInfo.cxx
  TestGradientBackground.cxx
  TestHomogeneousTransformOfActor.cxx
  #TestImageResliceMapperAlpha.cxx
  #TestImageResliceMapperBackground.cxx
  #TestImageResliceMapperBorder.cxx
  #TestImageResliceMapperInterpolation.cxx
  #TestImageResliceMapperOffAxis.cxx
  #TestImageResliceMapperOrient3D.cxx
  #TestImageResliceMapperSlab.cxx
  TestImageSliceMapperAlpha.cxx
  TestImageSliceMapperBackground.cxx
  TestImageSliceMapperBorder.cxx
  TestImageSliceMapperOrient2D.cxx
  TestImageSliceMapperOrient3D.cxx
  TestImageSliceMapperInterpolation.cxx
  #TestImageStack.cxx
  TestInteractorTimers.cxx
  #TestLabelPlacer.cxx
  #TestLabelPlacer2D.cxx
  #TestLabelPlacerCoincidentPoints.cxx
  #TestLabelPlacementMapper2D.cxx
  #TestLabelPlacementMapperCoincidentPoints.cxx
  TestLightActor.cxx
  TestLODActor.cxx
  TestManyActors.cxx
  TestOffAxisStereo.cxx
  TestOrderedTriangulator.cxx
  TestOpacity.cxx
  TestOpenGLPolyDataMapper.cxx
  TestOSConeCxx.cxx
  TestPOVExporter.cxx
  TestResetCameraVerticalAspectRatio.cxx
  TestResetCameraVerticalAspectRatioParallel.cxx
  #TestSetImageOrientation.cxx
  TestSobelGradientMagnitudePass.cxx
  TestShadowMapPass.cxx
  TestTextActorAlphaBlending.cxx
  TestTextActorDepthPeeling.cxx
  TestTextActor3DAlphaBlending.cxx
  TestTextActor3DDepthPeeling.cxx
  TestTexturedBackground.cxx
  TestTextureSize.cxx
  TestTDx.cxx
  #TestTilingCxx.cxx
  TestTransformCoordinateUseDouble.cxx
  TestTranslucentLUTAlphaBlending.cxx
  TestTranslucentLUTDepthPeeling.cxx
  TestTranslucentLUTDepthPeelingPass.cxx
  TestTranslucentLUTTextureAlphaBlending.cxx
  TestTranslucentLUTTextureDepthPeeling.cxx
  )

if(WIN32 AND NOT VTK_USE_X)
  set(RenderingTestsWithArguments
    ${RenderingTestsWithArguments}
    TestWin32OpenGLRenderWindow.cxx
    )
endif()

if(VTK_DATA_ROOT)
  set(RenderingTestsWithArguments
    ${RenderingTestsWithArguments}
    TestAreaSelections.cxx
    TestMultiTexturing.cxx
    TestMultiTexturingTransform.cxx
    TestGlyph3DMapperArrow.cxx
    #TestScalarBar.cxx
    TestScenePicker.cxx
    TestTextureRGBA.cxx
    TestTextureRGBADepthPeeling.cxx
    TestTranslucentImageActorAlphaBlending.cxx
    TestTranslucentImageActorDepthPeeling.cxx
    TestTStripsColorsTCoords.cxx
    TestTStripsNormalsColorsTCoords.cxx
    TestTStripsNormalsTCoords.cxx
    TestTStripsTCoords.cxx
    )
endif()

if(VTK_USE_DISPLAY AND VTK_DATA_ROOT)
  set(RenderingTestsWithArguments
    ${RenderingTestsWithArguments}
    RenderNonFinite.cxx
    SurfacePlusEdges.cxx
    TestLabelPlacementMapper.cxx
    )
endif()

if(VTK_USE_GLSL_SHADERS)
  # Tests testing GLSL Shaders.
  set(RenderingTestsWithArguments
    ${RenderingTestsWithArguments}
    TestGenericVertexAttributesGLSLCxx.cxx
    TestGenericVertexAttributesGLSLAlphaBlending.cxx
    TestGenericVertexAttributesGLSLDepthPeelingPass.cxx
    )
  # Temporarily disable LIC tests on Mac
  if(NOT APPLE)
    if(VTK_DATA_ROOT)
      set(RenderingTestsWithArguments
        ${RenderingTestsWithArguments}
        TestSurfaceLIC.cxx
        )
    endif()
  endif()
endif()

CREATE_TEST_SOURCELIST(Tests ${vtk-module}CxxTests.cxx
  ${RenderingTests};${RenderingTestsWithArguments}
  EXTRA_INCLUDE vtkTestDriver.h
  )

set(TEST_FBO_IMPLEMENTATION_EXE
  TestFBOImplementation)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TestFBOInclude.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/TestFBOInclude.h
  @ONLY IMMEDIATE ESCAPE_QUOTES)

# This is used by TestFBO. Using a separate processes makes is possible to
# avoid issues to OpenGL implementations segfaulting etc. from affecting the
# test.
vtk_add_test_executable(TestFBOImplementation
  TestFBOImplementation.cxx)
target_link_libraries(TestFBOImplementation
  vtkRenderingOpenGL ${OPENGL_gl_LIBRARY})

if(VTK_OPENGL_HAS_OSMESA AND OSMESA_LIBRARY)
  target_link_libraries(TestFBOImplementation ${OSMESA_LIBRARY})
endif()

vtk_add_test_executable(${vtk-module}CxxTests ${Tests})

if(VTK_OPENGL_HAS_OSMESA AND OSMESA_LIBRARY)
  TARGET_LINK_LIBRARIES(${vtk-module}CxxTests ${OSMESA_LIBRARY})
endif()

set(TestsToRun ${Tests})
remove(TestsToRun CxxTests.cxx)

#
# Add all the executables
foreach(test ${RenderingTests})
  get_filename_component(TName ${test} NAME_WE)
  add_test(NAME RenderingOpenGL-${TName}
    COMMAND ${vtk-module}CxxTests ${TName}
      -T ${VTK_BINARY_DIR}/Testing/Temporary
    )
endforeach()

foreach(test ${RenderingTestsWithArguments})
  GET_FILENAME_COMPONENT(TName ${test} NAME_WE)
  if(VTK_DATA_ROOT)
    add_test(NAME RenderingOpenGL-${TName}
      COMMAND ${vtk-module}CxxTests ${TName}
        -D ${VTK_DATA_ROOT}
        -T ${VTK_BINARY_DIR}/Testing/Temporary
        -V Baseline/Rendering/${TName}.png)
  else()
    add_test(NAME RenderingOpenGL-${TName}
      COMMAND ${vtk-module}CxxTests ${TName}
        -T ${VTK_BINARY_DIR}/Testing/Temporary
      )
  endif()
endforeach()

#
# Add other odd tests or executables
#
FOREACH (exe
    TimeRenderer
    TimeRenderer2
    VTKBenchMark
    )
  ADD_EXECUTABLE(${exe} ${exe}.cxx)
  TARGET_LINK_LIBRARIES(${exe} vtkRenderingOpenGL vtkIOCore ${OPENGL_gl_LIBRARY})
  IF (APPLE)
    TARGET_LINK_LIBRARIES(${exe} "-framework GLUT")
  ENDIF (APPLE)
  IF (VTK_OPENGL_HAS_OSMESA AND OSMESA_LIBRARY)
    TARGET_LINK_LIBRARIES(${exe} ${OSMESA_LIBRARY})
  ENDIF (VTK_OPENGL_HAS_OSMESA AND OSMESA_LIBRARY)
ENDFOREACH (exe)

IF(VTK_USE_GLSL_SHADERS AND VTK_USE_DISPLAY)
  set_tests_properties(TestGenericVertexAttributesGLSLDepthPeelingPass PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR:.*vtkOpenGLProperty.*Couldn't build the shader program. At this point , it can be an error in a shader or a driver bug.")
ENDIF(VTK_USE_GLSL_SHADERS AND VTK_USE_DISPLAY)
