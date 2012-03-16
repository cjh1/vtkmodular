/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkOpenGLContextDevice3D.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// .NAME vtkOpenGLContextDevice3D - OpenGL class drawing 3D primitives.
//
// .SECTION Description
// This defines the implementation of a 3D context device for drawing simple
// primitives.

#ifndef __vtkOpenGLContextDevice3D_h
#define __vtkOpenGLContextDevice3D_h

#include "vtkRenderingContext2DExport.h" // For export macro
#include "vtkContextDevice3D.h"
#include "vtkNew.h"             // For ivars.

class vtkBrush;
class vtkPen;
class vtkRenderer;

class VTKRENDERINGCONTEXT2D_EXPORT vtkOpenGLContextDevice3D : public vtkContextDevice3D
{
public:
  vtkTypeMacro(vtkOpenGLContextDevice3D, vtkContextDevice3D);
  void PrintSelf(ostream &os, vtkIndent indent);

  static vtkOpenGLContextDevice3D * New();

  // Description:
  // Draw a polyline between the specified points.
  void DrawPoly(const float *verts, int n, const unsigned char *colors, int nc);

  // Description:
  // Draw points at the vertex positions specified.
  void DrawPoints(const float *verts, int n, const unsigned char *colors, int nc);

  // Description:
  // Apply the supplied pen which controls the outlines of shapes, as well as
  // lines, points and related primitives. This makes a deep copy of the vtkPen
  // object in the vtkContext2D, it does not hold a pointer to the supplied object.
  void ApplyPen(vtkPen *pen);

  // Description:
  // Apply the supplied brush which controls the outlines of shapes, as well as
  // lines, points and related primitives. This makes a deep copy of the vtkBrush
  // object in the vtkContext2D, it does not hold a pointer to the supplied object.
  void ApplyBrush(vtkBrush *brush);

  // Description:
  // Set the model view matrix for the display
  void SetMatrix(vtkMatrix4x4 *m);

  // Description:
  // Set the model view matrix for the display
  void GetMatrix(vtkMatrix4x4 *m);

  // Description:
  // Multiply the current model view matrix by the supplied one
  void MultiplyMatrix(vtkMatrix4x4 *m);

  // Description:
  // Push the current matrix onto the stack.
  void PushMatrix();

  // Description:
  // Pop the current matrix off of the stack.
  void PopMatrix();

  // Description:
  // Supply a float array of length 4 with x1, y1, width, height specifying
  // clipping region for the device in pixels.
  void SetClipping(const vtkRecti &rect);

  // Description:
  // Enable or disable the clipping of the scene.
  void EnableClipping(bool enable);

  // Description:
  // Begin drawing, pass in the viewport to set up the view.
  virtual void Begin(vtkViewport*);

  // Description:
  // End drawing, clean up the view.
  virtual void End();

protected:
  vtkOpenGLContextDevice3D();
  ~vtkOpenGLContextDevice3D();

  // Description:
  // We need to store a pointer to the renderer for the text rendering
  vtkRenderer *Renderer;

  bool InRender;

private:
  vtkOpenGLContextDevice3D(const vtkOpenGLContextDevice3D &); // Not implemented.
  void operator=(const vtkOpenGLContextDevice3D &);   // Not implemented.

  // Description:
  // Private data pointer of the class
  class Private;
  Private *Storage;

  vtkNew<vtkBrush> Brush;
  vtkNew<vtkPen>   Pen;
};

#endif
