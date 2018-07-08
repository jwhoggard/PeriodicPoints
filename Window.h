#include <vector>

class Cell {
 public:
 Cell(int x, int y) : x(x), y(y) {}
  int GetX() {return x;}
  int GetY() {return y;}
  void AddConnection(Cell * newCell);
  int GetNumConnections() {return connections.size();}
  Cell*  GetConnection(size_t i);
 private:
  int x;
  int y;
  std::vector<Cell*> connections;
};

class Window {
 public:
 Window(double width, double height, double leftX, double lowerY, int xDiv, int yDiv) :
  leftX(leftX), lowerY(lowerY), width(width), height(height), 
    xDiv(xDiv), yDiv(yDiv) {}
 Window() : Window(4, 4, -2, -2, 100, 100) {}

  double GetLeftX() {return leftX;}
  double GetLowerY() {return lowerY;}
  double GetWidth() {return width;}
  double GetHeight() {return height;}
  int GetXDiv() {return xDiv;}
  int GetYDiv() {return yDiv;}
  
  /*
    Given an (i, j) index in the grid, convert it to the real-number
    coordinates of that point.

    Assumes that the indices are valid, although invalid coordinates
    will still return a reasonable (x, y) coordinate pair.
  */
  std::pair<double, double> GetCoordinatesFromIndex(int i, int j);

  /*
    Given an (x, y) real-number coordinate pair, will return the (i, j)
    coordinates in the window's grid which contains that point.
    
    Cells are inclusive on left and bottom, so are of the form 
    [x,x+d)x[y, y+d)

    If the resulting point is outside the grid, will return the
    coordinates (-1, -1).  The pair (-1, -1) will be considered to be
    pointing to the "dead" cell.
  */
  std::pair<int, int> GetIndexFromCoordinates(double x, double y);

 private:
  double leftX;
  double lowerY;
  double width;
  double  height;
  int xDiv;
  int yDiv;
  std::vector<std::vector<Cell>> cells;
  
};
