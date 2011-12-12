
find_package(PostgreSQL REQUIRED)

set(PostgreSQL_SRCS
  vtkPostgreSQLDatabase.cxx
  vtkPostgreSQLQuery.cxx
  vtkPostgreSQLToTableReader.cxx
  vtkTableToPostgreSQLWriter.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_BINARY_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/Common/Misc
  ${VTK_SOURCE_DIR}/Common/DataModel
  ${VTK_SOURCE_DIR}/IO/Core
  ${VTK_SOURCE_DIR}/IO/SQL
  ${PostgreSQL_INCLUDE_DIRS}
  )

vtk_add_library(vtkIOPostgreSQL ${PostgreSQL_SRCS})

target_link_libraries(vtkIOPostgreSQL ${PostgreSQL_LIBRARY})
