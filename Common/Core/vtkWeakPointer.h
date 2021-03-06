/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkWeakPointer.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkWeakPointer - a weak reference to a vtkObject.
// .SECTION Description
// A weak reference to a vtkObject, which means that assigning
// a vtkObject to the vtkWeakPointer does not affect the reference count of the
// vtkObject. However, when the vtkObject is destroyed, the vtkWeakPointer gets
// initialized to NULL, thus avoiding any dangling references.
//
// \code
// vtkTable *table = vtkTable::New();
// vtkWeakPointer<vtkTable> weakTable = table;
// \endcode
//
// Some time later the table may be deleted, but if it is tested for null then
// the weak pointer will not leave a dangling pointer.
//
// \code
// table->Delete();
// if (weakTable)
//   {
//   // Never executed as the weak table pointer will be null here
//   cout << "Number of columns in table: " << weakTable->GetNumberOfColumns()
//        << endl;
//   }
// \endcode

#ifndef __vtkWeakPointer_h
#define __vtkWeakPointer_h

#include "vtkCommonCoreExport.h" // For export macro
#include "vtkWeakPointerBase.h"

template <class T>
class vtkWeakPointer: public vtkWeakPointerBase
{
public:
  // Description:
  // Initialize smart pointer to NULL.
  vtkWeakPointer() {}

  // Description:
  // Initialize smart pointer to given object.
  vtkWeakPointer(T* r): vtkWeakPointerBase(r) {}

  // Description:
  // Initialize smart pointer with the given smart pointer.
  vtkWeakPointer(const vtkWeakPointerBase& r): vtkWeakPointerBase(r) {}

  // Description:
  // Assign object to reference.
  vtkWeakPointer& operator=(T* r)
    {
    this->vtkWeakPointerBase::operator=(r);
    return *this;
    }

  // Description:
  // Assign object to reference.
  vtkWeakPointer& operator=(const vtkWeakPointerBase& r)
    {
    this->vtkWeakPointerBase::operator=(r);
    return *this;
    }

  // Description:
  // Get the contained pointer.
  T* GetPointer() const
    {
    return static_cast<T*>(this->Object);
    }

  // Description:
  // Get the contained pointer.
  operator T* () const
    {
    return static_cast<T*>(this->Object);
    }

  // Description:
  // Dereference the pointer and return a reference to the contained
  // object.
  T& operator*() const
    {
    return *static_cast<T*>(this->Object);
    }

  // Description:
  // Provides normal pointer target member access using operator ->.
  T* operator->() const
    {
    return static_cast<T*>(this->Object);
    }

  // Work-around for HP and IBM overload resolution bug.  Since
  // NullPointerOnly is a private type the only pointer value that can
  // be passed by user code is a null pointer.  This operator will be
  // chosen by the compiler when comparing against null explicitly and
  // avoid the bogus ambiguous overload error.
#if defined(__HP_aCC) || defined(__IBMCPP__)
# define VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(op) \
  vtkstd_bool operator op (NullPointerOnly*) const        \
    {                                                     \
    return ::operator op (*this, 0);                      \
    }
private:
  class NullPointerOnly {};
public:
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(==)
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(!=)
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(<)
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(<=)
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(>)
  VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND(>=)
# undef VTK_WEAK_POINTER_DEFINE_OPERATOR_WORKAROUND
#endif
protected:
  vtkWeakPointer(T* r, const NoReference& n): vtkWeakPointerBase(r, n) {}
private:
  // These are purposely not implemented to prevent callers from
  // trying to take references from other smart pointers.
  void TakeReference(const vtkWeakPointerBase&);  // Not implemented.
  static void Take(const vtkWeakPointerBase&);  // Not implemented.
};

#define VTK_WEAK_POINTER_DEFINE_OPERATOR(op) \
  template <class T> \
  inline vtkstd_bool \
  operator op (const vtkWeakPointer<T>& l, const vtkWeakPointer<T>& r) \
    { \
    return (l.GetPointer() op r.GetPointer()); \
    } \
  template <class T> \
  inline vtkstd_bool operator op (T* l, const vtkWeakPointer<T>& r) \
    { \
    return (l op r.GetPointer()); \
    } \
  template <class T> \
  inline vtkstd_bool operator op (const vtkWeakPointer<T>& l, T* r) \
    { \
    return (l.GetPointer() op r); \
    }
// Description:
// Compare smart pointer values.
VTK_WEAK_POINTER_DEFINE_OPERATOR(==)
VTK_WEAK_POINTER_DEFINE_OPERATOR(!=)
VTK_WEAK_POINTER_DEFINE_OPERATOR(<)
VTK_WEAK_POINTER_DEFINE_OPERATOR(<=)
VTK_WEAK_POINTER_DEFINE_OPERATOR(>)
VTK_WEAK_POINTER_DEFINE_OPERATOR(>=)

#undef VTK_WEAK_POINTER_DEFINE_OPERATOR

// Description:
// Streaming operator to print smart pointer like regular pointers.
template <class T>
inline ostream& operator << (ostream& os, const vtkWeakPointer<T>& p)
{
  return os << static_cast<const vtkWeakPointerBase&>(p);
}


#endif


