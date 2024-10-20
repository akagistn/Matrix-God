#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.h"

int main() {
  Matrix georgy(12, 13);
  std::cout << "I am matrix god, i have " << georgy.columns() * georgy.rows() << " cells";
  return 0;
}
