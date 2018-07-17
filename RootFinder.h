#include "func.h"
#include <complex>

class RootFinder {
 public:
 RootFinder() : found(false), eps(1e-8), maxIter(25) {};
  void SetStart(std::complex<double> w) {start = w;}
  void SetEpsilon(double e) {eps = e;}
  //  void SetFunction(func * function) {F = function;}
  std::complex<double> GetResult() {return z;}
  void SetMaxIterations(int max) {maxIter = max;}
  void SetFunction(std::complex<double> (*F)(std::complex<double>)) {f = F;}
  bool FindRoot();
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
  // Pointer to function
  std::complex<double> (*f)(std::complex<double> z);
};
