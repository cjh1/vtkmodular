set(module_SRCS
  vtkAbstractContextBufferId.cxx
  vtkAbstractContextItem.cxx
  vtkBlockItem.cxx
  vtkBrush.cxx
  vtkContext2D.cxx
  vtkContext3D.cxx
  vtkContextActor.cxx
  vtkContextBufferId.cxx
  vtkContextClip.cxx
  vtkContextDevice2D.cxx
  vtkContextDevice3D.cxx
  vtkContextItem.cxx
  vtkContextKeyEvent.cxx
  vtkContextMapper2D.cxx
  vtkContextMouseEvent.cxx
  vtkContextScene.cxx
  vtkContextTransform.cxx
  vtkImageItem.cxx
  vtkOpenGL2ContextDevice2D.cxx
  vtkOpenGLContextBufferId.cxx
  vtkOpenGLContextDevice2D.cxx
  vtkOpenGLContextDevice3D.cxx
  vtkPen.cxx
#  vtkPiecewisePointHandleItem.cxx
  vtkTooltipItem.cxx
  )

set_source_files_properties(
  vtkContextKeyEvent
  vtkContextMouseEvent
  WRAP_EXCLUDE
  )

vtk_module_library(vtkRenderingContext2D ${module_SRCS})
