
SET(Kit_SRCS
  vtkAbstractTransform.cxx
  vtkCylindricalTransform.cxx
  vtkGeneralTransform.cxx
  vtkHomogeneousTransform.cxx
  vtkIdentityTransform.cxx
  vtkLinearTransform.cxx
  vtkMatrixToHomogeneousTransform.cxx
  vtkMatrixToLinearTransform.cxx
  vtkPerspectiveTransform.cxx
  vtkSphericalTransform.cxx
  vtkThinPlateSplineTransform.cxx
  vtkTransform2D.cxx
  vtkTransformCollection.cxx
  vtkTransform.cxx
  vtkWarpTransform.cxx
  vtkLandmarkTransform.cxx
  )

vtk_add_library(vtkCommonTransforms ${Kit_SRCS})
