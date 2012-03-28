include (FindMPI)
include_directories(${MPI_INCLUDE_PATH})

set(Kit_SRCS
  vtkClientServerCompositePass.cxx
  vtkClientServerSynchronizedRenderers.cxx
  vtkCompositedSynchronizedRenderers.cxx
  vtkCompositer.cxx
  vtkCompositeRenderManager.cxx
  vtkCompositeRGBAPass.cxx
  # vtkCompositeZPass.cxx # fixme shaders
  #  vtkCompositeZPassShader_fs.glsl
  vtkCompressCompositer.cxx
  vtkParallelRenderManager.cxx
  vtkPHardwareSelector.cxx
  vtkSynchronizedRenderers.cxx
  vtkSynchronizedRenderWindows.cxx
  vtkTreeCompositer.cxx
  )
vtk_module_library(vtkRenderingParallel ${Kit_SRCS})
