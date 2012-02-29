set(Kit_SRCS
  vtkAbstractMapper3D.cxx
  vtkAbstractMapper.cxx
  vtkAbstractPicker.cxx
  vtkAbstractVolumeMapper.cxx
  vtkActor2DCollection.cxx
  vtkActor2D.cxx
  vtkActorCollection.cxx
  vtkActor.cxx
  vtkAssembly.cxx
  vtkCameraActor.cxx
  vtkCamera.cxx
  vtkCameraInterpolator.cxx
  vtkCellCenterDepthSort.cxx
  vtkChooserPainter.cxx
  vtkClipPlanesPainter.cxx
  vtkCoincidentTopologyResolutionPainter.cxx
  #vtkColorMaterialHelper.cxx - needs vtkgl.h
  vtkColorTransferFunction.cxx
  vtkCompositePainter.cxx # needs vtkOpenGL.h
  vtkCompositePolyDataMapper2.cxx
  vtkCompositePolyDataMapper.cxx
  vtkCoordinate.cxx
  #vtkCoreGraphicsGPUInfoList.cxx - ApplicationServices/ApplicationServices.h
  vtkCullerCollection.cxx
  vtkCuller.cxx
  vtkDataSetMapper.cxx
  #vtkDataTransferHelper.cxx - needs vtkOpenGLRenderWindow
  vtkDefaultPainter.cxx
  #vtkDirectXGPUInfoList.cxx - for Windows only?
  vtkDiscretizableColorTransferFunction.cxx
  vtkDisplayListPainter.cxx
  vtkDistanceToCamera.cxx
  vtkDummyGPUInfoList.cxx
  #vtkDynamic2DLabelMapper.cxx - needs vtkLabeledDataMapper.h
  vtkFollower.cxx
  #vtkFrameBufferObject.cxx Needs vtkOpenGLExtensionManager
  vtkFrustumCoverageCuller.cxx
  #vtkGenericOpenGLRenderWindow.cxx - OpenGL...
  vtkGenericRenderWindowInteractor.cxx
  vtkGenericVertexAttributeMapping.cxx
  vtkGlyph3DMapper.cxx
  vtkGPUInfo.cxx
  vtkGPUInfoList.cxx
  vtkGraphicsFactory.cxx
  #vtkGraphMapper.cxx - vtkGraphToPolyData
  vtkGraphToGlyphs.cxx
  vtkHardwareSelector.cxx
  vtkHierarchicalPolyDataMapper.cxx
  #vtkIdentColoredPainter.cxx - Needs vtkOpenGL.h
  vtkImageActor.cxx
  vtkImageMapper3D.cxx
  vtkImageMapper.cxx
  vtkImageProperty.cxx
  #vtkImageResliceMapper.cxx - Needs vtkImageResliceToColors.h
  vtkImageSliceCollection.cxx
  vtkImageSlice.cxx
  vtkImageSliceMapper.cxx
  vtkImageStack.cxx
  #vtkImageViewer2.cxx - imaging
  #vtkImageViewer.cxx
  vtkImagingFactory.cxx
  vtkInteractorEventRecorder.cxx
  vtkInteractorObserver.cxx
  vtkInteractorStyle.cxx
  #vtkInteractorStyleSwitch.cxx
  vtkLightActor.cxx
  vtkLightCollection.cxx
  vtkLight.cxx
  #vtkLightingHelper.cxx - vtkgl.h
  vtkLightingPainter.cxx
  vtkLightKit.cxx
  #vtkLineIntegralConvolution2D.cxx - vtkOpenGLExtensionManager
  vtkLinesPainter.cxx
  vtkLogLookupTable.cxx
  vtkLookupTableWithEnabling.cxx
  vtkMapArrayValues.cxx
  vtkMapper2D.cxx
  vtkMapperCollection.cxx
  vtkMapper.cxx
  vtkObserverMediator.cxx
  #vtkOSOpenGLRenderWindow.cxx - vtkOpenGLRenderWindow
  vtkPainter.cxx
  vtkPainterDeviceAdapter.cxx
  vtkPainterPolyDataMapper.cxx # vtkHardwareSelectionPolyDataPainter.h
  #vtkParallelCoordinatesActor.cxx
  #vtkParallelCoordinatesInteractorStyle.cxx
  #vtkPixelBufferObject.cxx - vtkOpenGLExtensionManager
  #vtkPointSetToLabelHierarchy.cxx - vtkLabelHierarchyAlgorithm.h
  vtkPointsPainter.cxx
  vtkPolyDataMapper2D.cxx
  vtkPolyDataMapper.cxx
  vtkPolyDataPainter.cxx
  vtkPolygonsPainter.cxx
  vtkPrimitivePainter.cxx # vtkGLSLShaderDeviceAdapter2.h
  vtkProp3DCollection.cxx
  vtkProp3D.cxx
  vtkProp3DFollower.cxx
  vtkPropAssembly.cxx
  vtkPropCollection.cxx
  vtkProp.cxx
  vtkProperty2D.cxx
  vtkProperty.cxx # needs a load if image readers - IOImage, IOXML
  vtkRendererCollection.cxx
  vtkRenderer.cxx
  vtkRendererDelegate.cxx
  vtkRendererSource.cxx
  vtkRenderState.cxx
  vtkRenderWindowCollection.cxx
  vtkRenderWindow.cxx
  vtkRenderWindowInteractor.cxx
  vtkRepresentationPainter.cxx
  vtkScalarsToColorsPainter.cxx
  vtkSelectVisiblePoints.cxx
  #vtkShader2Collection.cxx
  #vtkShader2.cxx - vtkgl.h
  vtkShader.cxx # vtkXMLShader
  vtkShaderDeviceAdapter.cxx
  vtkShaderDeviceAdapter2.cxx
  #vtkShaderProgram2.cxx - vtkOpenGLExtensionManager
  vtkShaderProgram.cxx # vtkXMLShaderProgram
  vtkStandardPolyDataPainter.cxx # - vtkOpenGLProperty
  vtkStringToImage.cxx
  #vtkSurfaceLICDefaultPainter.cxx
  #vtkSurfaceLICPainter.cxx - vtkBase64Utilities
  #vtkTesting.cxx - vtkPNGWriter
  #vtkTestingInteractor.cxx
  #vtkTestingObjectFactory.cxx - vtkTestDriver.h
  vtkTexture.cxx
  vtkTexturedActor2D.cxx
  #vtkTextureObject.cxx - vtkOpenGLExtensionManager
  #vtkTextureUnitManager.cxx - vtkOpenGLRenderWindow
  vtkTransformCoordinateSystems.cxx
  vtkTransformInterpolator.cxx
  vtkTStripsPainter.cxx
  vtkTupleInterpolator.cxx
  #vtkUniformVariables.cxx - vtkgl.h
  vtkViewDependentErrorMetric.cxx
  vtkViewport.cxx
  #vtkViewTheme.cxx - vtkTextProperty
  vtkVisibilitySort.cxx
  #vtkVisibleCellSelector.cxx - vtkRenderer has no SetSelectMode...
  vtkVolumeCollection.cxx
  vtkVolume.cxx
  vtkVolumeProperty.cxx
  vtkWindowLevelLookupTable.cxx
  vtkWindowToImageFilter.cxx

  vtkAssemblyNode.cxx # Needed by vtkAssembly
  vtkAssemblyPath.cxx # Needed by vtkAssembly
  vtkAssemblyPaths.cxx # Needed by vtkAssembly

  vtkAreaPicker.cxx # Needed by vtkRenderer
  vtkPicker.cxx # Needed by vtkRenderer
  vtkAbstractPropPicker.cxx # Needed by vtkAreaPicker
  vtkPropPicker.cxx # Needed by vtkRenderWindowInteractor
  vtkLODProp3D.cxx # Needed by vtkAreaPicker
  vtkWorldPointPicker.cxx # Needed by vtkPropPicker
  vtkHardwareSelectionPolyDataPainter.cxx # Needed by vtkPainterPolyDataMapper

  # vtkTDx stuff dragged in by vtkInteractorStyle
  vtkTDxInteractorStyle.cxx
  vtkTDxInteractorStyleCamera.cxx
  vtkTDxInteractorStyleSettings.cxx
  # Needed for the InteractorStyleSwitch...
  vtkCellPicker.cxx
  vtkPointPicker.cxx
  vtkRenderedAreaPicker.cxx
  vtkScenePicker.cxx
  )

include_directories(
  ${VTK_SOURCE_DIR}/Rendering/OpenGL # For the OpenGL headers...
  ${VTK_SOURCE_DIR}/Rendering/GLSL # For the GLSL headers...
  ${VTK_BINARY_DIR}/Rendering/OpenGL # For the OpenGL headers...
  ${VTK_BINARY_DIR}/Rendering/GLSL # For the GLSL headers...
  )

vtk_module_library(vtkRenderingCore ${Kit_SRCS})
