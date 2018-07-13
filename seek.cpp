#include <iostream>
#include "Window.h"
#include "func.h"

using namespace std;

int main(){
  
  Window(4, 4, -2, -2, 20, 20, quadFunc(0));

  typedef vector<pair<int, int>> CycleT;
  vector<CycleT> cycles;

  // 

  return 0;
}
