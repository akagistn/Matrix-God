#pragma once
#include <initializer_list>

namespace linalg {
  class Matrix {
  private:
    double* m_ptr;
    int m_rows;
    int m_columns;
    double epsilon;
    bool equal_numbers(double a, double b) const;
  public:
    int rows();
    int columns();
    int volume();
    bool empty();
    void reshape(int rows, int cols);
    double determinant();
    void printMatrix();
    void printMatrixInt();

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    Matrix& operator=(const linalg::Matrix& other);
    Matrix& operator=(Matrix&& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix();
    Matrix(int rows);
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix(std::initializer_list<double> lst);
    Matrix(std::initializer_list<std::initializer_list<double>> lst);
    ~Matrix();
  };

  Matrix transpose(Matrix& m);
}
