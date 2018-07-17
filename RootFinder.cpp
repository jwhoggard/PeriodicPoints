#include "RootFinder.h"
#include <iostream>

using namespace std;

void PrintStatus(int it, complex<double> z, complex<double> z2){
  cout << "Iter: " << it;
  cout << "  z = " << z;
  cout << "  z2 = " << z2 << endl;
}

bool RootFinder::FindRoot() {
  int iter = 0;
  z = start;
  complex<double> z2 = start + .0001;
  complex<double> temp;
  while(abs(f(z)) >= eps and iter++ < maxIter
	and (abs(f(z)-f(z2))> 1e-10)) {
    temp = z;
    z = z - f(z)*(z-z2)/(f(z)-f(z2));
    z2 = temp;
    PrintStatus(iter, z, z2);
  }
  if(abs(f(z)) < eps) {
    found = true;
  }
  return found;
}

/*
complex<double> RootFinder::f(complex<double> w) {
  return w*w + complex<double>(1, 0);
}
*/


