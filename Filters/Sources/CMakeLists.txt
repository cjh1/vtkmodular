set(Kit_SRCS
  vtkArcSource.cxx
  vtkArrowSource.cxx
  vtkButtonSource.cxx
  vtkConeSource.cxx
  vtkCubeSource.cxx
  vtkCylinderSource.cxx
  vtkDiskSource.cxx
  vtkEllipticalButtonSource.cxx
  vtkFrustumSource.cxx
  vtkGlyphSource2D.cxx
  vtkHyperOctreeFractalSource.cxx
  vtkLineSource.cxx
  vtkOutlineCornerSource.cxx
  vtkOutlineSource.cxx
  vtkParametricFunctionSource.cxx
  vtkPlaneSource.cxx
  vtkPlatonicSolidSource.cxx
  vtkPointSource.cxx
  vtkProgrammableDataObjectSource.cxx
  vtkProgrammableSource.cxx
  vtkRectangularButtonSource.cxx
  vtkRegularPolygonSource.cxx
  #vtkRRandomTableSource.cxx # Should be in R kit
  #vtkSectorSource.cxx # Needs vtkRotationalExtrusionFilter
  vtkSelectionSource.cxx
  vtkSphereSource.cxx
  vtkSuperquadricSource.cxx
  vtkTessellatedBoxSource.cxx
  vtkTextSource.cxx
  vtkTexturedSphereSource.cxx
  vtkGraphToPolyData.cxx
  )

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${VTK_SOURCE_DIR}/Utilities
  )

vtk_add_library(vtkFiltersSources ${Kit_SRCS})
