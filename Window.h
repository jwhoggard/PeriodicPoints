#ifndef WINDOW
#define WINDOW

#include <vector>
#include <complex>
#include "func.h"

void printPair(std::pair<int, int> u);
void printPair(std::pair<double, double> u);

// Holds information for each cell in the grid
struct Cell {
Cell(int x, int y) : x(x), y(y), alive(true), locked(false), cycleLabel(-1) {}
  int x;
  int y;
  bool alive;
  bool locked;
  int cycleLabel;
  std::vector<std::pair<int, int>> connections;
};

// Window class holds a 2D array of cells, a function type, and
// information about coordinates of the window.
class Window {
 public:
  Window(double width, double height, double leftX, double lowerY, 
	 size_t xDiv, size_t yDiv);
 Window() : Window(4, 4, -2, -2, 100, 100) {}

  void ApplyFunction(func * applyFun);
  // Get various parameters if needed
  double GetLeftX() const {return leftX;}
  double GetLowerY() const {return lowerY;}
  double GetWidth() const {return width;}
  double GetHeight() const {return height;}
  size_t GetXDiv() const {return xDiv;}
  size_t GetYDiv() const {return yDiv;}

  // Return a copy of a cell for viewing
  Cell ViewCellAt(int i, int j) const {return cells[i][j];}

  // Alter connections, locks, colors, etc.  Most overloaded to take
  // either i, j or a pair.
  void AddConnectionAt(std::pair<int, int> cell, std::pair<int, int> target);
  void LockCellAt(int i, int j) {cells[i][j].locked = true;}
  void LockCellAt(std::pair<int, int> u) {LockCellAt(u.first, u.second);}
  void UnlockCellAt(int i, int j) {cells[i][j].locked = false;}
  void UnlockCellAt(std::pair<int, int> u) {UnlockCellAt(u.first, u.second);}
  bool IsLockedCellAt(int i, int j) const {return cells[i][j].locked;}
  bool IsLockedCellAt(std::pair<int, int> u) const {return IsLockedCellAt(u.first, u.second);}
  void SetCycleLabelAt(int i, int j, int color) {CellAt(i, j).cycleLabel = color;}
  void SetCycleLabelAt(std::pair<int, int> u, int color) {SetCycleLabelAt(u.first, u.second, color);}
  int GetCycleLabelAt(int i, int j) const {return ViewCellAt(i, j).cycleLabel;}
  int GetCycleLabelAt(std::pair<int, int> u) const {return GetCycleLabelAt(u.first, u.second);}

  bool CellAliveAt(int i, int j) const {return ViewCellAt(i, j).alive;}
  bool CellAliveAt(std::pair<int, int> u) const {return ViewCellAt(u.first, u.second).alive;}
  void KillCellAt(int i, int j) {CellAt(i, j).alive = false;}
  void KillCellAt(std::pair<int, int> u) {CellAt(u.first, u.second).alive = false;}

  // Get connection
  std::pair<int, int> GetConnectionAt(int i, int j, int idx) const {return ViewCellAt(i, j).connections[idx];}
  std::pair<int, int> GetConnectionAt(std::pair<int, int> u, int idx) const {return GetConnectionAt(u.first, u.second, idx);}
  
  /*
    Given an (i, j) index in the grid, convert it to the real-number
    coordinates of that point.

    Assumes that the indices are valid, although invalid coordinates
    will still return a reasonable (x, y) coordinate pair.
  */
  std::pair<double, double> GetCoordinatesFromIndex(int i, int j) const;

  /*
    Given an (x, y) real-number coordinate pair, will return the (i, j)
    coordinates in the window's grid which contains that point.
    
    Cells are inclusive on left and bottom, so are of the form 
    [x,x+d)x[y, y+d)

    If the resulting point is outside the grid, will return the
    coordinates (-1, -1).  The pair (-1, -1) will be considered to be
    pointing to the "dead" cell.
  */
  std::pair<int, int> GetIndexFromCoordinates(double x, double y) const;

 private:
  // Helper function to retrieve a particular cell:
  Cell& CellAt(int i, int j) {return cells[i][j];}
  Cell& CellAt(std::pair<int, int> u) {return CellAt(u.first, u.second);}

  double leftX;
  double lowerY;
  double width;
  double  height;
  size_t xDiv;
  size_t yDiv;
  std::vector<std::vector<Cell>> cells;
};
#endif
