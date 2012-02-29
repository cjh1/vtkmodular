set(Kit_SRCS
  vtkExporter.cxx
  vtkIVExporter.cxx
  vtkOBJExporter.cxx
  vtkOOGLExporter.cxx
  vtkPOVExporter.cxx
  vtkRIBExporter.cxx
  vtkRIBLight.cxx
  vtkRIBProperty.cxx
  vtkVRMLExporter.cxx
  vtkX3D.cxx
  vtkX3DExporter.cxx
  vtkX3DExporterFIWriter.cxx
  #vtkX3DExporterJavaHelper.cxx Needs JNI
  vtkX3DExporterWriter.cxx
  vtkX3DExporterXMLWriter.cxx
  vtkGL2PSExporter.cxx
  )

if(NOT VTK_USE_SYSTEM_GL2PS)
  # TODO: Build vtkgl2ps library over in its module
  list(APPEND Kit_SRCS ${VTK_SOURCE_DIR}/ThirdParty/gl2ps/vtkgl2ps/gl2ps.c)
  add_definitions(-DGL2PS_HAVE_ZLIB)
  add_definitions(-DGL2PS_HAVE_LIBPNG)
endif()

vtk_module_library(vtkIOExport ${Kit_SRCS})
