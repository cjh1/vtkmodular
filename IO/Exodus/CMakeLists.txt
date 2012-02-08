set(Kit_SRCS
  vtkExodusIICache.cxx
  vtkExodusIIReader.cxx
  vtkExodusIIReaderParser.cxx
  vtkExodusIIReaderVariableCheck.cxx
  vtkExodusModel.cxx
  )

vtk_add_library(vtkIOExodus ${Kit_SRCS})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/TPL
  )
set_source_files_properties(
  vtkExodusIIReaderParser
  vtkExodusIIReaderVariableCheck
  WRAP_EXCLUDE
  )
