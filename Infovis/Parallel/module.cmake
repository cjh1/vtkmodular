if(VTK_USE_MPI)
  set(_EXCLUDE_FROM_ALL)
else()
  set(_EXCLUDE_FROM_ALL EXCLUDE_FROM_ALL)
endif()
vtk_module(vtkInfovisParallel
  DEPENDS
    vtkInfovisCore
    vtkCommonExecutionModel
  ${_EXCLUDE_FROM_ALL}
  DEFAULT OFF)
