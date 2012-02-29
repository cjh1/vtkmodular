set(Kit_SRCS
  vtkPBGLBreadthFirstSearch.cxx
  vtkPBGLCollapseGraph.cxx
  vtkPBGLCollapseParallelEdges.cxx
  vtkPBGLCollectGraph.cxx
  vtkPBGLConnectedComponents.cxx
  vtkPBGLDistributedGraphHelper.cxx
  vtkPBGLGraphSQLReader.cxx
  vtkPBGLMinimumSpanningTree.cxx
  vtkPBGLRandomGraphSource.cxx
  vtkPBGLRMATGraphSource.cxx
  vtkPBGLShortestPaths.cxx
  vtkPBGLVertexColoring.cxx
  )


vtk_module_library(vtkInfovisParallel ${Kit_SRCS})
