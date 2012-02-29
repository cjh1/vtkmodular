set(Kit_SRCS
  vtkMINCImageAttributes.cxx
  vtkMINCImageReader.cxx
  vtkMINCImageWriter.cxx
  vtkMNIObjectReader.cxx
  vtkMNIObjectWriter.cxx
  vtkMNITagPointReader.cxx
  vtkMNITagPointWriter.cxx
  vtkMNITransformReader.cxx
  vtkMNITransformWriter.cxx
  )

vtk_module_library(vtkIOMINC ${Kit_SRCS})

#IF(NOT VTK_INSTALL_NO_DEVELOPMENT)
#  INSTALL(FILES
#    ${CMAKE_CURRENT_SOURCE_DIR}/vtkMINC.h
#    DESTINATION ${VTK_INSTALL_INCLUDE_DIR_CM24}
#    COMPONENT Development
#    )
#ENDIF(NOT VTK_INSTALL_NO_DEVELOPMENT)
