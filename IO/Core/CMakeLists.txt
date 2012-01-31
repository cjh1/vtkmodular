
SET(Kit_SRCS
  vtkAbstractParticleWriter.cxx
  vtkArrayReader.cxx
  vtkArrayWriter.cxx
  vtkASCIITextCodec.cxx
  vtkBase64InputStream.cxx
  vtkBase64OutputStream.cxx
  vtkBase64Utilities.cxx
  vtkDataCompressor.cxx
  vtkDataObjectReader.cxx
  vtkDataObjectWriter.cxx
  vtkDataReader.cxx
  vtkDataWriter.cxx
  vtkDelimitedTextWriter.cxx
  vtkGlobFileNames.cxx
  vtkGraphReader.cxx
  vtkGraphWriter.cxx
  vtkInputStream.cxx
  vtkJavaScriptDataWriter.cxx
  vtkOutputStream.cxx
  vtkSortFileNames.cxx
  vtkTextCodec.cxx
  vtkTextCodecFactory.cxx
  vtkUTF16TextCodec.cxx
  vtkUTF8TextCodec.cxx
  vtkWriter.cxx
  vtkZLibDataCompressor.cxx
  vtkTableReader.cxx
  vtkTableWriter.cxx
  vtkArrayDataReader.cxx
  vtkArrayDataWriter.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/TPL/utf8/source
  ${VTK_SOURCE_DIR}/Common/Core
  ${VTK_BINARY_DIR}/Common/Core
  ${VTK_SOURCE_DIR}/TPL
  )

vtk_add_library(vtkIOCore ${Kit_SRCS})
