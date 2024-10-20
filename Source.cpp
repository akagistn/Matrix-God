#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.h"

int main() {
  Matrix georgy(12, 13);
  std::cout << "I am matrix god, i have " << georgy.columns() * georgy.rows() << " cells\n\n";

  Matrix a(2, 3);
  Matrix b = a;
  a.reshape(3, 2);
  Matrix c(a);

  return 0;
}
