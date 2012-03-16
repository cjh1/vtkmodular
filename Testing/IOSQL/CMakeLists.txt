set(module_SRCS
  vtkTesting.cxx
  vtkTestingInteractor.cxx
  vtkTestingObjectFactory.cxx
  )

vtk_module_library(vtkTestingIOSQL ${module_SRCS})
