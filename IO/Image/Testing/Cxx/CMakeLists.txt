
set(TEST_SRC ${vtk-module}CxxTests.cxx)


if(WIN32)
  list(APPEND TEST_SRC TestAVIWriter.cxx)
endif()


create_test_sourcelist(Tests ${vtk-module}CxxTests.cxx
  ${TEST_SRC}
  EXTRA_INCLUDE vtkTestDriver.h
)

#vtk_add_test_executable(${vtk-module}CxxTests ${Tests})
