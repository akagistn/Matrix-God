#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Matrix.h"

int main() {
  try {
    linalg::Matrix m1 = { {6, 6}, {6, 4}, {1, 2} };
    linalg::Matrix m2 = { {6, 6, 3}, {6, 4, 2}, {1, 2, 3} };
    linalg::Matrix m3 = { {6, 5}, {4, 1} };
    linalg::Matrix m4 = { {1, 2}, {6, 4}, {9, 8} };
    linalg::Matrix m5 = { {1, 4, 5, 6, 7} };
    linalg::Matrix m6 = { {9}, {8}, {7}, {6}, {5} };
    linalg::Matrix m7 = { 1, 2, 4, 6, 7, 9 };
    linalg::Matrix test_copy = linalg::Matrix{ 2, 2, 8 };
    linalg::Matrix test_real_print = { {1.228, -2}, {666, 0}, {-2192, -6.67} };

    linalg::Matrix test_equal1 = { 5 };
    linalg::Matrix test_equal2 = { 5.0000000001 };
    linalg::Matrix copyyy = test_real_print;
    std::cout << (test_equal1 == test_equal2) << " " << (copyyy != test_real_print) << "\n";
    // std::cout << (std::fabs(double(5) - double(5)) < 1e-9) << "\n";

    double val = test_real_print(0, 0);
    const linalg::Matrix skibidi = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
    // skibidi = test_real_print;
    std::cout << "\n" << val << "\n";

    m1.printMatrixInt();
    m2.printMatrixInt();
    m7.printMatrixInt();
    m3.printMatrixInt();
    test_copy.printMatrixInt();
    m4.printMatrixInt();
    m5.printMatrixInt();
    m6.printMatrixInt();
    throw(5);
    test_real_print.printMatrix();
  }
  catch (std::string exc) {
    std::cout << exc;
  }
  catch (...) {
    std::cout << "untracked exception";
  }
  

  return 0;
}
