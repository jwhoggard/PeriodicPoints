#include <iostream>
#include "Seeker.h"

using namespace std;

int main() {

  Seeker test;
  test.DefineWindow(4, 4, -2, -2, 20, 20);
  quadFunc f(0.5);
  test.ApplyFunction(&f);
  test.FindCycles();
  test.SetEpsilon(.00001);
  test.RefineCycles();
  return 0;
}
