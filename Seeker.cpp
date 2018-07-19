#include "Seeker.h"
#include <functional>

using namespace std;

void Seeker::DefineWindow(double width, double height, double leftX, double lowerY,
			  size_t xDiv, size_t yDiv) {
  win.SetValues(width, height, leftX, lowerY, xDiv, yDiv);
  return;
}

void Seeker::ApplyFunction(func * f) {
  F = f;
  win.ApplyFunction(f);
  return;
}

void Seeker::FindCycles() {
  int currentColor = 0;
  pair<int, int> currentPair;

  pair<int, int> cellAddress;
  for(size_t rows = 0; rows < win.GetXDiv(); ++rows){
    for(size_t cols = 0; cols < win.GetYDiv(); ++cols){
      cellAddress = make_pair(rows, cols);
      CycleT currentCycle;
      while(win.CellAliveAt(cellAddress) and  
	    win.GetCycleLabelAt(cellAddress) == -1) {
	// While not yet colored
	currentCycle.push_back(cellAddress);
	win.SetCycleLabelAt(cellAddress, currentColor);
	cellAddress = win.GetConnectionAt(cellAddress, 0);
      }
      // Either exited because we hit a dead cell or hit color
      if(win.GetCycleLabelAt(cellAddress) == currentColor) {
	// We found a loop!
	ClipCycle(currentCycle);
	ColorCurrentCycle(currentCycle, currentColor);
	foundCoordinateCycles.push_back(currentCycle);
      } else {
	// Otherwise exited for dead cell, OR finding another color
	// already visited.
	MakeDead(currentCycle);
      }
      currentColor++;
    }
  }
}

void Seeker::ClipCycle(CycleT & cycle) {
  auto last = cycle[cycle.size()-1];
  CycleT::iterator index = cycle.begin();
  while(*index != last) {
    ++index;
  }
  cycle.erase(cycle.begin(), --index);
  return; 
}

void Seeker::ColorCurrentCycle(CycleT cycle, int color) {
  for(auto x : cycle) {
    win.SetCycleLabelAt(x, color);
  }
}

void Seeker::MakeDead(const CycleT & cycle) {
  for(auto x : cycle) {
    win.KillCellAt(x);
  }
  return;
}

void Seeker::SetEpsilon(double eps) {
  if(eps < ALMOST_ZERO) {
    epsilon = 2*ALMOST_ZERO;
  } else {
    epsilon = eps;
  }
  rf.SetEpsilon(epsilon);
}

/*
std::complex<double> Seeker::FCycleIdentity(complex<double> z, int n) {
  complex<double> w = z;
  for(int i = 0; i < n; ++i) {
    w = F->compVal(w);
  }
  return w - z;
}
*/

/*
  Take a CycleT of cycle of indices and attempt to use RootFinder to
  locate a valid cycle of complex points.

  For right now, just spit out all the cycles to stdout
 */
void Seeker::RefineCycles() {
  for (auto cycle : foundCoordinateCycles) {
    cout << "Starting to refine a cycle: " << endl;
    int cycleLength = cycle.size();
    // Set function to f^n(z) - z:
    rf.SetFunction([cycleLength, this](complex<double> z) {
	complex<double> oldz = z;
	for(int i = 0; i < cycleLength; ++i) {
	  z = (this->F)->compVal(z);
	}
	return z - oldz;
      });
    // First try:  Just try to refine each
    for(auto pointPair : cycle) {
      rf.SetStart(win.GetComplexFromIndexPair(pointPair));
      if(rf.FindRoot()) {
	cout << "Found cycle starting at " << rf.GetResult() << endl;
      } else {
	cout << "Failure to converge" << endl;
      }
    }
  }
}

