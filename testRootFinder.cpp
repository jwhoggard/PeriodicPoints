#include <iostream>
#include <complex>
#include "RootFinder.h"

using namespace std;

int main(){
  RootFinder rf;

  double tol;
  int maxIt;
  complex<double> start;

  cout << "Start (real, imag): ";
  while(cin >> start) {
    rf.SetStart(start);
    cout << "Tolerance: ";
    cin >> tol;
    rf.SetEpsilon(tol);
    cout << "Max iterations: ";
    cin >> maxIt;
    rf.SetMaxIterations(maxIt);
    if(rf.FindRoot()) {
      cout << "Approximate root: " << rf.GetResult() << endl;
    } else {
      cout << "Failed to converge." << endl;
    }
  }

  return 0;
}
