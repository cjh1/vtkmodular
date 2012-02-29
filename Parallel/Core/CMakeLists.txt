set(Kit_SRCS
  vtkCommunicator.cxx
  vtkDummyCommunicator.cxx
  vtkDummyController.cxx
  vtkMultiProcessController.cxx
  vtkMultiProcessStream.cxx
#  vtkParallelFactory.cxx
  vtkProcess.cxx
  vtkProcessGroup.cxx
  vtkSocketCommunicator.cxx
  vtkSocketController.cxx
  vtkSubCommunicator.cxx
  vtkSubGroup.cxx
  )

# Generate "vtkSocketCommunicatorHash.h".
add_custom_command(
  OUTPUT ${VTK_BINARY_DIR}/Parallel/Core/vtkSocketCommunicatorHash.h
  DEPENDS ${VTK_SOURCE_DIR}/Parallel/Core/vtkSocketCommunicator.cxx
          vtkHashSource
  COMMAND vtkHashSource
    ${VTK_SOURCE_DIR}/Parallel/Core/vtkSocketCommunicator.cxx
    vtkSocketCommunicatorHash vtkSocketCommunicatorHash.h
  )

set(Kit_SRCS
  ${Kit_SRCS}
  ${VTK_BINARY_DIR}/Parallel/Core/vtkSocketCommunicatorHash.h
  )

set_source_files_properties(
  vtkMultiProcessStream
  WRAP_EXCLUDE
  )

set_source_files_properties(
  vtkMultiProcessStream
  ABSTRACT
  )

vtk_module_library(vtkParallelCore ${Kit_SRCS})
