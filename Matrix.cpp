#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <string>

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

double Matrix::determinant() {
  if (m_columns != m_rows) {
    throw "rows and columns do not match";
  }
}

void Matrix::printMatrixInt() {
  for (int i = 0; i < m_rows; ++i) {
    std::cout << "|";
    int max_size = 1;
    int* elem_size = new int[m_columns];
    for (int j = 0; j < m_columns; ++j) {
      int tmp = int(m_ptr[m_rows * i + j]);
      int cnt = 0;
      if (tmp < 0) {
        ++cnt;
        tmp = -tmp;
      }
      if (tmp == 0) { cnt = 1; }
      else {
        while (tmp > 0) {
          tmp /= 10;
          ++cnt;
        }
      }
      elem_size[j] = cnt;
      max_size = std::max(max_size, cnt);
    }
    for (int j = 0; j < m_columns; ++j) {
      int tmp = m_ptr[m_rows * i + j];
      if (j + 1 == m_columns) {
        std::cout << tmp;
        break;
      }
      std::cout << tmp << std::string(max_size - elem_size[j] + 1, ' ');
    }
    delete[] elem_size;
    std::cout << "|\n";
  }
}

double& Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= m_rows || col >= m_columns) {
    throw "out of range";
  }
  return m_ptr[m_columns*row + col];
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

Matrix::Matrix(std::initializer_list<double> lst) {
  //
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
