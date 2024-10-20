#include <iostream>
#include <vector>
#include <algorithm>
#include "Matrix.h"

int main() {
  linalg::Matrix m1 = { {6, 6}, {6, 4}, {1, 2} };
  linalg::Matrix m2 = { {6, 6, 3}, {6, 4, 2}, {1, 2, 3} };
  linalg::Matrix m3 = { {6, 5}, {4, 1}};
  linalg::Matrix m4 = { {1, 2}, {6, 4}, {9, 8} };
  linalg::Matrix m5 = { {1, 4, 5, 6, 7} };
  linalg::Matrix m6 = { {9}, {8}, {7}, {6}, {5} };

  m1.printMatrixInt();
  m2.printMatrixInt();
  m3.printMatrixInt();
  m4.printMatrixInt();
  m5.printMatrixInt();
  m6.printMatrixInt();

  return 0;
}
