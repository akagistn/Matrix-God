#include "Matrix.h"

int Matrix::rows() { return m_rows; }

int Matrix::columns() { return m_columns; }

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
  m_rows = rows;
  m_columns = 1;
  m_ptr = new double[rows];
}

Matrix::Matrix(int rows, int cols) {
  m_rows = rows;
  m_columns = cols;
  m_ptr = new double[rows * cols];
}

Matrix::~Matrix() {
  delete[] m_ptr;
}
