#include "Window.h"

void Cell::AddConnection(Cell * newCell) {
  connections.push_back(newCell);
  return;
}

Cell* Cell::GetConnection(size_t i) {
  if (0 < i and i < connections.size()) {
    return connections[i];
  } else {
    return nullptr;
  }
}

std::pair<double, double> Window::GetCoordinatesFromIndex(int i, int j) {
  double x, y;
  x = leftX + (0.5+i)*width/xDiv;
  y = lowerY + (0.5+j)*height/yDiv;
  return std::make_pair(x, y);
}

std::pair<int, int> Window::GetIndexFromCoordinates(double x, double y) {
  int i, j;
  if(x<leftX or y<lowerY or x >= leftX+width or y >= lowerY + height) {
      return std::make_pair(-1, -1);
  } else {
    i = static_cast<int>((x-leftX)*xDiv/width);
    j = static_cast<int>((y-lowerY)*yDiv/height);
    return std::make_pair(i, j);
  }
}
