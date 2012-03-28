# Make sure we find the required Tcl components.
if(VTK_WRAP_TCL)
  set(VTK_WRAP_TCL_FIND_LIBS 1)
  include(vtkWrapTcl)
  include(vtkWrapHierarchy)
endif()

function(vtk_add_tcl_wrapping module_name module_srcs)
  if(NOT VTK_WRAP_TCL_INIT_EXE)
    message(FATAL_ERROR "VTK must be built with Tcl wrapping turned on.")
  endif()
  # Need to add the Wrapping directory to the include directory
  include_directories(
    ${VTK_SOURCE_DIR}/Wrapping
    ${VTK_BINARY_DIR}/Wrapping
    ${TCL_INCLUDE_PATH})

  # FIXME: These must be here for now, should be fixed in the wrap hierarchy stuff
  set(KIT_HIERARCHY_FILE ${CMAKE_CURRENT_BINARY_DIR}/${module_name}Hierarchy.txt)
  string(REGEX REPLACE "^vtk" "" kit_name "${module_name}")
  set(KIT ${kit_name})

  # Set up the include directories for the wrapping
  set(VTK_WRAP_INCLUDE_DIRS
    ${vtkCommonCore_SOURCE_DIR}
    ${vtkCommonCore_BINARY_DIR}
    ${VTK_SOURCE_DIR}/Utilities
    ${VTK_BINARY_DIR}/Utilities
    ${${vtk-module}_SOURCE_DIR}
    )

# FIXME: Terrible temporary hack - add in the extra source file for CommonCore
  if(${module_name} STREQUAL "vtkCommonCore")
     set(extra_srcs ${VTK_SOURCE_DIR}/Wrapping/vtkTclUtil.cxx)
     set(extra_links vtksys)
  else()
    unset(extra_srcs)
    # This contains the vtkTclUtil class....
    set(extra_links vtkCommonCoreTCL)
  endif()

  # Figure out the dependent Tcl libraries for the module
  foreach(dep ${VTK_MODULE_${vtk-module}_DEPENDS})
    if(NOT "${vtk-module}" STREQUAL "${dep}")
      if(NOT VTK_MODULE_${dep}_EXCLUDE_FROM_WRAPPING)
        if("${dep}" STREQUAL "vtkRenderingContext2D")
          set(dep "vtkRenderingContextIID")
        endif()
        list(APPEND extra_links ${dep}TCL)
        list(APPEND VTK_WRAP_INCLUDE_DIRS ${${dep}_SOURCE_DIR})
      endif()
    endif()
  endforeach()

  # Tcl will not accept module names with numbers in.
  set(tcl_module ${module_name})
  if("${tcl_module}" STREQUAL "vtkRenderingContext2D")
    set(tcl_module "vtkRenderingContextIID")
  elseif("${tcl_module}" STREQUAL "vtkViewsContext2D")
    set(tcl_module "vtkViewsContextIID")
  endif()
  vtk_wrap_tcl3(${tcl_module}TCL Tcl_SRCS "${module_srcs}" "")
  add_library(${tcl_module}TCL ${Tcl_SRCS} ${extra_srcs})
  target_link_libraries(${tcl_module}TCL ${module_name}
    ${extra_links} ${VTK_TCL_LIBRARIES})
endfunction()
