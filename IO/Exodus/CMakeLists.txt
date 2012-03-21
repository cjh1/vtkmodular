set(Kit_SRCS
  vtkExodusIICache.cxx
  vtkExodusIIReader.cxx
  vtkExodusIIReaderParser.cxx
  vtkExodusIIReaderVariableCheck.cxx
  vtkExodusModel.cxx
  )


set_source_files_properties(
  vtkExodusIIReaderParser
  vtkExodusIIReaderVariableCheck
  WRAP_EXCLUDE
  )


vtk_module_library(vtkIOExodus ${Kit_SRCS})
