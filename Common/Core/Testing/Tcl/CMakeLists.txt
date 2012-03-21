add_test(TestSetObjectMacro-Common ${TCL_TCLSH}
         ${vtkCommonCore_SOURCE_DIR}/Testing/Tcl/FindString.tcl
         "${VTK_SOURCE_DIR}/Common/Core/vtk\\\\*.h"
         "vtkSetObjectMacro"
         ${VTK_SOURCE_DIR}/Common/Core/vtkSetGet.h
         )
add_test(PrintSelf-CommonCore ${TCL_TCLSH}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/PrintSelfCheck.tcl
	 ${VTK_SOURCE_DIR}/Common/Core)
add_test(NAME TestArraysTCL
  COMMAND ${VTK_TCL_EXE}
    ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/TestArrays.tcl
    -A ${VTK_SOURCE_DIR}/Wrapping/Tcl)
add_test(TestEmptyInput ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/TestEmptyInput.tcl
         -A ${VTK_SOURCE_DIR}/Wrapping/Tcl)
add_test(TestSetGet ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/TestSetGet.tcl
         -A ${VTK_SOURCE_DIR}/Wrapping/Tcl)
add_test(TestString ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/TestString.tcl)
add_test(TestIgnoreBTX ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/TestIgnoreBTX.tcl)
add_test(otherInterp ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/otherInterp.tcl
         -A ${VTK_SOURCE_DIR}/Wrapping/Tcl)
add_test(otherPrint ${VTK_EXECUTABLE}
         ${${vtk-module}_SOURCE_DIR}/Testing/Tcl/otherPrint.tcl
         -A ${VTK_SOURCE_DIR}/Wrapping/Tcl)
