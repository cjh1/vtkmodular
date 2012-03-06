create_test_sourcelist(Tests ${vtk-module}CxxTests.cxx
  TestArrayAPI.cxx
  TestArrayAPIConvenience.cxx
  TestArrayAPIDense.cxx
  TestArrayAPISparse.cxx
  TestArrayBool.cxx
  TestArrayCasting.cxx
  TestArrayExtents.cxx
  TestArrayInterpolationDense.cxx
  TestArrayLookup.cxx
  TestArrayNullValues.cxx
  TestArraySize.cxx
  TestArrayUserTypes.cxx
  TestArrayVariants.cxx
#  TestConditionVariable.cxx
  TestCxxFeatures.cxx
  TestDataArray.cxx
  TestDataArrayComponentNames.cxx 
  TestGarbageCollector.cxx
#  TestInstantiator.cxx
  TestMath.cxx
  TestMinimalStandardRandomSequence.cxx
  TestNew.cxx
  TestObjectFactory.cxx
  TestObservers.cxx
  TestSmartPointer.cxx
  TestSortDataArray.cxx
  TestSparseArrayValidation.cxx
  TestUnicodeStringAPI.cxx
  TestUnicodeStringArrayAPI.cxx
  TestVariantComparison.cxx
  TestVectorOperators.cxx
  TestWeakPointer.cxx
  otherArrays.cxx
  otherByteSwap.cxx
  otherLookupTable.cxx
  otherLookupTableWithEnabling.cxx
  otherStringArray.cxx
  vtkTestNewVar.cxx
  
  EXTRA_INCLUDE vtkTestDriver.h
)

vtk_add_test_executable(${vtk-module}CxxTests ${Tests})

set(TestsToRun ${Tests})
list(REMOVE_ITEM TestsToRun ${vtk-module}CxxTests.cxx)

# Add all the executables
foreach (test ${TestsToRun})
  get_filename_component(TName ${test} NAME_WE)
  add_test(NAME ${TName} COMMAND ${vtk-module}CxxTests ${TName})
endforeach()
