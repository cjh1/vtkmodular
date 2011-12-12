/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkImageInterpolatorInternals.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkImageInterpolatorInternals - internals for vtkImageInterpolator

#ifndef __vtkImageInterpolatorInternals_h
#define __vtkImageInterpolatorInternals_h

#include "vtkMath.h"

// The interpolator info struct
struct vtkInterpolationInfo
{
  const void *Pointer;
  int Extent[6];
  vtkIdType Increments[3];
  int ScalarType;
  int NumberOfComponents;
  int BorderMode;
  int InterpolationMode;
  void *ExtraInfo;
};

// The interpolation weights struct
struct vtkInterpolationWeights : public vtkInterpolationInfo
{
  vtkIdType *Positions[3];
  void *Weights[3];
  int WeightExtent[6];
  int KernelSize[3];
  int WeightType; // VTK_FLOAT or VTK_DOUBLE

  // partial copy contstructor from superclass
  vtkInterpolationWeights(const vtkInterpolationInfo &info) :
    vtkInterpolationInfo(info) {}
};

//--------------------------------------------------------------------------
// Make all defined methods invisible outside current translation unit
namespace {

//--------------------------------------------------------------------------
// The 'floor' function is slow, so we want to do an integer
// cast but keep the "floor" behavior of always rounding down,
// rather than truncating, i.e. we want -0.6 to become -1.
// The easiest way to do this is to add a large value in
// order to make the value "unsigned", then cast to int, and
// then subtract off the large value.

// On the old i386 architecture even a cast to int is very
// expensive because it requires changing the rounding mode
// on the FPU.  So we use a bit-trick similar to the one
// described at http://www.stereopsis.com/FPU.html

#if defined ia64 || defined __ia64__ || defined _M_IA64
#define VTK_INTERPOLATE_64BIT_FLOOR
#elif defined __ppc64__ || defined __x86_64__ || defined _M_X64
#define VTK_INTERPOLATE_64BIT_FLOOR
#elif defined __ppc__ || defined sparc || defined mips
#define VTK_INTERPOLATE_32BIT_FLOOR
#elif defined i386 || defined _M_IX86
#define VTK_INTERPOLATE_I386_FLOOR
#endif

// We add a tolerance of 2^-17 (around 7.6e-6) so that float
// values that are just less than the closest integer are
// rounded up.  This adds robustness against rounding errors.

#define VTK_INTERPOLATE_FLOOR_TOL 7.62939453125e-06


template<class F>
inline int vtkInterpolateFloor(double x, F &f)
{
#if defined VTK_INTERPOLATE_64BIT_FLOOR
  x += (103079215104.0 + VTK_INTERPOLATE_FLOOR_TOL);
#ifdef VTK_TYPE_USE___INT64
  __int64 i = static_cast<__int64>(x);
  f = x - i;
  return static_cast<int>(i - 103079215104i64);
#else
  long long i = static_cast<long long>(x);
  f = x - i;
  return static_cast<int>(i - 103079215104LL);
#endif
#elif defined VTK_INTERPOLATE_32BIT_FLOOR
  x += (2147483648.0 + VTK_INTERPOLATE_FLOOR_TOL);
  unsigned int i = static_cast<unsigned int>(x);
  f = x - i;
  return static_cast<int>(i - 2147483648U);
#elif defined VTK_INTERPOLATE_I386_FLOOR
  union { double d; unsigned short s[4]; unsigned int i[2]; } dual;
  dual.d = x + 103079215104.0;  // (2**(52-16))*1.5
  f = dual.s[0]*0.0000152587890625; // 2**(-16)
  return static_cast<int>((dual.i[1]<<16)|((dual.i[0])>>16));
#else
  int i = vtkMath::Floor(x + VTK_INTERPOLATE_FLOOR_TOL);
  f = x - i;
  return i;
#endif
}


inline int vtkInterpolateRound(double x)
{
#if defined VTK_INTERPOLATE_64BIT_FLOOR
  x += (103079215104.5 + VTK_INTERPOLATE_FLOOR_TOL);
#ifdef VTK_TYPE_USE___INT64
  __int64 i = static_cast<__int64>(x);
  return static_cast<int>(i - 103079215104i64);
#else
  long long i = static_cast<long long>(x);
  return static_cast<int>(i - 103079215104LL);
#endif
#elif defined VTK_INTERPOLATE_32BIT_FLOOR
  x += (2147483648.5 + VTK_INTERPOLATE_FLOOR_TOL);
  unsigned int i = static_cast<unsigned int>(x);
  return static_cast<int>(i - 2147483648U);
#elif defined VTK_INTERPOLATE_I386_FLOOR
  union { double d; unsigned int i[2]; } dual;
  dual.d = x + 103079215104.5;  // (2**(52-16))*1.5
  return static_cast<int>((dual.i[1]<<16)|((dual.i[0])>>16));
#else
  return vtkMath::Floor(x + (0.5 + VTK_INTERPOLATE_FLOOR_TOL));
#endif
}

//----------------------------------------------------------------------------
// Perform a clamp to limit an index to [b, c] and subtract b.

inline int vtkInterpolateClamp(int a, int b, int c)
{
  a = (a <= c ? a : c);
  a -= b;
  a = (a >= 0 ? a : 0);
  return a;
}

//----------------------------------------------------------------------------
// Perform a wrap to limit an index to [b, c] and subtract b.

inline int vtkInterpolateWrap(int a, int b, int c)
{
  int range = c - b + 1;
  a -= b;
  a %= range;
  // required for some % implementations
  a = (a >= 0 ? a : a + range);
  return a;
}

//----------------------------------------------------------------------------
// Perform a mirror to limit an index to [b, c] and subtract b.

inline int vtkInterpolateMirror(int a, int b, int c)
{
  int range1 = c - b;
  int range = range1 + 1;
  a -= b;
  a = (a >= 0 ? a : -a - 1);
  int count = a/range;
  a -= count*range;
  a = ((count & 0x1) == 0 ? a : range1 - a);
  return a;
}

} // end anonymous namespace

#endif
