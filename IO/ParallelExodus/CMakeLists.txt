set(Kit_SRCS
  vtkPExodusIIReader.cxx
  )

vtk_module_library(vtkIOParallelExodus ${Kit_SRCS})
