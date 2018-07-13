#include <iostream>
#include "Window.h"
#include "func.h"

using namespace std;

typedef vector<pair<int, int>> CycleT;

void ClipCycle(CycleT & cycle) {
  auto last = cycle[cycle.size()-1];
  CycleT::iterator index = cycle.begin();
  while(*index != last) {
    ++index;
  }
  cycle.erase(cycle.begin(), --index);
  return; 
}

void ColorCurrentCycle(CycleT cycle, Window win, int color) {
  for(auto x : cycle) {
    win.SetCycleLabelAt(x, color);
  }
}

void MakeDead(const CycleT & cycle, Window & win) {
  for(auto x : cycle) {
    win.KillCellAt(x);
  }
  return;
}

int main(){
  
  Window win(4, 4, -2, -2, 20, 20);
  quadFunc function = quadFunc(0.5);
  win.ApplyFunction(&function);

  vector<CycleT> cycles;

  int currentColor = 0;
  pair<int, int> currentPair;

  pair<int, int> cellAddress;
  for(size_t rows = 0; rows < win.GetXDiv(); ++rows){
    for(size_t cols = 0; cols < win.GetYDiv(); ++cols){
      cellAddress = make_pair(rows, cols);
      cout << "**** Next Cycle:  \nStarting on cell ";
      printPair(cellAddress);
      cout << endl;
      CycleT currentCycle;
      while(win.CellAliveAt(cellAddress) and  
	    win.GetCycleLabelAt(cellAddress) == -1) {
	// While not yet colored
	currentCycle.push_back(cellAddress);
	win.SetCycleLabelAt(cellAddress, currentColor);
	cellAddress = win.GetConnectionAt(cellAddress, 0);
	cout << "Got next connection:";
	printPair(cellAddress);
	cout << endl;
      }
      // Either exited because we hit a dead cell or hit color
      if(win.GetCycleLabelAt(cellAddress) == currentColor) {
	// We found a loop!
	cout << "*** \t Loop Detected" << endl;
	ClipCycle(currentCycle);
	cout << "Clipped" << endl;
	ColorCurrentCycle(currentCycle, win, currentColor);
	cout << "Recolored" << endl;
	cycles.push_back(currentCycle);
	cout << "Stored" << endl;
      } else {
	// Otherwise exited for dead cell, OR finding another color
	// already visited.
	cout << "Killing...";
	MakeDead(currentCycle, win);
	cout << " DEAD." << endl;
      }
      currentColor++;
    }

  }
  
  cout << "Found " << cycles.size() << " cycles:" << endl;
  int count = 1;
  for(auto cyc : cycles) {
    cout << "Cycle " << count++ << ':' << endl;
    for(auto point : cyc) {
      cout << '\t';
      printPair(point);
      cout << "\tCoordinates: ";
      printPair(win.GetCoordinatesFromIndex(point.first, point.second));
      cout << endl;
    }
    cout << endl;
  }

  return 0;
}
