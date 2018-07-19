#include "func.h"
#include <complex>
#include <functional>

// Initial perturbation; take second point to be first + PERTURBATION
// to start secant method.
const double PERTURBATION = .0001;
// Point of problem if consecutive outputs get this close.
const double ALMOST_ZERO = 1e-12;

class RootFinder {
 public:
 RootFinder() : found(false), eps(1e-8), maxIter(25) {};
  void SetStart(std::complex<double> w) {start = w;}
  void SetEpsilon(double e); 
  std::complex<double> GetResult() {return z;}
  void SetMaxIterations(int max) {maxIter = max;}
  //  void SetFunction(std::complex<double> (*F)(std::complex<double>)) {f = F;}
  void SetFunction(std::function<std::complex<double>(std::complex<double>)> func) 
  {f = func;}
  bool FindRoot();
  bool FindNCycle(int n);
 private:
  // Start with a built-in function to figure out root finding.
  // std::complex<double> f(std::complex<double>);
  // Starting point
  std::complex<double> start;
  // Current/final z
  std::complex<double> z;
  // Have we converged?  False by default
  bool found;
  // Tolerance (1e-8 by default)
  double eps;
  // Maximum number of iterations (25 by default)
  int maxIter;
  // Pointer to function replaced with function (callable object)
  //  std::complex<double> (*f)(std::complex<double> z);
  std::function<std::complex<double>(std::complex<double>)> f;
  //  std::complex<double> FNIterate(std::complex<double> u, int n);
};
