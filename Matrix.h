#pragma once
#include <initializer_list>

class Matrix {
private:
  double* m_ptr;
  int m_rows;
  int m_columns;
public:
  int rows();
  int columns();
  int volume();
  bool empty();
  void reshape(int rows, int cols);
  double determinant();
  void printMatrixInt();

  double& operator()(int row, int col);

  Matrix();
  Matrix(int rows);
  Matrix(int rows, int cols);
  Matrix(std::initializer_list<double> lst);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();
};

