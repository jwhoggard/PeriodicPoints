#include "Window.h"
#include <iostream>
#include <iomanip>

using namespace std;



int main() {
  
  Window w(4,4,-2,-2,4,4,quadFunc(.5));

  cout << "Defaults:" << endl;
  cout << '\t' << "Left:   " << w.GetLeftX() << endl;
  cout << '\t' << "Width:  " << w.GetWidth() << endl;
  cout << '\t' << "Bot:    " << w.GetLowerY() << endl;
  cout << '\t' << "Height: " << w.GetHeight() << endl;
  cout << '\t' << "X divs: " << w.GetXDiv() << endl;
  cout << '\t' << "Y divs: " << w.GetYDiv() << endl;

  cout << endl << endl;

  
  double x, y;
  cout << "Enter a pair of (x, y) coordinates in the plane: "<< endl;
  while(cin >> x) {
    cin >> y;
    pair<int, int> result;
    result = w.GetIndexFromCoordinates(x, y);
    cout << "Pair is in cell (" << result.first << ", " << result.second;
    cout << ")." << endl;
    cout << "And cell there reports i = ";
    cout << w.GetCellAt(result.first, result.second).GetX();
    cout << "; j = " << w.GetCellAt(result.first,result.second).GetY() << endl;
    cout << "And cell maps to cell coordinates (";
    Cell resCell = w.GetCellAt(result.first, result.second);
    result = resCell.GetConnection(0);
    cout << result.first << ", " << result.second << "); or approximately";
    cout << endl << "(" << setprecision(3) << fixed;
    result = w.GetCoordinatesFromIndex(result.first, result.second);
    cout << result.first << ", " << result.second << ")." << endl;
  }
  
  

  return 0;
}
