#include "Window.h"
#include <iostream>

void printPair(std::pair<int, int> u) {
  std::cout << '(' << u.first << ", " << u.second << ')';
}
void printPair(std::pair<double, double> u) {
  std::cout << '(' << u.first << ", " << u.second << ')';
}

void Cell::AddConnection(std::pair<int, int> newAdd) {
  connections.push_back(newAdd);
  //  std::cout << "Added ";
  //printPair(newAdd);
  //std::cout << std::endl;
  return;
}

std::pair<int, int> Cell::GetConnection(size_t i) const {
  if (i < connections.size()) {
    return connections[i];
  } else {
    return std::pair<int, int>{-1, -1};
  }
}

Window::Window(double width, double height, double leftX, double lowerY, int xDiv, int yDiv, quadFunc F) :
  leftX(leftX), lowerY(lowerY), width(width), height(height), 
  xDiv(xDiv), yDiv(yDiv), f(F) {
  // Initialize the cells
  for(int i = 0; i < xDiv; ++i) {
    std::vector<Cell> temp;
    for(int j = 0; j < yDiv; ++j) {
      temp.push_back(Cell(i, j));
    }
    cells.push_back(temp);
  }
  // Initialize the connections
  for(int i =0; i < xDiv; ++i) {
    for(int j=0; j < yDiv; ++j) {
      std::cout << "Index ";
      printPair(std::make_pair(i, j));
      std::cout << " with coordinates ";
      std::pair<double,double> z = GetCoordinatesFromIndex(i, j);
      printPair(z);
      std::cout << "\tImage ";
      z = f.pairVal(z);
      printPair(z);
      std::cout << " coord: ";
      z = GetIndexFromCoordinates(z.first, z.second);
      printPair(z);
      std::cout << std::endl;
      AddConnectionAt(std::pair<int,int>{i, j}, z);
      std::cout << "connection reads ";
      printPair(GetCellAt(i, j).GetConnection(0));
      std::cout << std::endl;
    }
  }
}

std::pair<double, double> Window::GetCoordinatesFromIndex(int i, int j) const {
  double x, y;
  x = leftX + (0.5+i)*width/xDiv;
  y = lowerY + (0.5+j)*height/yDiv;
  return std::make_pair(x, y);
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
  (cells[cell.first][cell.second]).AddConnection(target);
  return;
}
