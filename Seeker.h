#include "Window.h"
#include "func.h"
#include <vector>
#include <iostream>

typedef std::vector<std::pair<int, int>> CycleT;

class Seeker {
 public:
  Seeker() {}
  void DefineWindow(double width, double height, double leftX, double lowerY, 
		    size_t xDiv, size_t yDiv);
  void ApplyFunction(func * function);
  std::vector<CycleT>& FindCycles();
    
 private:
  Window win;
  std::vector<CycleT> foundCoordinateCycles;
  func * F;
};

