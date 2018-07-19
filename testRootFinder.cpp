#include <iostream>
#include <complex>
#include <functional>
#include "RootFinder.h"


using namespace std;

/* Obsolete:  Used for built-in f at first testing
complex<double> f(complex<double> z) {
  return z*z + complex<double>(1, 0);
}
*/

complex<double> fplain(complex<double> z) { return z*z + complex<double>{0.5, 0};}
complex<double> fiter(complex<double> z, int n) {
  complex<double> w = z;
  for(int i = 0; i<n; ++i) {
    w = fplain(w);
  }
  return w - z;
}

int main(){
  RootFinder rf;

  double tol;
  int maxIt;
  complex<double> start;
  int compTimes =2;
  cout << "Start (real, imag): ";
  while(cin >> start) {
    rf.SetStart(start);
    cout << "Tolerance: ";
    cin >> tol;
    rf.SetEpsilon(tol);
    cout << "Max iterations: ";
    cin >> maxIt;
    rf.SetMaxIterations(maxIt);
    //rf.SetFunction(f);
    // Now try a lambda:
    /*
    rf.SetFunction([](complex<double> z) {return z*z+complex<double>(1, 0);});
    if(rf.FindRoot()) {
      cout << "Approximate root: " << rf.GetResult() << endl;
    } else {
      cout << "Failed to converge." << endl;
    }
    */
    rf.SetFunction([compTimes](complex<double> z) {
	complex<double> w = z;
	for (int i = 0; i < compTimes; ++i){
	  w = fplain(w);
	}
	return w -z;
      }
      );
    if(rf.FindRoot()) {
      cout << "Approximate root: " << rf.GetResult() << endl;
    } else {
      cout << "Failed to converge." << endl;
    }
        
  }
  
  //  auto fff = bind(fiter, std::placeholders::_1, 2);
  //  rf.SetFunction([](complex<double> z) {return };
  return 0;
}
