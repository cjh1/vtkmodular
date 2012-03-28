set(Kit_SRCS
  vtkComputeHistogram2DOutliers.cxx
  vtkDiagonalMatrixSource.cxx
  vtkDotProductSimilarity.cxx
  vtkExtractArray.cxx
  vtkExtractHistogram2D.cxx
  vtkMatricizeArray.cxx
  vtkNormalizeMatrixVectors.cxx
  vtkPairwiseExtractHistogram2D.cxx
  vtkPassArrays.cxx
  vtkPBivariateLinearTableThreshold.cxx
  vtkPComputeHistogram2DOutliers.cxx
  vtkPExtractHistogram2D.cxx
  vtkPPairwiseExtractHistogram2D.cxx
  vtkRemoveHiddenData.cxx
  vtkSplitColumnComponents.cxx
  vtkTransferAttributes.cxx
  )

vtk_module_library(vtkInfovisNeedAHome ${Kit_SRCS})
