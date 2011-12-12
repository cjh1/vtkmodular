
find_package(ODBC REQUIRED)

set(ODBC_SRCS
  vtkODBCDatabase.cxx
  vtkODBCQuery.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_BINARY_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/Common/Misc
  ${VTK_SOURCE_DIR}/Common/DataModel
  ${VTK_SOURCE_DIR}/IO/Core
  ${VTK_SOURCE_DIR}/IO/SQL
  ${ODBC_INCLUDE_DIRECTORIES}
  )

vtk_add_library(vtkIOODBC ${ODBC_SRCS})

target_link_libraries(vtkIOODBC ${ODBC_LIBRARIES})
