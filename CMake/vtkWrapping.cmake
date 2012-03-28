# This file ensures that any module that should be wrapped has the
# vtkWrapHierarchy command executed on it, and also dispatches to the language
# specific wrapping for each module.

# First, ensure we include the correct CMake code so that we can wrap.
if(VTK_WRAP_PYTHON)
  include(vtkPythonWrapping)
endif()
if(VTK_WRAP_TCL)
  include(vtkTclWrapping)
endif()
if(VTK_WRAP_JAVA)
  include(vtkJavaWrapping)
endif()

include(vtkWrapHierarchy)

# This is the main function, always called from the vtk_module_library function
# when a new module library is added.
function(vtk_add_wrapping module_name module_srcs)
  if(NOT VTK_MODULE_${module_name}_EXCLUDE_FROM_WRAPPING)
    set(_wrap_module FALSE)
    if(VTK_WRAP_PYTHON)
      set(_wrap_module TRUE)
      set_property(GLOBAL APPEND PROPERTY VTK_PYTHON_WRAPPED ${module_name})
    endif()
    if(VTK_WRAP_TCL)
      set(_wrap_module TRUE)
      set_property(GLOBAL APPEND PROPERTY VTK_TCL_WRAPPED ${module_name})
    endif()
    if(VTK_WRAP_JAVA)
      set(_wrap_module TRUE)
      set_property(GLOBAL APPEND PROPERTY VTK_JAVA_WRAPPED ${module_name})
    endif()
    if(_wrap_module)
      # The module is wrapped by at least one language - invoke wrap hierarchy.
      # Set up the include directories for the wrapping
      set(VTK_WRAP_INCLUDE_DIRS
        ${vtkCommonCore_SOURCE_DIR}
        ${vtkCommonCore_BINARY_DIR}
        ${VTK_SOURCE_DIR}/Utilities
        ${VTK_BINARY_DIR}/Utilities
        ${${vtk-module}_SOURCE_DIR}
        )
    
      vtk_wrap_hierarchy(${module_name}Hierarchy ${CMAKE_CURRENT_BINARY_DIR}
        "${module_srcs}")

      # Now to wrap the languages that are on.
      if(VTK_WRAP_PYTHON)
        vtk_add_python_wrapping(${module_name} "${module_srcs}")
      endif()
      if(VTK_WRAP_TCL)
        vtk_add_tcl_wrapping(${module_name} "${module_srcs}")
      endif()
      if(VTK_WRAP_JAVA)
        vtk_add_java_wrapping(${module_name} "${module_srcs}")
      endif()
    endif()
  endif()
endfunction()
