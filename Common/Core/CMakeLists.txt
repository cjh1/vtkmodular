# Core configuration options.
IF("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
 SET(VTK_USE_64BIT_IDS_DEFAULT ON)
ELSE("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
 SET(VTK_USE_64BIT_IDS_DEFAULT OFF)
ENDIF("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
OPTION(VTK_USE_64BIT_IDS "Build VTK with 64 bit ids"
      ${VTK_USE_64BIT_IDS_DEFAULT})

OPTION(VTK_DEBUG_LEAKS "Build leak checking support into VTK." OFF)
MARK_AS_ADVANCED(VTK_DEBUG_LEAKS VTK_USE_64BIT_IDS)

set(vtkCommonCore_EXPORT_OPTIONS
  VTK_DEBUG_LEAKS
  VTK_USE_64BIT_IDS
  )

#-----------------------------------------------------------------------------

if(WIN32)
  if(NOT VTK_USE_X)
    set(VTK_OWP_ENCODED_C vtkWin32OutputWindowProcessEncoded.c)
    set_source_files_properties(${VTK_OWP_ENCODED_C} PROPERTIES WRAP_EXCLUDE 1)
  endif()
endif()

include_directories(
  ${VTK_SOURCE_DIR}/ThirdParty/utf8/source
  )

SET(Kit_SRCS
  vtkAbstractArray.cxx
  vtkAnimationCue.cxx
  vtkArrayCoordinates.cxx
  vtkArray.cxx
  vtkArrayExtents.cxx
  vtkArrayExtentsList.cxx
  vtkArrayIterator.cxx
  vtkArrayRange.cxx
  vtkArraySort.cxx
  vtkArrayWeights.cxx
  vtkBitArray.cxx
  vtkBitArrayIterator.cxx
  vtkBoxMuellerRandomSequence.cxx
  vtkBreakPoint.cxx
  vtkByteSwap.cxx
  vtkCallbackCommand.cxx
  vtkCharArray.cxx
  vtkCollection.cxx
  vtkCollectionIterator.cxx
  vtkCommand.cxx
  vtkCommonInformationKeyManager.cxx
  vtkConditionVariable.cxx
  vtkCriticalSection.cxx
  vtkDataArrayCollection.cxx
  vtkDataArrayCollectionIterator.cxx
  vtkDataArray.cxx
  vtkDataArraySelection.cxx
  vtkDebugLeaks.cxx
  vtkDebugLeaksManager.cxx
  vtkDoubleArray.cxx
  vtkDynamicLoader.cxx
  vtkEventForwarderCommand.cxx
  vtkFileOutputWindow.cxx
  vtkFloatArray.cxx
  vtkFloatingPointExceptions.cxx
  vtkGarbageCollector.cxx
  vtkGarbageCollectorManager.cxx
  vtkGaussianRandomSequence.cxx
  vtkIdListCollection.cxx
  vtkIdList.cxx
  vtkIdTypeArray.cxx
  vtkIndent.cxx
  vtkInformation.cxx
  vtkInformationDataObjectKey.cxx
  vtkInformationDoubleKey.cxx
  vtkInformationDoubleVectorKey.cxx
  vtkInformationIdTypeKey.cxx
  vtkInformationInformationKey.cxx
  vtkInformationInformationVectorKey.cxx
  vtkInformationIntegerKey.cxx
  vtkInformationIntegerPointerKey.cxx
  vtkInformationIntegerVectorKey.cxx
  vtkInformationIterator.cxx
  vtkInformationKey.cxx
  vtkInformationKeyVectorKey.cxx
  vtkInformationObjectBaseKey.cxx
  vtkInformationObjectBaseVectorKey.cxx
  vtkInformationRequestKey.cxx
  vtkInformationStringKey.cxx
  vtkInformationStringVectorKey.cxx
  vtkInformationUnsignedLongKey.cxx
  vtkInformationVector.cxx
  vtkInstantiator.cxx
  vtkIntArray.cxx
  vtkIOStream.cxx
  vtkLargeInteger.cxx
  vtkLongArray.cxx
  vtkLookupTable.cxx
  vtkMath.cxx
  vtkMinimalStandardRandomSequence.cxx
  vtkMultiThreader.cxx
  vtkMutexLock.cxx
  vtkObjectBase.cxx
  vtkObject.cxx
  vtkObjectFactoryCollection.cxx
  vtkObjectFactory.cxx
  vtkOldStyleCallbackCommand.cxx
  vtkOStreamWrapper.cxx
  vtkOStrStreamWrapper.cxx
  vtkOutputWindow.cxx
  vtkOverrideInformationCollection.cxx
  vtkOverrideInformation.cxx
  vtkPoints2D.cxx
  vtkPoints.cxx
  vtkPriorityQueue.cxx
  vtkRandomSequence.cxx
  vtkReferenceCount.cxx
  vtkScalarsToColors.cxx
  vtkShortArray.cxx
  vtkSignedCharArray.cxx
  vtkSmartPointerBase.cxx
  vtkSortDataArray.cxx
  vtkStdString.cxx
  vtkStringArray.cxx
  vtkTimePointUtility.cxx
  vtkTimeStamp.cxx
  vtkUnicodeStringArray.cxx
  vtkUnicodeString.cxx
  vtkUnsignedCharArray.cxx
  vtkUnsignedIntArray.cxx
  vtkUnsignedLongArray.cxx
  vtkUnsignedShortArray.cxx
  vtkVariantArray.cxx
  vtkVariant.cxx
  vtkVersion.cxx
  vtkVoidArray.cxx
  vtkWeakPointerBase.cxx
  vtkWindow.cxx
  vtkXMLFileOutputWindow.cxx
  vtkDenseArray.h
  vtkSparseArray.h
  vtkTypedArray.h
  vtkTypeTemplate.h
  vtkSystemIncludes.h
  vtkType.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkMathConfigure.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkConfigure.h
  )

if(vtkCommonDataModel_ENABLED)
  include_directories(${VTK_BINARY_DIR}/Common/DataModel)
  set_property(SOURCE vtkInformationDataObjectKey.cxx
    PROPERTY COMPILE_DEFINITIONS vtkCommonDataModel_ENABLED)
endif()

# __int64 seems to be platform specific, turning on if
if(HAVE_VTK_SIZEOF__INT64)
  list(APPEND Kit_SRCS
    vtkUnsigned__Int64Array.cxx
    vtk__Int64Array.cxx
    )
endif()

if(WIN32)
  list(APPEND Kit_SRCS
    vtkWin32OutputWindow.cxx
    vtkWin32OutputWindowProcessEncoded.c
    vtkWin32ProcessOutputWindow.cxx
    )
endif()

# Generate data for folding Unicode strings
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vtkUnicodeString.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/vtkUnicodeString.cmake @ONLY)

# Setup clean configuration of vtkConfigure.h and vtkToolkits.h.
MACRO(VTK_PREPARE_CMAKEDEFINE not invar outvar)
  IF(${not} ${invar})
    SET(${outvar} 1)
  ELSE(${not} ${invar})
    SET(${outvar})
  ENDIF(${not} ${invar})
ENDMACRO(VTK_PREPARE_CMAKEDEFINE)

VTK_PREPARE_CMAKEDEFINE("" CMAKE_WORDS_BIGENDIAN VTK_WORDS_BIGENDIAN)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_USE_PTHREADS VTK_USE_PTHREADS)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_USE_SPROC VTK_USE_SPROC)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_HP_PTHREADS VTK_HP_PTHREADS)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_USE_WIN32_THREADS VTK_USE_WIN32_THREADS)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_NO_ANSI_STRING_STREAM VTK_NO_ANSI_STRING_STREAM)
VTK_PREPARE_CMAKEDEFINE("" CMAKE_NO_STD_NAMESPACE VTK_NO_STD_NAMESPACE)
VTK_PREPARE_CMAKEDEFINE(NOT CMAKE_ANSI_FOR_SCOPE VTK_NO_FOR_SCOPE)
VTK_PREPARE_CMAKEDEFINE(NOT VTK_EXPLICIT_TEMPLATES
                  VTK_NO_EXPLICIT_TEMPLATE_INSTANTIATION)
VTK_PREPARE_CMAKEDEFINE(NOT VTK_COMPILER_HAS_FULL_SPECIALIZATION
                        VTK_NO_FULL_TEMPLATE_SPECIALIZATION)
VTK_PREPARE_CMAKEDEFINE("" OPENGL_LIBRARY VTK_USE_OPENGL_LIBRARY)

configure_file(vtkConfigure.h.in vtkConfigure.h @ONLY)
configure_file(vtkToolkits.h.in vtkToolkits.h @ONLY)

add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CaseFolding.txt
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vtkUnicodeString.cmake
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/vtkUnicodeString.cmake
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/vtkUnicodeCaseFoldData.h
  )

set_source_files_properties(
  vtkUnicodeString.cxx
  OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vtkUnicodeCaseFoldData.h
  )

if(CMAKE_COMPILER_IS_GNUCXX)
  set_source_files_properties(
   vtkPolynomialSolversUnivariate.cxx
   PROPERTIES
   COMPILE_FLAGS -O0
   )
endif()

if(VTK_TYPE_USE_LONG_LONG)
  list(APPEND Kit_SRCS
    vtkLongLongArray.cxx
    vtkUnsignedLongLongArray.cxx
    )
endif()

if(VTK_TYPE_USE___INT64)
  list(APPEND Kit_SRCS vtk__Int64Array.cxx)
  if(VTK_TYPE_CONVERT_UI64_TO_DOUBLE)
    list(APPEND Kit_SRCS vtkUnsigned__Int64Array.cxx)
  endif()
endif()

# Configure data arrays for platform-independent fixed-size types.
# Match the type selection here to that in vtkType.h.
IF(VTK_TYPE_CHAR_IS_SIGNED)
  SET(VTK_TYPE_NATIVE_Int8 Char)
ELSE(VTK_TYPE_CHAR_IS_SIGNED)
  SET(VTK_TYPE_NATIVE_Int8 SignedChar)
ENDIF(VTK_TYPE_CHAR_IS_SIGNED)
SET(VTK_TYPE_NATIVE_Int16 Short)
SET(VTK_TYPE_NATIVE_Int32 Int)
SET(VTK_TYPE_NATIVE_UInt8 UnsignedChar)
SET(VTK_TYPE_NATIVE_UInt16 UnsignedShort)
SET(VTK_TYPE_NATIVE_UInt32 UnsignedInt)

IF(VTK_SIZEOF_LONG_LONG MATCHES "^8$")
  SET(VTK_TYPE_NATIVE_Int64 LongLong)
  SET(VTK_TYPE_NATIVE_UInt64 UnsignedLongLong)
ELSE(VTK_SIZEOF_LONG_LONG MATCHES "^8$")
  IF(VTK_SIZEOF_LONG MATCHES "^8$")
    SET(VTK_TYPE_NATIVE_Int64 Long)
    SET(VTK_TYPE_NATIVE_UInt64 UnsignedLong)
  ELSE(VTK_SIZEOF_LONG MATCHES "^8$")
    IF(VTK_SIZEOF___INT64 MATCHES "^8$")
      SET(VTK_TYPE_NATIVE_Int64 __Int64)
      IF(VTK_TYPE_CONVERT_UI64_TO_DOUBLE)
        SET(VTK_TYPE_NATIVE_UInt64 Unsigned__Int64)
      ENDIF(VTK_TYPE_CONVERT_UI64_TO_DOUBLE)
    ENDIF(VTK_SIZEOF___INT64 MATCHES "^8$")
  ENDIF(VTK_SIZEOF_LONG MATCHES "^8$")
ENDIF(VTK_SIZEOF_LONG_LONG MATCHES "^8$")
SET(VTK_TYPE_NATIVE_Float32 Float)
SET(VTK_TYPE_NATIVE_Float64 Double)
FOREACH(t Int8 Int16 Int32 Int64 UInt8 UInt16 UInt32 UInt64 Float32 Float64)
  SET(VTK_TYPE_NAME ${t})
  SET(VTK_TYPE_NATIVE ${VTK_TYPE_NATIVE_${t}})
  IF(VTK_TYPE_NATIVE)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/vtkTypedArray.h.in
                   ${CMAKE_CURRENT_BINARY_DIR}/vtkType${t}Array.h
                   @ONLY IMMEDIATE)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/vtkTypedArray.cxx.in
                   ${CMAKE_CURRENT_BINARY_DIR}/vtkType${t}Array.cxx
                   @ONLY IMMEDIATE)
    SET(Kit_SRCS ${Kit_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/vtkType${t}Array.cxx)
  ENDIF(VTK_TYPE_NATIVE)
ENDFOREACH(t)

# Figure out if isnan and isinf functions are present.
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckIncludeFile)

if(NOT HAVE_FLOAT_H)
  CHECK_INCLUDE_FILE("float.h" HAVE_FLOAT_H)
endif()

if(HAVE_FLOAT_H)
  CHECK_SYMBOL_EXISTS(isnan "float.h" VTK_HAS_ISNAN)
  if(NOT VTK_HAS_ISNAN)
    CHECK_SYMBOL_EXISTS(_isnan "float.h" VTK_HAS__ISNAN)
  endif()
  CHECK_SYMBOL_EXISTS(isinf "float.h" VTK_HAS_ISINF)
  if(NOT VTK_HAS_ISINF)
    CHECK_FUNCTION_EXISTS(_isinf "float.h" VTK_HAS__ISINF)
  endif()
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/vtkMathConfigure.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/vtkMathConfigure.h
  )

# Figure out if feenableexcept and fedisableexcept functions are present
CHECK_INCLUDE_FILE("fenv.h" HAVE_FENV_H)
IF (HAVE_FENV_H)
  SET(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)
  IF(UNIX)
    SET(CMAKE_REQUIRED_LIBRARIES m)
  ENDIF(UNIX)
  CHECK_SYMBOL_EXISTS(feenableexcept "fenv.h" VTK_HAS_FEENABLEEXCEPT)
  SET(CMAKE_REQUIRED_LIBRARIES)
ENDIF (HAVE_FENV_H)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/vtkFloatingPointExceptionsConfigure.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/vtkFloatingPointExceptionsConfigure.h
  )

# header files that have constants that can be wrapped
set_source_files_properties(
  vtkSystemIncludes.h
  vtkType.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkMathConfigure.h
  ${CMAKE_CURRENT_BINARY_DIR}/vtkConfigure.h
  PROPERTIES WRAP_HEADER 1
  )

set_source_files_properties(
  # vtkObjectBase is marked ABSTRACT so that instantiators are happy.
  vtkAbstractArray
  vtkArrayIterator
  vtkArrayIteratorTemplate
  vtkArray
  vtkCallbackCommand
  vtkCommand
  vtkCommonInformationKeyManager
  vtkDataArray
  vtkEventForwarderCommand
  vtkFloatingPointExceptions
  vtkFunctionSet
  vtkGaussianRandomSequence
  vtkInformationDataObjectKey
  vtkInformationDoubleKey
  vtkInformationDoubleVectorKey
  vtkInformationIdTypeKey
  vtkInformationInformationKey
  vtkInformationInformationVectorKey
  vtkInformationIntegerKey
  vtkInformationIntegerPointerKey
  vtkInformationIntegerVectorKey
  vtkInformationKey
  vtkInformationKeyVectorKey
  vtkInformationObjectBaseKey
  vtkInformationObjectBaseVectorKey
  vtkInformationQuadratureSchemeDefinitionVectorKey
  vtkInformationRequestKey
  vtkInformationStringKey
  vtkInformationStringVectorKey
  vtkInformationUnsignedLongKey
  vtkObjectBase
  vtkObjectFactory
  vtkOldStyleCallbackCommand
  vtkOverrideInformation
  vtkOverrideInformationCollection
  vtkRandomSequence
  vtkScalarsToColors
  vtkWindow
  ABSTRACT
  )

set_source_files_properties(
  vtkArrayCoordinates.cxx
  vtkArrayExtents.cxx
  vtkArrayExtentsList.cxx
  vtkArrayIteratorTemplate.txx
  vtkArrayRange.cxx
  vtkArraySort.cxx
  vtkArrayWeights.cxx
  vtkBoundingBox.cxx
  vtkBreakPoint.cxx
  vtkCallbackCommand.cxx
  vtkCommonInformationKeyManager.cxx
  vtkDebugLeaksManager.cxx
  vtkEventForwarderCommand.cxx
  vtkFloatingPointExceptions
  vtkGarbageCollectorManager.cxx
  vtkIOStream.cxx
  vtkIndent.cxx
  vtkLargeInteger.cxx
  vtkOStrStreamWrapper.cxx
  vtkOStreamWrapper.cxx
  vtkOldStyleCallbackCommand.cxx
  vtkSmartPointerBase.cxx
  vtkStdString.cxx
  vtkTimeStamp.cxx
  vtkVariant.cxx
  vtkWeakPointerBase.cxx
  vtkUnicodeString.cxx
  WRAP_EXCLUDE
  )

set_source_files_properties(
  vtkDenseArray.h
  vtkSparseArray.h
  vtkTypedArray.h
  vtkTypeTemplate.h
  HEADER_FILE_ONLY
  )

set_source_files_properties(
  vtkArrayCoordinates.cxx
  vtkArrayExtents.cxx
  vtkArrayExtentsList.cxx
  vtkArrayRange.cxx
  vtkArraySort.cxx
  vtkArrayWeights.cxx
  vtkDenseArray.h
  vtkSparseArray.h
  vtkTypedArray.h
  vtkTypeTemplate.h
  vtkTimeStamp.cxx
  vtkVariant.cxx
  PROPERTIES WRAP_SPECIAL 1
)

# Activate code in "vtkVariant.cxx".  See the comment in the source.
set_source_files_properties(vtkVariant.cxx PROPERTIES
  COMPILE_FLAGS -DVTK_VARIANT_IMPL)

if(WIN32)
  if(NOT VTK_USE_X)
    list(APPEND Kit_SRCS vtkWin32OutputWindow.cxx
      vtkWin32ProcessOutputWindow.cxx)
    set(Kit_EXTRA_SRCS ${Kit_EXTRA_SRCS} vtkWin32OutputWindowProcessEncoded.c)
    set_source_files_properties(vtkWin32OutputWindowProcessEncoded.c
      PROPERTIES WRAP_EXCLUDE 1)
  endif()
endif()

# Need nsl to resolve gethostbyname on SunOS-5.8
# and socket also
if(CMAKE_SYSTEM MATCHES "SunOS.*")
  set(KIT_LIBS ${KIT_LIBS} socket nsl)
endif()

vtk_module_library(vtkCommonCore ${Kit_SRCS})

target_link_libraries(vtkCommonCore ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(vtkCommonCore PROPERTIES LINK_INTERFACE_LIBRARIES "")

IF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
  # MinGW fails to dllexport the explicit instantiations of
  # vtkDataArrayTemplate, so we must export all symbols.
  GET_TARGET_PROPERTY(VTK_COMMON_LINK_FLAGS vtkCommon LINK_FLAGS)
  IF(VTK_COMMON_LINK_FLAGS)
    SET(VTK_COMMON_LINK_FLAGS "${VTK_COMMON_LINK_FLAGS} ")
  ELSE(VTK_COMMON_LINK_FLAGS)
    SET(VTK_COMMON_LINK_FLAGS)
  ENDIF(VTK_COMMON_LINK_FLAGS)
  SET_TARGET_PROPERTIES(vtkCommon PROPERTIES
    LINK_FLAGS "${VTK_COMMON_LINK_FLAGS}-Wl,--export-all-symbols")
ENDIF(CMAKE_COMPILER_IS_GNUCXX AND MINGW)
