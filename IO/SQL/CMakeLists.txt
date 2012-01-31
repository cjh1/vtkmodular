
set(Kit_SRCS
  vtkDatabaseToTableReader.cxx
  vtkRowQuery.cxx
  vtkRowQueryToTable.cxx
  vtkSQLDatabase.cxx
  #  vtkSQLDatabaseGraphSource.cxx
  vtkSQLDatabaseSchema.cxx
  vtkSQLDatabaseTableSource.cxx
  #vtkSQLGraphReader.cxx
  vtkSQLQuery.cxx
  vtkTableToDatabaseWriter.cxx
  )

set(SQLite_SRCS
  vtkSQLiteDatabase.cxx
  vtkSQLiteQuery.cxx
  vtkSQLiteToTableReader.cxx
  vtkTableToSQLiteWriter.cxx
  )

include_directories(
  ${VTK_SOURCE_DIR}/Common/Misc
  ${VTK_SOURCE_DIR}/TPL
  )

vtk_add_library(vtkIOSQL ${Kit_SRCS} ${SQLite_SRCS})
