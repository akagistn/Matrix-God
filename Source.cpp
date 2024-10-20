#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Matrix.h"

int main() {
  try {

    // Use all constructors to create different matrices

    linalg::Matrix empty;
    linalg::Matrix one_dim(66);
    linalg::Matrix m1 = { {6, 6}, {6, 4}, {1, 2} };
    linalg::Matrix m2 = { {6, 6, 3}, {6, 4, 2}, {1, 2, 3} };
    linalg::Matrix m3 = { {6, 5}, {4, 1} };
    linalg::Matrix m4 = { {1, 2}, {6, 4}, {9, 8} };
    linalg::Matrix m5 = { {0.9, 4.0, 55.54321, 6.0, -777.0} };
    linalg::Matrix m6 = { {9}, {8}, {7}, {6}, {5} };
    linalg::Matrix m7 = { 1.0, 2.0, 4.22, 6.0, -7.0, 0.121 };
    linalg::Matrix test_copy = linalg::Matrix{ 2, 2, 8 };
    linalg::Matrix test_real_print = { {1.228, -2}, {666, 0}, {-2192, -6.67} };

    // Test operator== and operator!=

    linalg::Matrix test_equal1 = { 5 };
    linalg::Matrix test_equal2 = { 5.0000000001 };
    linalg::Matrix copyyy = test_real_print;
    std::cout << (test_equal1 == test_equal2) << " " << (copyyy != test_real_print) << "\n";
    // std::cout << (std::fabs(double(5) - double(5)) < 1e-9) << "\n";

    double val = test_real_print(0, 0);
    const linalg::Matrix skibidi = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
    // skibidi = test_real_print;
    std::cout << "\n" << val << "\n";

    linalg::Matrix mult = m7 * m5;
    std::cout << "\n";
    mult.printMatrix();
    std::cout << "\n";

    linalg::Matrix eee{ {1, 0.1, -4},{0, 1, 2},{0.08, 0, 1} };
    std::cout << "\n";
    eee.printMatrix();
    std::cout << "\n";
    (eee*m2).printMatrix(); // produces right answer
    std::cout << "\n";

    m1.printMatrixInt();
    m2.printMatrixInt();
    m7.printMatrixInt();
    m3.printMatrixInt();
    test_copy.printMatrixInt();
    m4.printMatrixInt();
    m5.printMatrixInt();
    m6.printMatrixInt();
    test_real_print.printMatrix();
    throw(5);
  }
  catch (std::string exc) {
    std::cout << exc;
  }
  catch (...) {
    std::cout << "untracked exception";
  }
  

  return 0;
}
