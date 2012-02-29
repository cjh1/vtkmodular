set(Kit_SRCS
  vtkCameraPass.cxx
  vtkClearZPass.cxx
  vtkColorMaterialHelper.cxx
  #vtkCoreGraphicsGPUInfoList.cxx # Mac specific
  vtkDataTransferHelper.cxx
  vtkDefaultPass.cxx
  vtkDepthPeelingPass.cxx
  vtkFrameBufferObject.cxx
  vtkGaussianBlurPass.cxx
  vtkGenericOpenGLRenderWindow.cxx
  #vtkIdentColoredPainter.cxx
  vtkImageProcessingPass.cxx
  vtkLightingHelper.cxx
  vtkLightsPass.cxx
  vtkLineIntegralConvolution2D.cxx
  vtkOpaquePass.cxx
  vtkOpenGLActor.cxx
  vtkOpenGLCamera.cxx
  vtkOpenGLClipPlanesPainter.cxx
  vtkOpenGLCoincidentTopologyResolutionPainter.cxx
  vtkOpenGLDisplayListPainter.cxx
  vtkOpenGLExtensionManager.cxx
  #vtkOpenGLFreeTypeTextMapper.cxx
  vtkOpenGLGlyph3DMapper.cxx
  vtkOpenGLHardwareSupport.cxx
  vtkOpenGLImageMapper.cxx
  #vtkOpenGLImageResliceMapper.cxx
  vtkOpenGLImageSliceMapper.cxx
  vtkOpenGLLight.cxx
  vtkOpenGLLightingPainter.cxx
  vtkOpenGLPainterDeviceAdapter.cxx
  vtkOpenGLPolyDataMapper2D.cxx
  vtkOpenGLPolyDataMapper.cxx
  vtkOpenGLProperty.cxx
  vtkOpenGLRenderer.cxx
  vtkOpenGLRenderWindow.cxx
  vtkOpenGLRepresentationPainter.cxx
  vtkOpenGLScalarsToColorsPainter.cxx
  vtkOpenGLState.cxx
  vtkOpenGLTexture.cxx
  #vtkOSOpenGLRenderWindow.cxx # OS Mesa
  vtkOverlayPass.cxx
  vtkPixelBufferObject.cxx
  vtkRenderPassCollection.cxx
  vtkRenderPass.cxx
  vtkSequencePass.cxx
  vtkShader2Collection.cxx
  vtkShader2.cxx
  vtkShaderProgram2.cxx
  vtkShadowMapBakerPass.cxx
  vtkShadowMapPass.cxx
  vtkSobelGradientMagnitudePass.cxx
  vtkTextureObject.cxx
  vtkTextureUnitManager.cxx
  vtkTranslucentPass.cxx
  vtkUniformVariables.cxx
  vtkVolumetricPass.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/vtkgl.cxx
  vtkGLSLShaderDeviceAdapter.cxx
  vtkGLSLShaderDeviceAdapter2.cxx
  vtkGLSLShader.cxx
  vtkGLSLShaderProgram.cxx
  ${CMAKE_CURRENT_BINARY_DIR}/vtkRenderingOpenGLObjectFactory.cxx
  )

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/vtkgl.cxx
  GENERATED)

set_source_files_properties(
  vtkLightingHelper
  vtkRenderState
  vtkOpenGLState
  vtkShader2
  vtkShader2Collection
  vtkShaderProgram2
  vtkTextureUnitManager
  WRAP_EXCLUDE
  )

find_package(OpenGL REQUIRED)

# Configuration for vtkOpenGLExtensionManager
if(WIN32)
  set(VTK_USE_WGL_GET_PROC_ADDRESS 1)
elseif(APPLE)
  set(VTK_USE_APPLE_LOADER 1)
else()
  include(CheckFunctionExists)
  set(VTK_SAVE_CMAKE_REQUIRED_LIBRARIES "${CMAKE_REQUIRED_LIBRARIES}")
  set(CMAKE_REQUIRED_LIBRARIES
    ${OPENGL_LIBRARIES}
    ${CMAKE_THREAD_LIBS}
    ${CMAKE_REQUIRED_LIBRARIES}
    -lm
    )
  if(VTK_USE_X)
    include(vtkTestGLX)
    check_function_exists(glXGetProcAddressARB VTK_USE_GLX_GET_PROC_ADDRESS_ARB)
    if(VTK_USE_GLX_GET_PROC_ADDRESS_ARB)
      if(NOT "${VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS_INCLUDES}" STREQUAL "${OPENGL_INCLUDE_DIR}")
        # The OpenGL includes changed.  Retest glXGetProcAddressARB prototype.
        set(VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS_TESTED 0)
      endif()
      if(NOT VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS_TESTED)
        message(STATUS "Looking for glXGetProcAddressARB in GL/glx.h")
        try_compile(VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS
          ${CMAKE_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR}/CheckglXGetProcAddressARB.cxx
          CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${CMAKE_REQUIRED_LIBRARIES}"
          "-DINCLUDE_DIRECTORIES:STRING=${OPENGL_INCLUDE_DIR}"
          OUTPUT_VARIABLE OUTPUT)
        message(STATUS "Looking for glXGetProcAddressARB in GL/glx.h - ${VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS}")
        file(APPEND ${CMAKE_BINARY_DIR}/CMakeOutput.log
          "Determining if glXGetProcAddressARB exists in GL/glx.h ${VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS} with the following output:\n"
          "${OUTPUT}\n\n")
        set(VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS_TESTED 1
          CACHE INTERNAL "Already set VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS")
        set(VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS_INCLUDES
          "${OPENGL_INCLUDE_DIR}"
          CACHE INTERNAL "OpenGL includes used to test glXGetProcAddressARB prototype.")
      endif()
      if(NOT VTK_GLX_GET_PROC_ADDRESS_ARB_PROTOTYPE_EXISTS)
        set(VTK_DEFINE_GLX_GET_PROC_ADDRESS_PROTOTYPE 1)
      endif()
    else()
      check_function_exists(glXGetProcAddress VTK_USE_GLX_GET_PROC_ADDRESS)
      if(NOT VTK_USE_GLX_GET_PROC_ADDRESS)
        message(STATUS "Could not find extension loader.  Extensions disabled.")
        set(VTK_NO_EXTENSION_LOADING 1)
      endif()
    endif()
  else()
    set(VTK_NO_EXTENSION_LOADING 1)
  endif()
  set(CMAKE_REQUIRED_LIBRARIES "${VTK_SAVE_CMAKE_REQUIRED_LIBRARIES}")
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/vtkOpenGLExtensionManagerConfigure.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/vtkOpenGLExtensionManagerConfigure.h)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/vtkgl.cxx
  COMMAND vtkParseOGLExt
  ARGS ${CMAKE_CURRENT_BINARY_DIR} ${VTK_GLEXT_FILE} ${VTK_GLXEXT_FILE} ${VTK_WGLEXT_FILE}
  DEPENDS ${VTK_GLEXT_FILE} ${VTK_GLXEXT_FILE} ${VTK_WGLEXT_FILE}
  )

set_source_files_properties(vtkOpenGLExtensionManager.cxx
  PROPERTIES OBJECT_DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vtkgl.cxx)

include_directories(
  ${OPENGL_INCLUDE_DIR}
  )

set(shader_files
  vtkColorMaterialHelper_vs.glsl
  vtkDepthPeeling_fs.glsl
  vtkGaussianBlurPassShader_fs.glsl
  vtkLighting_s.glsl # s not vs or fs because it can be used in both.
  vtkLightingHelper_s.glsl # s not vs or fs because it can be used in both.
  vtkLineIntegralConvolution2D_fs.glsl
  vtkLineIntegralConvolution2D_fs1.glsl
  vtkLineIntegralConvolution2D_fs2.glsl
  vtkOpenGLRenderer_PeelingFS.glsl
  vtkOpenGLPropertyDefaultPropFunc_fs.glsl
  vtkOpenGLPropertyDefaultPropFunc_vs.glsl
  vtkOpenGLPropertyDefaultMain_fs.glsl
  vtkOpenGLPropertyDefaultMain_vs.glsl
  vtkSobelGradientMagnitudePassShader1_fs.glsl
  vtkSobelGradientMagnitudePassShader2_fs.glsl
  vtkShadowMapPassShader_fs.glsl
  vtkShadowMapPassShader_vs.glsl
  #  vtkSurfaceLICPainter_fs1.glsl
  #vtkSurfaceLICPainter_fs2.glsl
  #vtkSurfaceLICPainter_vs1.glsl
  )

unset(shader_h_files)
foreach(file ${shader_files})
  get_filename_component(file_we ${file} NAME_WE)
  set(src  ${CMAKE_CURRENT_SOURCE_DIR}/${file})
  set(res  ${CMAKE_CURRENT_BINARY_DIR}/${file_we}.cxx)
  set(resh ${CMAKE_CURRENT_BINARY_DIR}/${file_we}.h)
  list(APPEND shader_h_files ${resh})
  add_custom_command(
    OUTPUT ${res} ${resh}
    DEPENDS ${src} vtkEncodeString
    COMMAND vtkEncodeString
    ARGS ${res} ${src} ${file_we} --build-header VTKRENDERINGOPENGL_EXPORT vtkRenderingOpenGLExport.h
    )
  list(APPEND Kit_SRCS ${res})
endforeach()

# Now we need to generate the object factory for this module. Create a list of
# overrides, and then generate the class that overrides those classes.
macro(vtk_add_override base override)
  list(APPEND vtk_module_overrides ${base})
  set(vtk_module_${base}_override ${override})
endmacro()

set(opengl_overrides
  Actor
  Camera
  ClipPlanesPainter
  CoincidentTopologyResolutionPainter
  DisplayListPainter
  Glyph3DMapper
  ImageSliceMapper
  Light
  LightingPainter
  PainterDeviceAdapter
  Property
  PolyDataMapper
  Renderer
  RepresentationPainter
  ScalarsToColorsPainter
  Texture
  )
foreach(_override ${opengl_overrides})
  vtk_add_override(vtk${_override} vtkOpenGL${_override})
endforeach()

# Now we iterate and create that class file...
foreach(_class ${vtk_module_overrides})
  set(_override ${vtk_module_${_class}_override})
  set(_vtk_override_includes "${_vtk_override_includes}
#include \"${_override}.h\"")
  set(_vtk_override_creates "${_vtk_override_creates}
VTK_CREATE_CREATE_FUNCTION(${_override})")
  set(_vtk_override_do "${_vtk_override_do}
  this->RegisterOverride(\"${_class}\",
                         \"${_override}\",
                         \"Override for ${vtk-module} module\", 1,
                         vtkObjectFactoryCreate${_override});")
endforeach()

# Now lets create the object factory classes
string(TOUPPER ${vtk-module} VTK-MODULE)
configure_file(${VTK_CMAKE_DIR}/vtkObjectFactory.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/${vtk-module}ObjectFactory.h)
configure_file(${VTK_CMAKE_DIR}/vtkObjectFactory.cxx.in
  ${CMAKE_CURRENT_BINARY_DIR}/${vtk-module}ObjectFactory.cxx)

vtk_module_library(vtkRenderingOpenGL ${Kit_SRCS})
target_link_libraries(vtkRenderingOpenGL ${OPENGL_LIBRARIES})

add_subdirectory(Testing/Cxx)
