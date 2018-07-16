#include <iostream>

template <class T>                                                                 
void printPair(std::pair<T, T> u) {                                                
  std::cout << '(' << u.first << ", " << u.second << ')';                          
}    

int main() {
  std::pair<int, int> x(1, 2);

  printPair(x);

  std::cout << std::endl;

  return 0;
}


