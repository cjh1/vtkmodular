# Make sure we find the required Python components.
if(VTK_WRAP_PYTHON)
  find_package(PythonLibs REQUIRED)
  include(vtkWrapPython)
  include(vtkWrapHierarchy)
endif()

function(vtk_add_python_wrapping module_name)
  if(NOT VTK_WRAP_PYTHON_INIT_EXE)
    message(FATAL_ERROR "VTK must be built with Python wrapping turned on.")
  endif()
  # Need to add the Wrapping/Python to the include directory
  include_directories(
    ${VTK_SOURCE_DIR}/Wrapping/PythonCore
    ${VTK_BINARY_DIR}/Wrapping/PythonCore
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
      if(NOT VTK_MODULE_${dep}_EXCLUDE_FROM_WRAPPING)
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
    if(${vtk-module} STREQUAL "vtkCommonCore")
      # vtkVariant has a special helper that is imported for it.
      file(APPEND "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/vtk/__init__.py"
        "from util.vtkVariant import *\n")
    endif()
  endif()
endfunction()
