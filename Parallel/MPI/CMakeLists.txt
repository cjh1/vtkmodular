include (FindMPI)
include_directories(${MPI_INCLUDE_PATH})

set(Kit_SRCS
  vtkMPICommunicator.cxx
  vtkMPIController.cxx
  # vtkMPIEventLog.cxx # Deprecated
  vtkMPI.h
  )

set_source_files_properties(
  vtkMPI.h
  HEADER_FILE_ONLY
  )

set_source_files_properties(
  vtkMPI.h
  WRAP_EXCLUDE
  )

# Needed for mpich 2
add_definitions("-DMPICH_IGNORE_CXX_SEEK")

vtk_module_library(vtkParallelMPI ${Kit_SRCS})
target_link_libraries(vtkParallelMPI ${MPI_LIBRARY} ${MPI_EXTRA_LIBRARY})
