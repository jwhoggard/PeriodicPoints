#ifndef WINDOW
#define WINDOW

#include <vector>
#include <complex>
#include "func.h"
#include <iostream>

/*
  Helper debug function:  Prints pairs of ints, doubles, size_ts, etc.
 */
template <class T>
void printPair(std::pair<T, T> u) {
  std::cout << '(' << u.first << ", " << u.second << ')';
}


/* 
   Holds information for each cell in the grid
*/
struct Cell {
Cell(int x, int y) : x(x), y(y), alive(true), locked(false), cycleLabel(-1) {}
  // Coordinates of cell [This may not be needed at all!]
  int x;
  int y;
  // Is cell alive: Mark a cell as "Dead" when it leads (eventually)
  // outside the bounds of the grid, or if it leads into an already marked
  // cycle.
  bool alive;
  // Future use:  May need to "lock" a cell for parallel processing later.
  bool locked;
  // Label (with integers) what cycles (if any) a cell belongs to.
  // Starts with default value -1 to indicate the cell has not been
  // visited.
  int cycleLabel;
  // Connections: The cell(s) that a given cell maps to.  This will be
  // only one point if we are dealing with a function.  For an inverse
  // function, this will be multiple points.
  std::vector<std::pair<int, int>> connections;
};

// Window class holds a 2D array of cells, a function type, and
// information about coordinates of the window.
class Window {
 public:
  Window(double width, double height, double leftX, double lowerY, 
	 size_t xDiv, size_t yDiv);
  // A default constructor that does nothing--
  // Call SetValues afterwards to use the window.
  Window() {} 
  
  void SetValues(double width, double height, double leftX, double lowerY, 
		 size_t xDiv, size_t yDiv);

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

  // Manage connections:

  // Add connection.  First pair indicates the cell to add a
  // connection to; second pair is the cell we are to map to.  [So
  // AddConnectionAt({0, 1}, {2, 3}) says that te cell at {0, 1} maps to
  // the cell at {2, 3}.]
  void AddConnectionAt(std::pair<int, int> cell, std::pair<int, int> target);
  // Two versions of GetConnectionAt, using either row and column, or
  // an ordered pair with row and column numbers, followed by the index
  // (which connection to get). So GetConnectionAt(7, 6, 0) returns the
  // coordinates (as a pair) of the first [zeroth] cell that cell {7, 6}
  // maps to.
  std::pair<int, int> GetConnectionAt(int row, int col, int index) const {return ViewCellAt(row, col).connections[index];}
  std::pair<int, int> GetConnectionAt(std::pair<int, int> u, int index) const {return GetConnectionAt(u.first, u.second, index);}

  // For locking, unlocking, or querying locked status.
  // Future use:  Parallel processing.
  void LockCellAt(int i, int j) {cells[i][j].locked = true;}
  void LockCellAt(std::pair<int, int> u) {LockCellAt(u.first, u.second);}
  void UnlockCellAt(int i, int j) {cells[i][j].locked = false;}
  void UnlockCellAt(std::pair<int, int> u) {UnlockCellAt(u.first, u.second);}
  bool IsLockedCellAt(int i, int j) const {return cells[i][j].locked;}
  bool IsLockedCellAt(std::pair<int, int> u) const {return IsLockedCellAt(u.first, u.second);}

  // Managing cycle labels.  Start with coordinates of a point (row
  // and column) either individually or as a pair, then give the integer
  // "color" to apply to that cell.

  void SetCycleLabelAt(int row, int col, int color) 
  {CellAt(row, col).cycleLabel = color;}

  void SetCycleLabelAt(std::pair<int, int> u, int color) 
  {SetCycleLabelAt(u.first, u.second, color);}

  // Returns the color at a given cell.
  int GetCycleLabelAt(int i, int j) const {return ViewCellAt(i, j).cycleLabel;}
  int GetCycleLabelAt(std::pair<int, int> u) const {return GetCycleLabelAt(u.first, u.second);}

  // Managing "alive" status of cells.  Cells start as alive by
  // default, but can be killed (marked at "not alive").  It is not
  // possible for a cell to "come back to live" after being killed, so this
  //is a one-way switch.
  bool CellAliveAt(int i, int j) const {return ViewCellAt(i, j).alive;}
  bool CellAliveAt(std::pair<int, int> u) const {return ViewCellAt(u.first, u.second).alive;}
  void KillCellAt(int i, int j) {CellAt(i, j).alive = false;}
  void KillCellAt(std::pair<int, int> u) {CellAt(u.first, u.second).alive = false;}

  // The following manage the mapping between coordinates and indices in the grid.
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

  // Set up the grid once coordinates are established.
  void SetupGrid();

  // Left and bottom coordinates of grid
  double leftX;
  double lowerY;
  // Total width and height of the grid
  double width;
  double  height;
  // Number of divisions in x and y directions
  size_t xDiv;
  size_t yDiv;
  
  // 2D array of cells.  Use vectors because size is determined at
  // runtime.
  std::vector<std::vector<Cell>> cells;


};
#endif
