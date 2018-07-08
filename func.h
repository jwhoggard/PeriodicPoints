#include <complex>

class func {
 public:
  virtual std::complex<double> compVal(std::complex<double> z) = 0;
  virtual std::pair<double, double> pairVal(std::pair<double, double>)=0;
 private:
};

class quadFunc : public func {
 public:
 quadFunc(std::complex<double> z) : c(z) {cX = z.real(); cY = z.imag();}
 quadFunc(std::pair<double, double> w) : cX(w.first), cY(w.second), c(std::complex<double>{w.first, w.second}) {}

  std::complex<double> compVal(std::complex<double> z);
  std::pair<double, double> pairVal(std::pair<double, double>);
  
 private:
  double cX;
  double cY;
  std::complex<double> c;
};
