#pragma once
class Matrix {
private:
  double* m_ptr;
  int m_rows;
  int m_columns;
public:
  int rows();
  int columns();
  bool empty();
  void reshape(int rows, int cols);

  Matrix();
  Matrix(int rows);
  Matrix(int rows, int cols);
  ~Matrix();
};

