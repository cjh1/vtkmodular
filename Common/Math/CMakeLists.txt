
SET(Kit_SRCS
  vtkAmoebaMinimizer.cxx
  vtkFastNumericConversion.cxx
  vtkFunctionSet.cxx
  vtkInitialValueProblemSolver.cxx
  vtkMatrix3x3.cxx
  vtkMatrix4x4.cxx
  vtkPolynomialSolversUnivariate.cxx
  vtkQuaternionInterpolator.cxx
  vtkRungeKutta2.cxx
  vtkRungeKutta4.cxx
  vtkRungeKutta45.cxx
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set_source_files_properties(
   vtkPolynomialSolversUnivariate.cxx
   PROPERTIES
   COMPILE_FLAGS -O0
   )
endif()

vtk_add_library(vtkCommonMath ${Kit_SRCS})
