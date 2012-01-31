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
  vtkX3DExporterJavaHelper.cxx
  vtkX3DExporterWriter.cxx
  vtkX3DExporterXMLWriter.cxx
  vtkGL2PSExporter.cxx
  )
# FIXME need to work out what todo here
SET(Kit_GL2PS_SRCS ${VTK_SOURCE_DIR}/TPL/vtkgl2ps/gl2ps.c)
ADD_DEFINITIONS(-DGL2PS_HAVE_ZLIB)
ADD_DEFINITIONS(-DGL2PS_HAVE_LIBPNG)

vtk_add_library(vtkIOExport ${Kit_SRCS})

