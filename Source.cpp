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
    linalg::Matrix two_dim(4, 8);
    linalg::Matrix m1 = { {6, 6}, {6, 4}, {1, 2} };
    linalg::Matrix m2 = { {6, 6, 3}, {6, 4, 2}, {1, 2, 3} };
    linalg::Matrix m3 = { {6, 5}, {4, 1} };
    linalg::Matrix m4 = { {1, 2}, {6, 4}, {9, 8} };
    linalg::Matrix m5 = { {0.9, 4.0, 55.54321, 6.0, -777.0} };
    linalg::Matrix m6 = { {9}, {8}, {7}, {6}, {5} };
    linalg::Matrix m7 = { 1.0, 2.0, 4.22, 6.0, -7.0, 0.121 };
    linalg::Matrix test_copy = linalg::Matrix{ 2, 2, 8 };
    linalg::Matrix test_real_print = { {1.228, -2}, {666, 0}, {-2192, -6.67} };

    linalg::Matrix test_gauss = { {1, 2, 3}, {5, 0, 2}, {6, 0, 1} };
    std::cout << "Test Gauss:\n" << test_gauss << "\nto\n"
      << linalg::gaussElimination(test_gauss);

    // Test operator== and operator!=

    linalg::Matrix test_equal1 = { 5 };
    linalg::Matrix test_equal2 = { 5.0000000001 };

    linalg::Matrix demo = linalg::power(linalg::identityMatrix(6), 123) + 
                 linalg::transpose(linalg::identityMatrix(6)) * 0.1;
    demo.addRows(0,1,-1);
    std::cout << demo;
    demo = linalg::gaussElimination(demo);
    std::cout << "this is new matrix\n" << demo;

    std::cout << linalg::power(m2, 7);
    m2(1, 0) = 0;
    m2(1, 1) = 0;
    m2(1, 2) = 0;
    std::cout << linalg::power(m2, 7);

    linalg::Matrix copyyy = test_real_print;
    std::cout << (test_equal1 == test_equal2) << " " << (copyyy != test_real_print) << "\n";
    // std::cout << (std::fabs(double(5) - double(5)) < 1e-9) << "\n";

    double val = test_real_print(0, 0);
    const linalg::Matrix skibidi = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0} };
    // skibidi = test_real_print;
    std::cout << "\n" << val << "\n";

    linalg::Matrix mult = m7 * m5;
    std::cout << "\n" << mult << "\n";
    linalg::Matrix eee{ {1, 0.1, -4 }, {0, 1, 2},{0.08, 0, 1} };

    std::cout << "eee matrix gaussElim: \n" << eee << "\nto\n" << linalg::gaussElimination(eee);

    std::cout << "\n" << test_real_print - test_real_print << m2 - eee;

    std::cout << "\n" << eee << "\n" << eee * m2 << "\n";
    std::cout << m1 << m2 << m7 << m3 << test_copy 
              << m4 << m5 << m6 << test_real_print;

    std::cout << eee * 2 << "\n" << 2 * eee;
    std::cout << ((test_copy * 7) == (7 * test_copy)) << "\n";

    std::cout << "\nconcatenate:\n" << linalg::concatenate(eee, eee * 2);
    
    std::cout << "m4\n" <<m4;
    m4 -= 0.9 * m4;
    std::cout << m4;
    m4 *= -0.65;
    std::cout << m4;
    m4 += m5;

    std::cout << m1 + m2 << "gg";
    std::cout << m1 * m7;

    

    throw(5);
  }
  catch (std::runtime_error err) {
    std::cout << err.what();
  }
  catch (...) {
    std::cout << "untracked exception";
  }
  

  return 0;
}
