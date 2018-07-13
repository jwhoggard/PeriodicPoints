#include "Window.h"
#include <iostream>

using namespace std;

int main() {

  int x, y;
  cout << "Coords for cell: ";
  cin >> x >> y;
  Cell test(x, y);
  cout << "Coords to add: ";
  while(cin >> x) {
    cin >> y;
    test.AddConnection(pair<int, int>{x, y});
    cout << "Now " << test.GetNumConnections() << " connections: ";
    for(int i = 0; i < test.GetNumConnections(); ++i) {
      printPair(test.GetConnection(i));
      cout << ' ';
    }
    cout << endl << "Coords to add: ";
  }

  return 0;
}
