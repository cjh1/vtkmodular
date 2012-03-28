set(Kit_SRCS
  #vtkInteractorStyle.cxx # Moved to RenderingCore for render window int
  vtkInteractorStyleFlight.cxx
  vtkInteractorStyleImage.cxx
  vtkInteractorStyleJoystickActor.cxx
  vtkInteractorStyleJoystickCamera.cxx
  vtkInteractorStyleRubberBand2D.cxx
  vtkInteractorStyleRubberBand3D.cxx
  vtkInteractorStyleRubberBandPick.cxx
  vtkInteractorStyleRubberBandZoom.cxx
  vtkInteractorStyleTerrain.cxx
  vtkInteractorStyleTrackballActor.cxx
  vtkInteractorStyleTrackballCamera.cxx
  vtkInteractorStyleTrackball.cxx
  vtkInteractorStyleUnicam.cxx
  vtkInteractorStyleUser.cxx

  vtkInteractorStyleSwitch.cxx
  vtkParallelCoordinatesInteractorStyle.cxx
  )

vtk_module_library(vtkInteractionStyle ${Kit_SRCS})
