#include "Window.h"
#include <iostream>

Window::Window(double width, double height, double leftX, double lowerY, 
	       size_t xDiv, size_t yDiv) :
  leftX(leftX), lowerY(lowerY), width(width), height(height), 
  xDiv(xDiv), yDiv(yDiv) {
  SetupGrid();
}

void Window::ApplyFunction(func * f) {
  // Initialize the connections
  for(size_t i =0; i < xDiv; ++i) {
    for(size_t j=0; j < yDiv; ++j) {
      std::cout << "Index ";
      printPair(std::make_pair(i, j));
      std::cout << " with coordinates ";
      std::pair<double,double> z = GetCoordinatesFromIndex(i, j);
      printPair(z);
      std::cout << "\tImage ";
      z = f->pairVal(z);
      printPair(z);
      std::cout << " coord: ";
      z = GetIndexFromCoordinates(z.first, z.second);
      if(z.first == -1) {
	KillCellAt(i,j);
      }
      printPair(z);
      std::cout << std::endl;
      AddConnectionAt(std::pair<int,int>{i, j}, z);
      std::cout << "connection reads ";
      printPair(ViewCellAt(i, j).connections[0]);
      std::cout << std::endl;
    }
  }
  return;
}

std::pair<double, double> Window::GetCoordinatesFromIndex(int i, int j) const {
  double x, y;
  x = leftX + (0.5+i)*width/xDiv;
  y = lowerY + (0.5+j)*height/yDiv;
  return std::make_pair(x, y);
}

std::complex<double> Window::GetComplexFromIndexPair(std::pair<int, int> u) const {
  std::pair<double, double> temp = GetCoordinatesFromIndex(u.first, u.second);
  return std::complex<double>{temp.first, temp.second};
}

std::pair<int, int> Window::GetIndexFromCoordinates(double x, double y) const {
  int i, j;
  if(x<leftX or y<lowerY or x >= leftX+width or y >= lowerY + height) {
      return std::make_pair(-1, -1);
  } else {
    i = static_cast<int>((x-leftX)*xDiv/width);
    j = static_cast<int>((y-lowerY)*yDiv/height);
    return std::make_pair(i, j);
  }
}

void Window::AddConnectionAt(std::pair<int, int> cell, std::pair<int, int> target){
  CellAt(cell).connections.push_back(target);
  return;
}

void Window::SetValues(double w, double h, double lX, double lY, 
		       size_t xD, size_t yD) {
  width = w;
  height = h;
  leftX = lX;
  lowerY = lY;
  xDiv = xD;
  yDiv = yD;
  
  SetupGrid();
}

void Window::SetupGrid() {
  // Initialize the cells
  // If we didn't have to initialize each cell's x, y coordinates, 
  // we could try to initialize the whole array at once...
  // Maybe we don't actually need cells to have coords, 'though.
  for(size_t i = 0; i < xDiv; ++i) {
    std::vector<Cell> temp;
    for(size_t j = 0; j < yDiv; ++j) {
      temp.push_back(Cell(i, j));
    }
    cells.push_back(temp);
  }
}


