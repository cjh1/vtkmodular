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

# Generate configured header file
configure_file(${vtkChemistryCore_SOURCE_DIR}/vtkChemistryConfigure.h.in
               ${vtkChemistryCore_BINARY_DIR}/vtkChemistryConfigure.h IMMEDIATE)

vtk_module_library(vtkChemistryCore ${Kit_SRCS})
