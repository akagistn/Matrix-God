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
  linalg::Matrix m7 = {1, 2, 4, 6, 7, 9};
  linalg::Matrix test_copy = linalg::Matrix{ 2, 2, 8 };
  linalg::Matrix test_real_print = { {1.228, -2}, {666, 0}, {-2192, -6.67} };


  m1.printMatrixInt();
  m2.printMatrixInt();
  m7.printMatrixInt();
  m3.printMatrixInt();
  test_copy.printMatrixInt();
  m4.printMatrixInt();
  m5.printMatrixInt();
  m6.printMatrixInt();
  test_real_print.printMatrix();

  return 0;
}
