set(Kit_SRCS
    vtkLODActor.cxx
    vtkQuadricLODActor.cxx)

vtk_module_library(vtkRenderingLOD ${Kit_SRCS})
