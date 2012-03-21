set(KIT Chemistry)
set(UKIT CHEMISTRY)

set(KIT_TCL_LIBS vtkFilteringTCL vtkRenderingTCL vtkVolumeRenderingTCL)
set(KIT_PYTHON_LIBS vtkFilteringPythonD vtkRenderingPythonD vtkVolumeRenderingPythonD)
set(KIT_JAVA_LIBS vtkFilteringJava vtkRenderingJava vtkVolumeRenderingJava)
set(KIT_INTERFACE_LIBRARIES vtkFiltering vtkRendering vtkVolumeRendering)

set(Kit_SRCS
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

set_source_files_properties(
  vtkMoleculeToPolyDataFilter.cxx
  ABSTRACT
  )

set_source_files_properties(
  vtkBlueObeliskData.cxx
  vtkBlueObeliskDataParser.cxx
  WRAP_EXCLUDE
  )

# Generate configured header file
configure_file(${vtkChemistryCore_SOURCE_DIR}/vtkChemistryConfigure.h.in
               ${vtkChemistryCore_BINARY_DIR}/vtkChemistryConfigure.h IMMEDIATE)

vtk_module_library(vtkChemistryCore ${Kit_SRCS})
