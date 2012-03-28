#
# a cmake implementation of the Wrap Python command
#
macro(VTK_WRAP_PYTHON2 TARGET SOURCE_LIST_NAME)
  # convert to the WRAP3 signature
  vtk_wrap_python3(${TARGET} ${SOURCE_LIST_NAME} "${ARGN}")
endmacro()

macro(VTK_WRAP_PYTHON3 TARGET SRC_LIST_NAME SOURCES)
  if(NOT VTK_WRAP_PYTHON_INIT_EXE)
   message(SEND_ERROR
      "VTK_WRAP_PYTHON_INIT_EXE not specified when calling VTK_WRAP_PYTHON3")
  endif()
  if(NOT VTK_WRAP_PYTHON_EXE)
    message(SEND_ERROR
      "VTK_WRAP_PYTHON_EXE not specified when calling VTK_WRAP_PYTHON3")
  endif()

  # The shell into which nmake.exe executes the custom command has some issues
  # with mixing quoted and unquoted arguments :( Let's help.
  if(CMAKE_GENERATOR MATCHES "NMake Makefiles")
    set(verbatim "")
    set(quote "\"")
  else()
    set(verbatim "VERBATIM")
    set(quote "")
  endif()

  # Initialize the custom target counter.
  if(VTK_WRAP_PYTHON_NEED_CUSTOM_TARGETS)
    set(VTK_WRAP_PYTHON_CUSTOM_COUNT "")
    set(VTK_WRAP_PYTHON_CUSTOM_NAME ${TARGET})
    set(VTK_WRAP_PYTHON_CUSTOM_LIST)
  endif()

  # start writing the input file for the init file
  set(VTK_WRAPPER_INIT_DATA "${TARGET}")

  get_directory_property(TMP_DEF_LIST DEFINITION COMPILE_DEFINITIONS)
  set(TMP_DEFINITIONS)
  foreach(TMP_DEF ${TMP_DEF_LIST})
    set(TMP_DEFINITIONS ${TMP_DEFINITIONS} -D "${quote}${TMP_DEF}${quote}")
  endforeach()

  if(VTK_WRAP_INCLUDE_DIRS)
    set(TMP_INCLUDE_DIRS ${VTK_WRAP_INCLUDE_DIRS})
  else()
    set(TMP_INCLUDE_DIRS ${VTK_INCLUDE_DIRS})
  endif()
  set(TMP_INCLUDE)
  foreach(INCLUDE_DIR ${TMP_INCLUDE_DIRS})
    set(TMP_INCLUDE ${TMP_INCLUDE} -I "${quote}${INCLUDE_DIR}${quote}")
  endforeach()

  if(VTK_WRAP_HINTS)
    set(TMP_HINTS "--hints" "${quote}${VTK_WRAP_HINTS}${quote}")
  else()
    unset(TMP_HINTS)
  endif()

  if(KIT_HIERARCHY_FILE)
    set(TMP_HIERARCHY "--types" "${quote}${KIT_HIERARCHY_FILE}${quote}")
  else(K)
    unset(TMP_HIERARCHY)
  endif()

  # For each class
  foreach(FILE ${SOURCES})
    # should we wrap the file?
    get_source_file_property(TMP_WRAP_EXCLUDE ${FILE} WRAP_EXCLUDE)
    get_source_file_property(TMP_WRAP_SPECIAL ${FILE} WRAP_SPECIAL)

    # if we should wrap it
    if(TMP_WRAP_SPECIAL OR NOT TMP_WRAP_EXCLUDE)

      # what is the filename without the extension
      get_filename_component(TMP_FILENAME ${FILE} NAME_WE)

      # the input file might be full path so handle that
      get_filename_component(TMP_FILEPATH ${FILE} PATH)

      # compute the input filename
      if(TMP_FILEPATH)
        set(TMP_INPUT ${TMP_FILEPATH}/${TMP_FILENAME}.h)
      else()
        set(TMP_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/${TMP_FILENAME}.h)
      endif()

      # is it abstract?
      get_source_file_property(TMP_ABSTRACT ${FILE} ABSTRACT)
      if(TMP_ABSTRACT)
        set(TMP_CONCRETE "--abstract")
      else()
        set(TMP_CONCRETE "--concrete")
      endif()

      # is it special?
      if(TMP_WRAP_SPECIAL)
        set(TMP_SPECIAL "--special")
      else()
        set(TMP_SPECIAL "--vtkobject")
      endif()

      # add the info to the init file
      set(VTK_WRAPPER_INIT_DATA
        "${VTK_WRAPPER_INIT_DATA}\n${TMP_FILENAME}")

      # new source file is namePython.cxx, add to resulting list
      set(${SRC_LIST_NAME} ${${SRC_LIST_NAME}}
        ${TMP_FILENAME}Python.cxx)

      # add custom command to output
      add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TMP_FILENAME}Python.cxx
        DEPENDS ${VTK_WRAP_PYTHON_EXE} ${VTK_WRAP_HINTS} ${TMP_INPUT}
          ${KIT_HIERARCHY_FILE}
        COMMAND ${VTK_WRAP_PYTHON_EXE}
          ARGS
          ${TMP_CONCRETE}
          ${TMP_SPECIAL}
          ${TMP_HINTS}
          ${TMP_HIERARCHY}
          ${TMP_DEFINITIONS}
          ${TMP_INCLUDE}
          "${quote}${TMP_INPUT}${quote}"
          "${quote}${CMAKE_CURRENT_BINARY_DIR}/${TMP_FILENAME}Python.cxx${quote}"
        COMMENT "Python Wrapping - generating ${TMP_FILENAME}Python.cxx"
          ${verbatim}
        )

      # Add this output to a custom target if needed.
      if(VTK_WRAP_PYTHON_NEED_CUSTOM_TARGETS)
        set(VTK_WRAP_PYTHON_CUSTOM_LIST ${VTK_WRAP_PYTHON_CUSTOM_LIST}
          ${CMAKE_CURRENT_BINARY_DIR}/${TMP_FILENAME}Python.cxx)
        set(VTK_WRAP_PYTHON_CUSTOM_COUNT ${VTK_WRAP_PYTHON_CUSTOM_COUNT}x)
        if(VTK_WRAP_PYTHON_CUSTOM_COUNT MATCHES "^${VTK_WRAP_PYTHON_CUSTOM_LIMIT}$")
          set(VTK_WRAP_PYTHON_CUSTOM_NAME ${VTK_WRAP_PYTHON_CUSTOM_NAME}Hack)
          add_custom_target(${VTK_WRAP_PYTHON_CUSTOM_NAME}
            DEPENDS ${VTK_WRAP_PYTHON_CUSTOM_LIST})
          set(KIT_PYTHON_DEPS ${VTK_WRAP_PYTHON_CUSTOM_NAME})
          set(VTK_WRAP_PYTHON_CUSTOM_LIST)
          set(VTK_WRAP_PYTHON_CUSTOM_COUNT)
        endif()
      endif()
    endif()
  endforeach()

  # finish the data file for the init file
  configure_file(
    ${VTK_CMAKE_DIR}/vtkWrapperInit.data.in
    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Init.data
    COPY_ONLY
    IMMEDIATE
    )

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Init.cxx
    DEPENDS ${VTK_WRAP_PYTHON_INIT_EXE}
      ${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Init.data
    COMMAND ${VTK_WRAP_PYTHON_INIT_EXE}
    ARGS
      "${quote}${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Init.data${quote}"
      "${quote}${CMAKE_CURRENT_BINARY_DIR}/${TARGET}Init.cxx${quote}"
    COMMENT "Python Wrapping - generating ${TARGET}Init.cxx"
      ${verbatim}
    )

  # Create the Init File
  set(${SRC_LIST_NAME} ${${SRC_LIST_NAME}} ${TARGET}Init.cxx)

endmacro(VTK_WRAP_PYTHON3)

if(VTK_WRAP_PYTHON_FIND_LIBS)
  get_filename_component(_CURRENT_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
  find_package(PythonLibs)

  # Use separate debug/optimized libraries if they are different.
  if(PYTHON_DEBUG_LIBRARY)
    if("${PYTHON_DEBUG_LIBRARY}" STREQUAL "${PYTHON_LIBRARY}")
      set(VTK_PYTHON_LIBRARIES ${PYTHON_LIBRARY})
    else()
      set(VTK_PYTHON_LIBRARIES
        optimized ${PYTHON_LIBRARY}
        debug ${PYTHON_DEBUG_LIBRARY})
    endif()
    set(VTK_WINDOWS_PYTHON_DEBUGGABLE 0)
    if(WIN32)
      if(PYTHON_DEBUG_LIBRARY MATCHES "_d")
        set(VTK_WINDOWS_PYTHON_DEBUGGABLE 1)
      endif()
    endif()
  else()
    set(VTK_PYTHON_LIBRARIES ${PYTHON_LIBRARY})
  endif()

  # Some python installations on UNIX need to link to extra libraries
  # such as zlib (-lz).  It is hard to automatically detect the needed
  # libraries so instead just give the user an easy way to specify
  # the libraries.  This should be needed only rarely.  It should
  # also be moved to the CMake FindPython.cmake module at some point.
  if(UNIX)
    if(NOT DEFINED PYTHON_EXTRA_LIBS)
      set(PYTHON_EXTRA_LIBS "" CACHE STRING
        "Extra libraries to link when linking to python (such as \"z\" for zlib).  Separate multiple libraries with semicolons.")
      mark_as_advanced(PYTHON_EXTRA_LIBS)
    endif()
  endif()

  # Include any extra libraries for python.
  set(VTK_PYTHON_LIBRARIES ${VTK_PYTHON_LIBRARIES} ${PYTHON_EXTRA_LIBS})
endif()
