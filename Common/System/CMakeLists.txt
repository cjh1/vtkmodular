
SET(Kit_SRCS
  vtkClientSocket.cxx
  vtkDirectory.cxx
  vtkServerSocket.cxx
  vtkSocket.cxx
  vtkSocketCollection.cxx
  vtkThreadMessager.cxx
  vtkTimerLog.cxx
  )

set_source_files_properties(
  vtkSocket
  ABSTRACT
)

if(NOT HAVE_SOCKETS)
  # Tell vtkSocket.cxx that there are no sockets on this platform.
  set_source_files_properties(vtkSocket.cxx PROPERTIES
    COMPILE_FLAGS -DVTK_SOCKET_FAKE_API)
endif()

if(WIN32 AND NOT BORLAND)
  set(KIT_LIBS ${KIT_LIBS} wsock32)
endif()

vtk_add_library(vtkCommonSystem ${Kit_SRCS})
