#include "Window.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  
  Window w;

  cout << "Defaults:" << endl;
  cout << '\t' << "Left:   " << w.GetLeftX() << endl;
  cout << '\t' << "Width:  " << w.GetWidth() << endl;
  cout << '\t' << "Bot:    " << w.GetLowerY() << endl;
  cout << '\t' << "Height: " << w.GetHeight() << endl;
  cout << '\t' << "X divs: " << w.GetXDiv() << endl;
  cout << '\t' << "Y divs: " << w.GetYDiv() << endl;

  cout << endl << endl;
  cout << "Enter a pair of (x, y) coordinates in the plane: "<< endl;
  double x, y;
  cin >> x >> y;
  pair<int, int> result;
  result = w.GetIndexFromCoordinates(x, y);
  cout << "Pair is in cell (" << result.first << ", " << result.second;
  cout << ")." << endl;

  return 0;
}
