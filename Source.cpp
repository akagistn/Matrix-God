#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.h"

int main() {
  linalg::Matrix georgy(12, 13);
  std::cout << "I am matrix god, i have " << georgy.columns() * georgy.rows() << " cells\n\n";

  // Matrix a = {1, 2, 3, 4, 5, 6};
  linalg::Matrix a(2, 3);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      a(i, j) = i + j;
    }
  }
  a.printMatrixInt();

  linalg::Matrix b = linalg::transpose(a);

  std::cout << a(1, 1) << "\n";
  b.printMatrixInt();
  // linalg::Matrix b = a;
  a.reshape(3, 2);
  linalg::Matrix c(a);

  linalg::Matrix d(std::move(c));

  return 0;
}
