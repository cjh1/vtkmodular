set(Kit_SRCS
  vtkChacoGraphReader.cxx
  vtkChacoGraphReader.h
  vtkDelimitedTextReader.cxx
  vtkDelimitedTextReader.h
  vtkDIMACSGraphReader.cxx
  vtkDIMACSGraphReader.h
  vtkDIMACSGraphWriter.cxx
  vtkDIMACSGraphWriter.h
  vtkFixedWidthTextReader.cxx
  vtkFixedWidthTextReader.h
  vtkISIReader.cxx
  vtkISIReader.h
  vtkRISReader.cxx
  vtkRISReader.h
  vtkTulipReader.cxx
  vtkTulipReader.h
  vtkXGMLReader.cxx
  vtkXGMLReader.h
  vtkXMLTreeReader.cxx
  vtkXMLTreeReader.h
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/TPL
  )

vtk_add_library(vtkIOInfovis ${Kit_SRCS})
