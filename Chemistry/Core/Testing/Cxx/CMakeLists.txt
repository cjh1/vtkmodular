set(MyTests
  TestBallAndStick.cxx
  TestBondColorModeDiscreteByAtom.cxx
  TestBondColorModeSingleColor.cxx
  TestCompositeRender.cxx
  TestFastRender.cxx
  TestLiquoriceSticks.cxx
  TestMolecule.cxx
  TestMoleculeSelection.cxx
  TestMultiCylinderOn.cxx
  TestMultiCylinderOff.cxx
  TestPeriodicTable.cxx
  TestProgrammableElectronicData.cxx
  TestSimpleBondPerceiver.cxx
  TestVDWSpheres.cxx
  )

# Tests with data
if(VTK_DATA_ROOT)
  set(MyTests
    ${MyTests}
    TestCMLMoleculeReader.cxx
    )
  if(VTK_USE_OPENQUBE)
    # Add Eigen to the include path for the OpenQube headers
    include_directories(${EIGEN2_INCLUDE_DIR})
    set(MyTests
      ${MyTests}
      TestOpenQubeElectronicData.cxx
      TestOpenQubeMOPACDensity.cxx
      TestOpenQubeMOPACOrbital.cxx
    )
  endif()
endif()

# Use the testing object factory, to reduce boilerplate code in tests.
#include("${VTK_SOURCE_DIR}/Rendering/vtkTestingObjectFactory.cmake")
#vtk_add_test_executable(${vtk-module}CxxTests ${MyTests})
#target_link_libraries(${vtk-module}CxxTests
#                      vtkChemistry
#                      vtkRendering
#                      vtkVolumeRendering)

set(TestsToRun ${MyTests})
list(REMOVE_ITEM TestsToRun ${vtk-module}CxxTests.cxx)

# Add all the executables
FOREACH (test ${TestsToRun})
  GET_FILENAME_COMPONENT(TName ${test} NAME_WE)
  if(VTK_DATA_ROOT)
    if(${${TName}Error})
      set(_error_threshold ${${TName}Error})
    else()
      set(_error_threshold 10)
    endif()
    add_test(Chemistry-${TName} ${CXX_TEST_PATH}/${KIT}CxxTests ${TName}
      -D ${VTK_DATA_ROOT}
      -T ${VTK_BINARY_DIR}/Testing/Temporary
      -V Baseline/${KIT}/${TName}.png
      -E ${_error_threshold})
  else()
    add_test(Chemistry-${TName} ${CXX_TEST_PATH}/${KIT}CxxTests ${TName})
  endif()
endforeach ()
