CREATE_TEST_SOURCELIST(Tests ${vtk-module}CxxTests.cxx
  TestVector.cxx
  EXTRA_INCLUDE vtkTestDriver.h
)

ADD_EXECUTABLE(${vtk-module}CxxTests ${Tests})
SET (TestsToRun ${Tests})
REMOVE (TestsToRun ${vtk-module}CxxTests.cxx)

# Configure a header needed by SystemInformation.
#CONFIGURE_FILE("${VTK_SOURCE_DIR}/Common/Testing/Cxx/SystemInformation.h.in"
#               "${VTK_BINARY_DIR}/Common/Testing/Cxx/SystemInformation.h"
#               @ONLY IMMEDIATE)

#
# Add all the executables
FOREACH (test ${TestsToRun})
  GET_FILENAME_COMPONENT(TName ${test} NAME_WE)
  ADD_TEST(NAME ${TName} COMMAND ${CXX_TEST_PATH}/${vtk-module}CxxTests ${TName})
  message("${TName} ${CXX_TEST_PATH}/${vtk-module}CxxTests ${TName}")
ENDFOREACH (test)
