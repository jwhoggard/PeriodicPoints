#include "Seeker.h"

using namespace std;

void Seeker::DefineWindow(double width, double height, double leftX, double lowerY,
			  size_t xDiv, size_t yDiv) {
  win.SetValues(width, height, leftX, lowerY, xDiv, yDiv);
}



