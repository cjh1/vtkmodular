create_test_sourcelist(Tests ${vtk-module}CxxTests.cxx
  # Volume rendering in not in yet
  # ExerciseUnstructuredGridRayCastMapper.cxx
  # HomogeneousRayIntegration.cxx
  # LinearRayIntegration.cxx
  # PartialPreIntegration.cxx
  # PreIntegrationIncremental.cxx
  # PreIntegrationNonIncremental.cxx
  # ProjectedTetrahedraZoomIn.cxx
  # TestFinalColorWindowLevel.cxx
  # TestFixedPointRayCastLightComponents.cxx
  # TestGPURayCastAdditive.cxx
  # TestGPURayCastCompositeBinaryMask.cxx
  # TestGPURayCastCompositeMask.cxx
  # TestGPURayCastCompositeMaskBlend.cxx
  # TestGPURayCastCompositeShadeMask.cxx
  # TestGPURayCastCompositeToMIP.cxx
  # TestGPURayCastCropping.cxx
  # TestGPURayCastDataTypesMIP.cxx
  # TestGPURayCastDataTypesMinIP.cxx
  # TestGPURayCastFourComponentsComposite.cxx
  # TestGPURayCastFourComponentsCompositeStreaming.cxx
  # TestGPURayCastFourComponentsMIP.cxx
  # TestGPURayCastFourComponentsMinIP.cxx
  # TestGPURayCastMIPBinaryMask.cxx
  # TestGPURayCastMIPToComposite.cxx
  # TestGPURayCastNearestDataTypesMIP.cxx
  # TestGPURayCastPerspectiveParallel.cxx
  # TestHAVSVolumeMapper.cxx
  # TestMinIntensityRendering.cxx
  # TestProjectedHexahedra.cxx
  # TestProjectedTetrahedra.cxx
  # TestProp3DFollower.cxx
  # TestSmartVolumeMapper.cxx
  # TestSmartVolumeMapperWindowLevel.cxx
  # TestTM3DLightComponents.cxx
  # ZsweepConcavities.cxx
  # volProt.cxx

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
