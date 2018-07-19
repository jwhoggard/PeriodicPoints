#include "Window.h"
#include "func.h"
#include "RootFinder.h"
#include <vector>
#include <iostream>
#include <complex>

// A cycle of points, defined in terms of grid coordinates
typedef std::vector<std::pair<int, int>> CycleT;
typedef std::vector<std::complex<double>> ComplexCycleT;
struct IndexedCycle {
  int cycleLength;
  double firstX;
  double firstY;
  ComplexCycleT points;
};

class Seeker {
 public:
  Seeker() {}
  void DefineWindow(double width, double height, double leftX, double lowerY, 
		    size_t xDiv, size_t yDiv);
  void ApplyFunction(func * f);
  void FindCycles();
  void SetEpsilon(double eps);
  
  void RefineCycles();
    
 private:
  Window win;
  std::vector<CycleT> foundCoordinateCycles;
  std::vector<IndexedCycle> cycleIndex;
  //std::function<std::complex<double>(std::complex<double>)> F;
  func * F;

  // Helper functions
  void ClipCycle(CycleT & cycle);
  void ColorCurrentCycle(CycleT cycle, int color);
  void MakeDead(const CycleT & cycle);
  //  std::complex<double> FCycleIdentity(std::complex<double> z, int n);

  // The root finder
  RootFinder rf;
  double epsilon;
};

