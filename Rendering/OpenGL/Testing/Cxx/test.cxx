#include "vtkActor.h"
#include "vtkNew.h"

int main()
{
  vtkNew<vtkActor> actor;
  cout << "Actor class: " << actor->GetClassName() << endl;
  return 0;
}
