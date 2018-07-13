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
    test.connections.push_back(pair<int, int>{x, y});
    cout << "Now " << test.connections.size() << " connections: ";
    for(size_t i = 0; i < test.connections.size(); ++i) {
      printPair(test.connections[i]);
      cout << ' ';
    }
    cout << endl << "Coords to add: ";
  }

  return 0;
}
