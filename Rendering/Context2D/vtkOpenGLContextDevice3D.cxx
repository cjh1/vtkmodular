/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkOpenGLContextDevice3D.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkOpenGLContextDevice3D.h"

#include "vtkBrush.h"
#include "vtkPen.h"

#include "vtkMatrix4x4.h"
#include "vtkOpenGLRenderer.h"
#include "vtkOpenGLRenderWindow.h"
#include "vtkOpenGLExtensionManager.h"
#include "vtkgl.h"

#include "vtkObjectFactory.h"

class vtkOpenGLContextDevice3D::Private
{
public:
  Private()
  {
    this->SavedLighting = GL_TRUE;
    this->SavedDepthTest = GL_TRUE;
  }

  ~Private()
  {
  }

  void SaveGLState()
  {
    this->SavedLighting = glIsEnabled(GL_LIGHTING);
    this->SavedDepthTest = glIsEnabled(GL_DEPTH_TEST);
    this->SavedBlending = glIsEnabled(GL_BLEND);
  }

  void RestoreGLState()
  {
    this->SetGLCapability(GL_LIGHTING, this->SavedLighting);
    this->SetGLCapability(GL_DEPTH_TEST, this->SavedDepthTest);
    this->SetGLCapability(GL_BLEND, this->SavedBlending);
  }

  void SetGLCapability(GLenum capability, GLboolean state)
  {
    if (state)
      {
      glEnable(capability);
      }
    else
      {
      glDisable(capability);
      }
  }

  void Transpose(double *in, double *transposed)
  {
    transposed[0] = in[0];
    transposed[1] = in[4];
    transposed[2] = in[8];
    transposed[3] = in[12];

    transposed[4] = in[1];
    transposed[5] = in[5];
    transposed[6] = in[9];
    transposed[7] = in[13];

    transposed[8] = in[2];
    transposed[9] = in[6];
    transposed[10] = in[10];
    transposed[11] = in[14];

    transposed[12] = in[3];
    transposed[13] = in[7];
    transposed[14] = in[11];
    transposed[15] = in[15];
  }

  void SetLineType(int type)
  {
    if (type == vtkPen::SOLID_LINE)
      {
      glDisable(GL_LINE_STIPPLE);
      }
    else
      {
      glEnable(GL_LINE_STIPPLE);
      }
    GLushort pattern = 0x0000;
    switch (type)
      {
      case vtkPen::NO_PEN:
        pattern = 0x0000;
        break;
      case vtkPen::DASH_LINE:
        pattern = 0x00FF;
        break;
      case vtkPen::DOT_LINE:
        pattern = 0x0101;
        break;
      case vtkPen::DASH_DOT_LINE:
        pattern = 0x0C0F;
        break;
      case vtkPen::DASH_DOT_DOT_LINE:
        pattern = 0x1C47;
        break;
      default:
        pattern = 0x0000;
      }
    glLineStipple(1, pattern);
  }

  // Store the previous GL state so that we can restore it when complete
  GLboolean SavedLighting;
  GLboolean SavedDepthTest;
  GLboolean SavedBlending;

  vtkVector2i Dim;
  vtkVector2i Offset;
};

vtkStandardNewMacro(vtkOpenGLContextDevice3D)

vtkOpenGLContextDevice3D::vtkOpenGLContextDevice3D() : Storage(new Private)
{
  this->InRender = false;
}

vtkOpenGLContextDevice3D::~vtkOpenGLContextDevice3D()
{
  delete Storage;
}

void vtkOpenGLContextDevice3D::DrawPoly(const float *verts, int n,
                                        const unsigned char *colors, int nc)
{
  assert("verts must be non-null" && verts != NULL);
  assert("n must be greater than 0" && n > 0);

  this->Storage->SetLineType(this->Pen->GetLineType());
  glLineWidth(this->Pen->GetWidth());

  if (colors)
    {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(nc, GL_UNSIGNED_BYTE, 0, colors);
    }
  else
    {
    glColor4ubv(this->Pen->GetColor());
    }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, verts);
  glDrawArrays(GL_LINE_STRIP, 0, n);
  glDisableClientState(GL_VERTEX_ARRAY);
  if (colors)
    {
    glDisableClientState(GL_COLOR_ARRAY);
    }
}

void vtkOpenGLContextDevice3D::DrawPoints(const float *verts, int n,
                                          const unsigned char *colors, int nc)
{
  assert("verts must be non-null" && verts != NULL);
  assert("n must be greater than 0" && n > 0);

  glPointSize(this->Pen->GetWidth());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (colors && nc)
    {
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(nc, GL_UNSIGNED_BYTE, 0, colors);
    }
  else
    {
    glColor4ubv(this->Pen->GetColor());
    }
  glVertexPointer(3, GL_FLOAT, 0, verts);
  glDrawArrays(GL_POINTS, 0, n);
  glDisableClientState(GL_VERTEX_ARRAY);
  if (colors && nc)
    {
    glDisableClientState(GL_COLOR_ARRAY);
    }
}

void vtkOpenGLContextDevice3D::ApplyPen(vtkPen *pen)
{
  this->Pen->DeepCopy(pen);
}

void vtkOpenGLContextDevice3D::ApplyBrush(vtkBrush *brush)
{
  this->Brush->DeepCopy(brush);
}

void vtkOpenGLContextDevice3D::SetMatrix(vtkMatrix4x4 *m)
{
  double matrix[16];
  double *M = m->Element[0];
  this->Storage->Transpose(M, matrix);

  glLoadMatrixd(matrix);
}

void vtkOpenGLContextDevice3D::GetMatrix(vtkMatrix4x4 *m)
{
  double *M = m->Element[0];
  m->Transpose();
  double matrix[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
  this->Storage->Transpose(M, matrix);
}

void vtkOpenGLContextDevice3D::MultiplyMatrix(vtkMatrix4x4 *m)
{
  double matrix[16];
  double *M = m->Element[0];
  this->Storage->Transpose(M, matrix);

  glMultMatrixd(matrix);
}

void vtkOpenGLContextDevice3D::PushMatrix()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
}

void vtkOpenGLContextDevice3D::PopMatrix()
{
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void vtkOpenGLContextDevice3D::SetClipping(const vtkRecti &rect)
{
  // Check the bounds, and clamp if necessary
  GLint vp[4] = { this->Storage->Offset.GetX(), this->Storage->Offset.GetY(),
                  this->Storage->Dim.GetX(), this->Storage->Dim.GetY()};

  if (rect.X() > 0 && rect.X() < vp[2] )
    {
    vp[0] += rect.X();
    }
  if (rect.Y() > 0 && rect.Y() < vp[3])
    {
    vp[1] += rect.Y();
    }
  if (rect.Width() > 0 && rect.Width() < vp[2])
    {
    vp[2] = rect.Width();
    }
  if (rect.Height() > 0 && rect.Height() < vp[3])
    {
    vp[3] = rect.Height();
    }

  glScissor(vp[0], vp[1], vp[2], vp[3]);
}

void vtkOpenGLContextDevice3D::EnableClipping(bool enable)
{
  if (enable)
    {
    glEnable(GL_SCISSOR_TEST);
    }
  else
    {
    glDisable(GL_SCISSOR_TEST);
    }
}

void vtkOpenGLContextDevice3D::Begin(vtkViewport* viewport)
{
  // Need the actual pixel size of the viewport - ask OpenGL.
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  this->Storage->Offset.Set(static_cast<int>(vp[0]),
                            static_cast<int>(vp[1]));

  this->Storage->Dim.Set(static_cast<int>(vp[2]),
                         static_cast<int>(vp[3]));

  // push a 2D matrix on the stack
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  float offset = 0.5;
  glOrtho(offset, vp[2]+offset-1.0,
          offset, vp[3]+offset-1.0,
          -1000, 1000);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Store the previous state before changing it
  this->Storage->SaveGLState();
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  this->Renderer = vtkRenderer::SafeDownCast(viewport);

  this->InRender = true;
}

void vtkOpenGLContextDevice3D::End()
{
  if (!this->InRender)
    {
    return;
    }

  // push a 2D matrix on the stack
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  // Restore the GL state that we changed
  this->Storage->RestoreGLState();

  this->InRender = false;
}

void vtkOpenGLContextDevice3D::PrintSelf(ostream &os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
}
