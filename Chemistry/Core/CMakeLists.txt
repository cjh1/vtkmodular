SET(KIT Chemistry)
SET(UKIT CHEMISTRY)

SET(KIT_TCL_LIBS vtkFilteringTCL vtkRenderingTCL vtkVolumeRenderingTCL)
SET(KIT_PYTHON_LIBS vtkFilteringPythonD vtkRenderingPythonD vtkVolumeRenderingPythonD)
SET(KIT_JAVA_LIBS vtkFilteringJava vtkRenderingJava vtkVolumeRenderingJava)
SET(KIT_INTERFACE_LIBRARIES vtkFiltering vtkRendering vtkVolumeRendering)

SET(Kit_SRCS
  vtkBlueObeliskData.cxx
  vtkBlueObeliskDataParser.cxx
  vtkCMLMoleculeReader.cxx
  vtkMoleculeAlgorithm.cxx
  vtkMoleculeMapper.cxx
  vtkMoleculeToAtomBallFilter.cxx
  vtkMoleculeToBondStickFilter.cxx
  vtkMoleculeToPolyDataFilter.cxx
  vtkPeriodicTable.cxx
  vtkProgrammableElectronicData.cxx
  vtkSimpleBondPerceiver.cxx
  )

SET_SOURCE_FILES_PROPERTIES(
  vtkMoleculeToPolyDataFilter.cxx
  ABSTRACT
  )

SET(Kit_EXTRA_SRCS)
SET(Kit_EXTRA_CMDS)
SET(Kit_TCL_EXTRA_SRCS)
SET(Kit_PYTHON_EXTRA_SRCS)
SET(Kit_JAVA_EXTRA_SRCS)
SET(KIT_TCL_DEPS)
SET(KIT_PYTHON_DEPS)
SET(KIT_JAVA_DEPS)

# OpenQube setup
FIND_PACKAGE(OpenQube QUIET)
IF(OpenQube_FOUND)
  FIND_PACKAGE(Eigen2 QUIET)
ENDIF(OpenQube_FOUND)
VTK_DEPENDENT_OPTION(VTK_USE_OPENQUBE
                     "Compile OpenQube support into vtkChemistry."
                     ON "OpenQube_FOUND;EIGEN2_FOUND" OFF)
IF(VTK_USE_OPENQUBE)
  INCLUDE_DIRECTORIES(${OpenQube_INCLUDE_DIRS} ${EIGEN2_INCLUDE_DIR})
  SET(KIT_LIBS ${KIT_LIBS} OpenQube)
  SET(Kit_SRCS
    ${Kit_SRCS}
    vtkOpenQubeElectronicData.cxx
    vtkOpenQubeMoleculeSource.cxx
  )
ENDIF(VTK_USE_OPENQUBE)

# Install Blue Obelisk Data Repository files
INSTALL(DIRECTORY vtkBODRData
  DESTINATION ${VTK_INSTALL_SHARE_DIR_CM24}/vtkChemistry
  )

# Generate configured header file
CONFIGURE_FILE(${vtkChemistryCore_SOURCE_DIR}/vtkChemistryConfigure.h.in
               ${vtkChemistryCore_BINARY_DIR}/vtkChemistryConfigure.h IMMEDIATE)

vtk_module_library(vtkChemistryCore ${Kit_SRCS})
