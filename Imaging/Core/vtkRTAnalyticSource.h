/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRTAnalyticSource.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkRTAnalyticSource - Create an image for regression testing
// .SECTION Description
// vtkRTAnalyticSource just produces images with pixel values determined 
// by a Maximum*Gaussian*XMag*sin(XFreq*x)*sin(YFreq*y)*cos(ZFreq*z)
// Values are float scalars on point data with name "RTData".

#ifndef __vtkRTAnalyticSource_h
#define __vtkRTAnalyticSource_h

#include "vtkImagingCoreExport.h" // For export macro
#include "vtkImageAlgorithm.h"

class VTKIMAGINGCORE_EXPORT vtkRTAnalyticSource : public vtkImageAlgorithm
{
public:
  static vtkRTAnalyticSource *New();
  vtkTypeMacro(vtkRTAnalyticSource,vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set/Get the extent of the whole output image. Initial value is
  // {-10,10,-10,10,-10,10}
  void SetWholeExtent(int xMinx, int xMax, int yMin, int yMax,
                      int zMin, int zMax);
  vtkGetVector6Macro(WholeExtent, int);
  
  // Description:
  // Set/Get the center of function. Initial value is {0.0,0.0,0.0}
  vtkSetVector3Macro(Center, double);
  vtkGetVector3Macro(Center, double);

  // Description:
  // Set/Get the Maximum value of the function. Initial value is 255.0.
  vtkSetMacro(Maximum, double);
  vtkGetMacro(Maximum, double);

  // Description:
  // Set/Get the standard deviation of the function. Initial value is 0.5.
  vtkSetMacro(StandardDeviation, double);
  vtkGetMacro(StandardDeviation, double);

  // Description:
  // Set/Get the natural frequency in x. Initial value is 60.
  vtkSetMacro(XFreq, double);
  vtkGetMacro(XFreq, double);

  // Description:
  // Set/Get the natural frequency in y. Initial value is 30.
  vtkSetMacro(YFreq, double);
  vtkGetMacro(YFreq, double);

  // Description:
  // Set/Get the natural frequency in z. Initial value is 40.
  vtkSetMacro(ZFreq, double);
  vtkGetMacro(ZFreq, double);

  // Description:
  // Set/Get the magnitude in x. Initial value is 10.
  vtkSetMacro(XMag, double);
  vtkGetMacro(XMag, double);

  // Description:
  // Set/Get the magnitude in y. Initial value is 18.
  vtkSetMacro(YMag, double);
  vtkGetMacro(YMag, double);

  // Description:
  // Set/Get the magnitude in z. Initial value is 5.
  vtkSetMacro(ZMag, double);
  vtkGetMacro(ZMag, double);

  // Description:
  // Set/Get the sub-sample rate. Initial value is 1.
  vtkSetMacro(SubsampleRate, int);
  vtkGetMacro(SubsampleRate, int);

protected:
  // Description:
  // Default constructor. Initial values are:
  // Maximum=255.0, Center[3]={0.0,0.0,0.0}, WholeExtent={-10,10,-10,10,-10,10}
  // StandardDeviation=0.5, XFreq=60, XMag=10, YFreq=30, YMag=18, ZFreq=40,
  // ZMag=5, SubsampleRate=1
  vtkRTAnalyticSource();

  // Description:
  // Destructor.
  ~vtkRTAnalyticSource()
    {
    }

  double XFreq;
  double YFreq;
  double ZFreq;
  double XMag;
  double YMag;
  double ZMag;
  double StandardDeviation;
  int WholeExtent[6];
  double Center[3];
  double Maximum;
  int SubsampleRate;

  virtual int RequestInformation(vtkInformation *request,
                                 vtkInformationVector **inputVector,
                                 vtkInformationVector *outputVector);
  virtual void ExecuteData(vtkDataObject *data, vtkInformation *outInfo);
private:
  vtkRTAnalyticSource(const vtkRTAnalyticSource&);  // Not implemented.
  void operator=(const vtkRTAnalyticSource&);  // Not implemented.
};


#endif
