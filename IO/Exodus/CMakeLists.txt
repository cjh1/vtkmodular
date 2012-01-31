set(Kit_SRCS
  vtkExodusIICache.cxx
  vtkExodusIIReader.cxx
  vtkExodusIIReaderParser.cxx
  vtkExodusIIReaderVariableCheck.cxx
  vtkExodusModel.cxx
  )

vtk_add_library(vtkExodus ${Kit_SRCS})

include_directories(
  ${VTK_SOURCE_DIR}/TPL
  )
set_source_files_properties(
  vtkExodusIIReaderParser
  vtkExodusIIReaderVariableCheck
  WRAP_EXCLUDE
  )
