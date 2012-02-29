
find_package(MySQL REQUIRED)

set(MySQL_SRCS
  vtkMySQLDatabase.cxx
  vtkMySQLQuery.cxx
  vtkMySQLToTableReader.cxx
  vtkTableToMySQLWriter.cxx
  )

include_directories(
  ${MYSQL_INCLUDE_DIRECTORIES}
  )

vtk_module_library(vtkIOMySQL ${MySQL_SRCS})

target_link_libraries(vtkIOMySQL ${MYSQL_LIBRARY} ${MYSQL_EXTRA_LIBRARIES})
