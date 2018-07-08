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

/*
  Given an (i, j) index in the grid, convert it to the real-number
  coordinates of that point.

  Assumes that the indices are valid, although invalid coordinates
  will still return a reasonable (x, y) coordinate pair.
*/
std::pair<double, double> Window::GetCoordinatesFromIndex(int i, int j) {
  double x, y;
  x = leftX + (0.5+i)*width/xDiv;
  y = lowerY + (0.5+j)*height/yDiv;
  return std::make_pair(x, y);
}

/*
  Given an (x, y) real-number coordinate pair, will return the (i, j)
  coordinates in the window's grid which contains that point.

  Cells are inclusive on left and bottom, so are of the form
  [x, x+d)x[y, y+d)

  If the resulting point is outside the grid, will return the
  coordinates (-1, -1).  The pair (-1, -1) will be considered to be
  pointing to the "dead" cell.
 */
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
