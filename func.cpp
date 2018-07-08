#include "func.h"

std::complex<double> quadFunc::compVal(std::complex<double> z) {
  return (z*z)+c;
}
std::pair<double, double> quadFunc::pairVal(std::pair<double, double> w) {
  return std::pair<double, double>{w.first*w.first-w.second*w.second+cX, 
      2*w.first*w.second+cY};
  }
