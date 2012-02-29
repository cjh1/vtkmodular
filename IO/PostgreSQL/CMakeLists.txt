
find_package(PostgreSQL REQUIRED)

set(PostgreSQL_SRCS
  vtkPostgreSQLDatabase.cxx
  vtkPostgreSQLQuery.cxx
  vtkPostgreSQLToTableReader.cxx
  vtkTableToPostgreSQLWriter.cxx
  )

include_directories(
  ${PostgreSQL_INCLUDE_DIRS}
  )

vtk_module_library(vtkIOPostgreSQL ${PostgreSQL_SRCS})

target_link_libraries(vtkIOPostgreSQL ${PostgreSQL_LIBRARY})
