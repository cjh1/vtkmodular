# Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
# All rights reserved.
# See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
#
#    This software is distributed WITHOUT ANY WARRANTY; without even
#    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#    PURPOSE.  See the above copyright notice for more information.
#

IF(NOT CMAKE_CROSSCOMPILING)
  include_directories(${VTK_SOURCE_DIR}/Common/Core
    ${VTK_BINARY_DIR}/Common/Core)
  VTK_ADD_EXECUTABLE(vtkEncodeString vtkEncodeString.cxx)
  IF(COMPILE_TOOLS_TARGET)
    ADD_DEPENDENCIES(${COMPILE_TOOLS_TARGET} vtkEncodeString)
  ENDIF(COMPILE_TOOLS_TARGET)
ENDIF(NOT CMAKE_CROSSCOMPILING)

SET(ENCODESTRING_EXE vtkEncodeString)
