#include <iostream>
#include <iomanip>
#include "func.h"

using namespace std;

int main() {
  complex<double> c, z;
  double x, y;
  pair<double, double> zp;
  pair<double, double> cp;

  cout << "Constant x y coords: " << endl;
  cout << "\t";
  cin >> x >> y;
  //  c = complex<double>{x, y};
  cp = make_pair(x, y);
  quadFunc f = quadFunc(cp);

  cout << fixed;
  cout << "x y coords:" << endl;
  while( cin>> x) {
    cin >> y;
    // z = complex<double>{x, y};
    zp = make_pair(x, y);
    zp = f.pairVal(zp);
    cout << "z^2 = " << zp.first << " + " << zp.second << "i" << endl;
    cout << endl;
  }

  return 0;
}
