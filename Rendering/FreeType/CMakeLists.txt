set(Kit_SRCS
  face_arial_bold.cxx
  face_arial_bold_italic.cxx
  face_arial.cxx
  face_arial_italic.cxx
  face_courier_bold.cxx
  face_courier_bold_italic.cxx
  face_courier.cxx
  face_courier_italic.cxx
  face_times_bold.cxx
  face_times_bold_italic.cxx
  face_times.cxx
  face_times_italic.cxx
  )

include_directories(
  ${VTK_SOURCE_DIR}/TPL
  ${VTK_SOURCE_DIR}/TPL/vtkfreetype/include)

vtk_add_library(vtkRenderingFreeType ${Kit_SRCS})

