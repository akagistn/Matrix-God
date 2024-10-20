#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.h"

int main() {
  Matrix georgy(12, 13);
  std::cout << "I am matrix god, i have " << georgy.columns() * georgy.rows() << " cells\n\n";

  // Matrix a = {1, 2, 3, 4, 5, 6};
  Matrix a(2, 3);
  a(1, 1) = 7;
  std::cout << a(1, 1) << "\n";
  a.printMatrixInt();
  Matrix b = a;
  a.reshape(3, 2);
  Matrix c(a);

  Matrix d(std::move(c));

  return 0;
}
