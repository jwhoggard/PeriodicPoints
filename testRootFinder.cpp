#include <iostream>
#include <complex>
#include "RootFinder.h"

using namespace std;

complex<double> f(complex<double> z) {
  return z*z + complex<double>(1, 0);
}

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
    rf.SetFunction(f);
    if(rf.FindRoot()) {
      cout << "Approximate root: " << rf.GetResult() << endl;
    } else {
      cout << "Failed to converge." << endl;
    }
  }

  return 0;
}
