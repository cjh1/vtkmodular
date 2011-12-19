/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtk__Int64Array.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtk__Int64Array - dynamic, self-adjusting array of __int64
// .SECTION Description
// vtk__Int64Array is an array of values of type __int64.
// It provides methods for insertion and retrieval of values and will
// automatically resize itself to hold new data.

#ifndef __vtk__Int64Array_h
#define __vtk__Int64Array_h

// Tell the template header how to give our superclass a DLL interface.
#if !defined(__vtk__Int64Array_cxx)
# define VTK_DATA_ARRAY_TEMPLATE_TYPE __int64
#endif

#include "vtkCommonCoreExport.h" // For export macro
#include "vtkDataArray.h"
#include "vtkDataArrayTemplate.h" // Real Superclass

// Fake the superclass for the wrappers.
#define vtkDataArray vtkDataArrayTemplate<__int64>
class VTKCOMMONCORE_EXPORT vtk__Int64Array : public vtkDataArray
#undef vtkDataArray
{
public:
  static vtk__Int64Array* New();
  vtkTypeMacro(vtk__Int64Array,vtkDataArray);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Get the data type.
  int GetDataType()
    { return VTK___INT64; }

  // Description:
  // Copy the tuple value into a user-provided array.
  void GetTupleValue(vtkIdType i, __int64* tuple)
    { this->RealSuperclass::GetTupleValue(i, tuple); }

  // Description:
  // Set the tuple value at the ith location in the array.
  void SetTupleValue(vtkIdType i, const __int64* tuple)
    { this->RealSuperclass::SetTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple into the ith location
  // in the array.
  void InsertTupleValue(vtkIdType i, const __int64* tuple)
    { this->RealSuperclass::InsertTupleValue(i, tuple); }

  // Description:
  // Insert (memory allocation performed) the tuple onto the end of the array.
  vtkIdType InsertNextTupleValue(const __int64* tuple)
    { return this->RealSuperclass::InsertNextTupleValue(tuple); }

  // Description:
  // Get the data at a particular index.
  __int64 GetValue(vtkIdType id)
    { return this->RealSuperclass::GetValue(id); }

  // Description:
  // Set the data at a particular index. Does not do range checking. Make sure
  // you use the method SetNumberOfValues() before inserting data.
  void SetValue(vtkIdType id, __int64 value)
    { this->RealSuperclass::SetValue(id, value); }

  // Description:
  // Specify the number of values for this object to hold. Does an
  // allocation as well as setting the MaxId ivar. Used in conjunction with
  // SetValue() method for fast insertion.
  void SetNumberOfValues(vtkIdType number)
    { this->RealSuperclass::SetNumberOfValues(number); }

  // Description:
  // Insert data at a specified position in the array.
  void InsertValue(vtkIdType id, __int64 f)
    { this->RealSuperclass::InsertValue(id, f); }

  // Description:
  // Insert data at the end of the array. Return its location in the array.
  vtkIdType InsertNextValue(__int64 f)
    { return this->RealSuperclass::InsertNextValue(f); }

  // Description:
  // Get the range of array values for the given component in the
  // native data type.
  __int64 *GetValueRange(int comp)
    { return this->RealSuperclass::GetValueRange(comp); }
//BTX
  void GetValueRange(__int64 range[2], int comp)
    { this->RealSuperclass::GetValueRange(range, comp); }
//ETX

  // Description:
  // Get the range of array values for the 0th component in the
  // native data type.
  __int64 *GetValueRange()
    { return this->RealSuperclass::GetValueRange(0); }
//BTX
  void GetValueRange(__int64 range[2])
    { this->RealSuperclass::GetValueRange(range, 0); }
//ETX

  // Description:
  // Get the minimum data value in its native type.
  static __int64 GetDataTypeValueMin() { return VTK___INT64_MIN; }

  // Description:
  // Get the maximum data value in its native type.
  static __int64 GetDataTypeValueMax() { return VTK___INT64_MAX; }

  // Description:
  // Get the address of a particular data index. Make sure data is allocated
  // for the number of items requested. Set MaxId according to the number of
  // data values requested.
  __int64* WritePointer(vtkIdType id, vtkIdType number)
    { return this->RealSuperclass::WritePointer(id, number); }

  // Description:
  // Get the address of a particular data index. Performs no checks
  // to verify that the memory has been allocated etc.
  __int64* GetPointer(vtkIdType id)
    { return this->RealSuperclass::GetPointer(id); }

  // Description:
  // This method lets the user specify data to be held by the array.  The
  // array argument is a pointer to the data.  size is the size of
  // the array supplied by the user.  Set save to 1 to keep the class
  // from deleting the array when it cleans up or reallocates memory.
  // The class uses the actual array provided; it does not copy the data
  // from the suppled array.
  void SetArray(__int64* array, vtkIdType size, int save)
    { this->RealSuperclass::SetArray(array, size, save); }
  void SetArray(__int64* array, vtkIdType size, int save, int deleteMethod)
    { this->RealSuperclass::SetArray(array, size, save, deleteMethod); }

protected:
  vtk__Int64Array(vtkIdType numComp=1);
  ~vtk__Int64Array();

private:
  //BTX
  typedef vtkDataArrayTemplate<__int64> RealSuperclass;
  //ETX
  vtk__Int64Array(const vtk__Int64Array&);  // Not implemented.
  void operator=(const vtk__Int64Array&);  // Not implemented.
};

#endif