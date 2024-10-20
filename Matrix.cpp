#include "Matrix.h"
#include <initializer_list>
#include <algorithm>

int Matrix::rows() { return m_rows; }

int Matrix::columns() { return m_columns; }

int Matrix::volume() { return m_rows * m_columns; }

bool Matrix::empty() { return m_rows != 0 && m_columns != 0; }

void Matrix::reshape(int rows, int cols) {
  if (rows <= 0 || cols <= 0 || rows * cols != m_rows * m_columns) { return; } // exception
  m_rows = rows;
  m_columns = cols;
  return;
}

Matrix::Matrix() {
  m_rows = 1;
  m_columns = 1;
  m_ptr = new double[1];
}

Matrix::Matrix(int rows) {
  m_rows = std::max(rows, 1);
  m_columns = 1;
  m_ptr = new double[rows];
}

Matrix::Matrix(int rows, int cols) {
  m_rows = std::max(rows, 1);
  m_columns = std::max(cols, 1);
  m_ptr = new double[rows * cols];
}

Matrix::Matrix(const Matrix& other) {
  m_rows = other.m_rows;
  m_columns = other.m_columns;
  int sz = m_rows * m_columns;
  m_ptr = new double[sz];
  for (int i = 0; i < sz; ++i) {
    m_ptr[i] = other.m_ptr[i];
  }
}

Matrix::Matrix(Matrix&& other) {
  m_ptr = other.m_ptr;
  m_rows = other.m_rows;
  m_columns = other.m_columns;
  other.m_ptr = 0;
  other.m_rows = 0;
  other.m_columns = 0;
}

Matrix::~Matrix() {
  delete[] m_ptr;
}
