set(Kit_SRCS
  vtkTDxDevice.cxx
  vtkTDxInteractorStyleGeo.cxx
  )

SET_SOURCE_FILES_PROPERTIES(vtkTDxDevice ABSTRACT)
# -----------------------------------------------------------------------------
# 3DConnexion device (SpaceNavigator, etc... ) on Unix.
IF(VTK_USE_X)
  OPTION(VTK_USE_TDX "Use 3Dconnexion device" OFF)
  MARK_AS_ADVANCED(VTK_USE_TDX)
  IF(VTK_USE_TDX)

   SET(VTK_TDX_INCLUDE_PATH CACHE PATH "Directory path to xdrvlib.h for 3DConnexion device")
   SET(VTK_TDX_OBJECT_PATH CACHE FILEPATH "File path to xdrvlib.a for 3DConnexion device")
   SET(Kit_SRCS ${Kit_SRCS} vtkTDxDevice.cxx vtkTDxUnixDevice.cxx)
   INCLUDE_DIRECTORIES(${VTK_TDX_INCLUDE_PATH})
   SET_SOURCE_FILES_PROPERTIES(vtkTDxDevice ABSTRACT)
   SET_SOURCE_FILES_PROPERTIES(vtkTDxUnixDevice WRAP_EXCLUDE)
   LIST(APPEND KIT_INTERFACE_LIBRARIES ${VTK_TDX_OBJECT_PATH})
  ENDIF()
ENDIF()
# -----------------------------------------------------------------------------
# 3DConnexion device (SpaceNavigator, etc... ) on Mac (not X11).
IF(VTK_USE_CARBON OR VTK_USE_COCOA)
  OPTION(VTK_USE_TDX "Use 3Dconnexion device" OFF)
  MARK_AS_ADVANCED(VTK_USE_TDX)
  IF(VTK_USE_TDX)
# framework is in /Library/Frameworks/3DconnexionClient.framework
   find_package(3DconnexionClient)
   if(3DconnexionClient_FOUND)
     set(KIT_LIBS ${KIT_LIBS} ${3DconnexionClient_LIBRARY})
     include_directories(${3DconnexionClient_INCLUDE_DIR})
   endif()
   SET(Kit_SRCS ${Kit_SRCS} vtkTDxDevice.cxx vtkTDxMacDevice.cxx)
   SET_SOURCE_FILES_PROPERTIES(vtkTDxDevice.cxx ABSTRACT)
   LIST(APPEND KIT_INTERFACE_LIBRARIES ${VTK_TDX_OBJECT_PATH})
  ENDIF()
ENDIF()
# -----------------------------------------------------------------------------
# 3DConnexion device (SpaceNavigator, etc... ) on Windows.
IF(WIN32)
  OPTION(VTK_USE_TDX "Use 3Dconnextion device" OFF)
  MARK_AS_ADVANCED(VTK_USE_TDX)
  IF(VTK_USE_TDX)
   SET(Kit_SRCS ${Kit_SRCS} vtkTDxDevice.cxx vtkTDxWinDevice.cxx)
   SET_SOURCE_FILES_PROPERTIES(vtkTDxDevice.cxx ABSTRACT)
  ENDIF()
ENDIF()
# -----------------------------------------------------------------------------
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/vtkTDxConfigure.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/vtkTDxConfigure.h @ONLY IMMEDIATE)

vtk_module_library(vtkRenderingTDx ${Kit_SRCS})
