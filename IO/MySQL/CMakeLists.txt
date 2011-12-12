
find_package(MySQL REQUIRED)

set(MySQL_SRCS
  vtkMySQLDatabase.cxx
  vtkMySQLQuery.cxx
  vtkMySQLToTableReader.cxx
  vtkTableToMySQLWriter.cxx
  )

include_directories(
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_BINARY_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/Common/Misc
  ${MYSQL_INCLUDE_DIRECTORIES}
  )

vtk_add_library(vtkIOMySQL ${MySQL_SRCS})

target_link_libraries(vtkIOMySQL ${MYSQL_LIBRARY} ${MYSQL_EXTRA_LIBRARIES})
