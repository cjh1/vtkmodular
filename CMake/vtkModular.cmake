# Create vtk_* functions to add libraries, executables and modules. Add LABELS
# automatically. Depends on the CMake variable vtk-module being set to the
# "current" module when add_* is called.
function(verify_vtk_module_is_set)
  if("" STREQUAL "${vtk-module}")
    message(FATAL_ERROR "CMake variable vtk-module is not set")
  endif()
endfunction()

function(vtk_add_executable)
  add_executable(${ARGN})
  verify_vtk_module_is_set()
  set_property(TARGET ${ARGV0} PROPERTY LABELS ${vtk-module})
  set_property(GLOBAL APPEND PROPERTY ${vtk-module}_EXECUTABLE_TARGETS ${ARGV0})
endfunction()

function(vtk_add_library)
  add_library(${ARGN})
  verify_vtk_module_is_set()

  if(${vtk-module}_IS_TPL)
    return()
  endif()

  include_directories(${CMAKE_CURRENT_BINARY_DIR})
  foreach(dep IN LISTS VTK_MODULE_${vtk-module}_DEPENDS)
    include_directories(${${dep}_SOURCE_DIR} ${${dep}_BINARY_DIR})
  endforeach()

  set_property(TARGET ${ARGV0} PROPERTY LABELS ${vtk-module})
  set_property(GLOBAL APPEND PROPERTY ${vtk-module}_LIBRARY_TARGETS ${ARGV0})
  set_property(GLOBAL APPEND PROPERTY VTK_TARGETS ${ARGV0})

  # Generate the export macro header for symbol visibility/Windows DLL declspec
  include(GenerateExportHeader)
  generate_export_header(${vtk-module} EXPORT_FILE_NAME ${vtk-module}Export.h)
  add_compiler_export_flags(my_abi_flags)
  set_property(TARGET ${vtk-module} APPEND
    PROPERTY COMPILE_FLAGS "${VTK_ABI_CXX_FLAGS}")

  # Link to the libraries specified in dependencies
  unset(_link_deps)
  foreach(link_dep IN LISTS VTK_MODULE_${vtk-module}_LINK_DEPENDS)
    if(${link_dep}_IS_TPL AND DEFINED ${link_dep}_TPL_LIBRARIES)
      list(APPEND _link_deps ${${link_dep}_TPL_LIBRARIES})
    else()
      list(APPEND _link_deps ${link_dep})
    endif()
  endforeach()
  target_link_libraries(${vtk-module} ${_link_deps})
  if(DEFINED VTK_MODULE_${vtk-module}_LINK_INTERFACE_LIBRARIES)
    set_target_properties(${vtk-module} PROPERTIES
      LINK_INTERFACE_LIBRARIES "${VTK_MODULE_${vtk-module}_LINK_INTERFACE_LIBRARIES}")
  endif()

  if(VTK_WRAP_PYTHON AND NOT ${vtk-module}_IS_TPL)
    vtk_add_wrapping("${vtk-module}")
  endif()
endfunction()

function(vtk_add_test)
  add_test(${ARGN})
  verify_vtk_module_is_set()
  if("NAME" STREQUAL "${ARGV0}")
    set(_imm_test ${ARGV1})
  else()
    set(_imm_test ${ARGV0})
  endif()
  set_property(TEST ${_imm_test} PROPERTY LABELS ${vtk-module})
  set_property(GLOBAL APPEND PROPERTY ${vtk-module}_TESTS ${_imm_test})
endfunction()

# Handle Python wrapping
if(VTK_WRAP_PYTHON)
  find_package(PythonLibs REQUIRED)
  include(vtkMakeInstantiator)
  include(vtkWrapPython)
  include(vtkWrapHierarchy)
endif()

function(vtk_add_wrapping module_name)
  if(NOT VTK_WRAP_PYTHON_INIT_EXE)
    message(FATAL_ERROR "VTK must be built with Python wrapping turned on.")
  endif()
  # Need to add the Wrapping/Python to the include directory
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${VTK_SOURCE_DIR}/Wrapping/PythonCore
    ${VTK_SOURCE_DIR}/Wrapping
    ${VTK_BINARY_DIR}/Wrapping
    ${PYTHON_INCLUDE_DIRS})

  get_target_property(module_srcs ${module_name} SOURCES)

  # FIXME: These must be here for now, should be fixed in the wrap hierarchy stuff
  set(KIT_HIERARCHY_FILE ${CMAKE_CURRENT_BINARY_DIR}/${module_name}Hierarchy.txt)
  string(REGEX REPLACE "^vtk" "" kit_name "${module_name}")
  set(KIT ${kit_name})

  # FIXME: Terrible temporary hack - add in the extra source file for CommonCore
  if(${module_name} STREQUAL "vtkCommonCore")
    set(extra_srcs vtkPythonCommand.cxx)
    unset(extra_links)
  else()
    unset(extra_srcs)
    # This contains the PyVTKClass....
    set(extra_links vtkCommonCorePythonD)
  endif()

  # Set up the include directories for the wrapping
  set(VTK_WRAP_INCLUDE_DIRS
    ${vtkCommonCore_SOURCE_DIR}
    ${vtkCommonCore_BINARY_DIR}
    ${VTK_SOURCE_DIR}/Utilities
    ${VTK_BINARY_DIR}/Utilities
    ${${vtk-module}_SOURCE_DIR}
    )

  # Figure out the dependent PythonD libraries for the module
  foreach(dep ${VTK_MODULE_${vtk-module}_DEPENDS})
    if(NOT "${vtk-module}" STREQUAL "${dep}")
      if(NOT ${dep}_IS_TPL)
        list(APPEND extra_links ${dep}PythonD)
        list(APPEND VTK_WRAP_INCLUDE_DIRS ${${dep}_SOURCE_DIR})
      endif()
    endif()
  endforeach()

  vtk_wrap_hierarchy(${module_name}Hierarchy ${CMAKE_CURRENT_BINARY_DIR}
    "${module_srcs}")

  vtk_wrap_python3(${module_name}Python Python_SRCS "${module_srcs}")
  add_library(${module_name}PythonD ${Python_SRCS} ${extra_srcs})
  target_link_libraries(${module_name}PythonD ${module_name}
    vtkWrappingPythonCore ${extra_links} ${VTK_PYTHON_LIBRARIES})
  python_add_module(${module_name}Python ${module_name}PythonInit.cxx)
  if(PYTHON_ENABLE_MODULE_${module_name}Python)
    set(VTK_PYTHON_MODULES ${VTK_PYTHON_MODULES} ${module_name}
      CACHE INTERNAL "Python modules for VTK")
    target_link_libraries(${module_name}Python ${module_name}PythonD)
    # Then write the Python code to import the module
    file(WRITE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/vtk/${kit_name}.py"
      "from ${module_name}Python import *\n")
    if(NOT EXISTS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/vtk/__init__.py")
      file(WRITE "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/vtk/__init__.py"
        "import os\nimport sys\n\nfrom ${vtk-module}Python import *\n")
    else()
      file(APPEND "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/vtk/__init__.py"
        "from ${vtk-module}Python import *\n")
    endif()
  endif()
endfunction()

# Follow dependencies.
macro(vtk_module_enable vtk-module _needed_by)
  if(NOT Module_${vtk-module})
    if(NOT ${vtk-module}_TESTED_BY OR
      NOT "x${_needed_by}" STREQUAL "x${${vtk-module}_TESTED_BY}")
      list(APPEND VTK_MODULE_${vtk-module}_NEEDED_BY ${_needed_by})
    endif()
  endif()
  if(NOT ${vtk-module}_ENABLED)
    set(${vtk-module}_ENABLED 1)
    foreach(dep IN LISTS VTK_MODULE_${vtk-module}_DEPENDS)
      vtk_module_enable(${dep} ${vtk-module})
    endforeach()
    foreach(dep IN LISTS VTK_MODULE_${vtk-module}_COMPILE_DEPENDS)
      vtk_module_enable(${dep} ${vtk-module})
    endforeach()
    if(${vtk-module}_TESTED_BY)
      vtk_module_enable(${${vtk-module}_TESTED_BY} "")
    endif()
  endif()
endmacro()

macro(vtk_module _name)
  set(vtk-module ${_name})
  set(vtk-module-test ${_name}-Test)
  set(_doing "")
  set(VTK_MODULE_${vtk-module}_DEPENDS "")
  set(VTK_MODULE_${vtk-module}_COMPILE_DEPENDS "")
  set(VTK_MODULE_${vtk-module-test}_DEPENDS "${vtk-module}")
  set(VTK_MODULE_${vtk-module}_DEFAULT OFF)
  set(my_list "${ARGN}")
  foreach(arg IN LISTS my_list)
    if("${arg}" MATCHES "^(DEPENDS|COMPILE_DEPENDS|TEST_DEPENDS|DEFAULT|LINK_INTERFACE_LIBRARIES)$")
      set(_doing "${arg}")
    elseif("${_doing}" MATCHES "^DEPENDS$")
      list(APPEND VTK_MODULE_${vtk-module}_DEPENDS "${arg}")
    elseif("${_doing}" MATCHES "^COMPILE_DEPENDS$")
      list(APPEND VTK_MODULE_${vtk-module}_COMPILE_DEPENDS "${arg}")
    elseif("${_doing}" MATCHES "^TEST_DEPENDS$")
      list(APPEND VTK_MODULE_${vtk-module-test}_DEPENDS "${arg}")
    elseif("${_doing}" MATCHES "^DEFAULT")
      set(VTK_MODULE_${vtk-module}_DEFAULT "${arg}")
    elseif("${_doing}" MATCHES "^LINK_INTERFACE_LIBRARIES")
      message("LINK_INTERFACE_LIBRARIES for ${vtk-module}: '${arg}'")
      set(VTK_MODULE_${vtk-module}_LINK_INTERFACE_LIBRARIES "${arg}")
    else()
      set(_doing "")
      message(AUTHOR_WARNING "Unknown argument [${arg}]")
    endif()
  endforeach()
  list(SORT VTK_MODULE_${vtk-module}_DEPENDS) # Deterministic order.
  set(VTK_MODULE_${vtk-module}_LINK_DEPENDS ${VTK_MODULE_${vtk-module}_DEPENDS})
  list(APPEND VTK_MODULE_${vtk-module}_DEPENDS
    ${VTK_MODULE_${vtk-module}_COMPILE_DEPENDS})
  list(SORT VTK_MODULE_${vtk-module}_DEPENDS) # Deterministic order.
  list(SORT VTK_MODULE_${vtk-module-test}_DEPENDS) # Deterministic order.
endmacro()

macro(init_module_vars)
  verify_vtk_module_is_set()
  set(${vtk-module}-targets VTKTargets)
  set(${vtk-module}-targets-install "${VTK_INSTALL_PACKAGE_DIR}/ITKTargets.cmake")
  set(${vtk-module}-targets-build "${VTK_BINARY_DIR}/VTKTargets.cmake")
  set(${vtk-module}_DIR "${${vtk-module}_BINARY_DIR}") # find_package

  # Start each module with these properties empty. Calls to add_executable,
  # add_library and add_test accumulate names into these properties:
  set_property(GLOBAL PROPERTY ${vtk-module}_EXECUTABLE_TARGETS "")
  set_property(GLOBAL PROPERTY ${vtk-module}_LIBRARY_TARGETS "")
  set_property(GLOBAL PROPERTY ${vtk-module}_TESTS "")
endmacro()

function(add_module_target)
  verify_vtk_module_is_set()
  add_custom_target(${vtk-module}-all)
  get_property(_imm_exe_targets GLOBAL PROPERTY ${vtk-module}_EXECUTABLE_TARGETS)
  get_property(_imm_lib_targets GLOBAL PROPERTY ${vtk-module}_LIBRARY_TARGETS)
  set(_imm_dep_targets ${_imm_exe_targets} ${_imm_lib_targets})
  if(_imm_dep_targets)
    add_dependencies(${vtk-module}-all ${_imm_dep_targets})
  endif()
endfunction()
