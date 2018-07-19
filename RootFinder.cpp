#include "RootFinder.h"
#include <iostream>

using namespace std;

const bool DEBUG = false;

void PrintStatus(int it, complex<double> z, complex<double> z2){
  if(DEBUG) {
  cout << "Iter: " << it;
  cout << "  z = " << z;
  cout << "  z2 = " << z2 << endl;
  }
  return;
}

void RootFinder::SetEpsilon(double e)  {
  if(e < ALMOST_ZERO) {
    eps = 2*ALMOST_ZERO;
    // cout << "Set epsilon" << endl;
    } else {
    eps = e;
  }
}


/*
  Actually find the root.  Uses a simple secant method, with a default
  perturbation of PERTURBATION from original.  

  Fails (leave found as false) if |f(z)| >= eps.  

  May fail if takes more than maxIter iterations, or if f at
  consecutive points <= ALMOST_ZERO.
*/
bool RootFinder::FindRoot() {
  int iter = 0;
  z = start;
  complex<double> z2 = start + PERTURBATION;
  complex<double> temp;
  while(abs(f(z)) >= eps and iter++ < maxIter
	and (abs(f(z)-f(z2))> ALMOST_ZERO)) {
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
complex<double> RootFinder::FNIterate(complex<double> u, int n) {
  complex<double> w = u;
  for(int i = 0; i < n; ++i) {
    w = f(w);
  }
  return w - u;
}


bool RootFinder::FindNCycle(int n) {
  int iter = 0;
  z = start;
  complex<double> z2 = start + PERTURBATION;
  complex<double> temp;
  while(abs(FNIterate(z, n)) >= eps and iter++ < maxIter
	and (abs(FNIterate(z, n)-FNIterate(z2, n))> ALMOST_ZERO)) {
    temp = z;
    z = z - FNIterate(z,n)*(z-z2)/(FNIterate(z,n)-FNIterate(z2,n));
    z2 = temp;
    PrintStatus(iter, z, z2);
  }
  if(abs(FNIterate(z,n)) < eps) {
    found = true;
  }
  return found;
  
}
*/
