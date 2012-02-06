set(Kit_SRCS
  vtkBoostBetweennessClustering.cxx
  vtkBoostBiconnectedComponents.cxx
  vtkBoostBrandesCentrality.cxx
  vtkBoostBreadthFirstSearch.cxx
  vtkBoostBreadthFirstSearchTree.cxx
  vtkBoostConnectedComponents.cxx
  vtkBoostExtractLargestComponent.cxx
  vtkBoostKruskalMinimumSpanningTree.cxx
  vtkBoostLogWeighting.cxx
  vtkBoostPrimMinimumSpanningTree.cxx
  vtkBoostRandomSparseArraySource.cxx
  vtkBoostSplitTableField.cxx  
  )

vtk_add_library(vtkInfovisBoostGraphAlgorithms ${Kit_SRCS})
