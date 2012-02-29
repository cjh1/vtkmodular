set(Kit_SRCS
  vtkVideoSource.cxx
)

IF (WIN32)
  IF (VTK_VFW_SUPPORTS_CAPTURE)
    SET (Kit_SRCS ${Kit_SRCS} vtkWin32VideoSource.cxx)
  ENDIF (VTK_VFW_SUPPORTS_CAPTURE)

  IF (VTK_USE_MATROX_IMAGING)
    SET (Kit_SRCS ${Kit_SRCS} vtkMILVideoSource.cxx)
    # Include directory needed for vtkMILVideoSource.cxx.
  ENDIF (VTK_USE_MATROX_IMAGING)
ENDIF (WIN32)


vtk_module_library(vtkIOVideo ${Kit_SRCS})
