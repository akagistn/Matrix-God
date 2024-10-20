#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <string>

int linalg::Matrix::rows() { return m_rows; }

int linalg::Matrix::columns() { return m_columns; }

int linalg::Matrix::volume() { return m_rows * m_columns; }

bool linalg::Matrix::empty() { return m_rows != 0 && m_columns != 0; }

void linalg::Matrix::reshape(int rows, int cols) {
  if (rows <= 0 || cols <= 0 || rows * cols != m_rows * m_columns) { return; } // exception
  m_rows = rows;
  m_columns = cols;
  return;
}

double linalg::Matrix::determinant() {
  if (m_columns != m_rows) {
    throw "rows and columns do not match";
  }
}

void linalg::Matrix::printMatrixInt() {
  for (int i = 0; i < m_rows; ++i) {
    std::cout << "|";
    for (int j = 0; j < m_columns; ++j) {
      int tmp = m_ptr[m_columns * i + j];
      if (j + 1 == m_columns) {
        std::cout << tmp;
        break;
      }
      std::cout << tmp << " ";
    }
    std::cout << "|\n";
  }
}

double& linalg::Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= m_rows || col >= m_columns) {
    throw "out of range";
  }
  return m_ptr[m_columns * row + col];
}

const double& linalg::Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= m_rows || col >= m_columns) {
    throw "out of range";
  }
  return m_ptr[row * m_columns + col];
}

linalg::Matrix& linalg::Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    delete[] m_ptr;
    m_ptr = other.m_ptr;
    m_rows = other.m_rows;
    m_columns = other.m_columns;
    other.m_ptr = nullptr;
    other.m_rows = 0;
    other.m_columns = 0;
  }
  return *this;
}

linalg::Matrix& linalg::Matrix::operator=(const linalg::Matrix& other) {
  if (this != &other) {
    delete[] m_ptr;
    m_rows = other.m_rows;
    m_columns = other.m_columns;
    m_ptr = new double[m_rows * m_columns];
    for (int i = 0; i < m_rows * m_columns; ++i) {
      m_ptr[i] = other.m_ptr[i];
    }
  }
  return *this;
}

bool linalg::Matrix::operator==(const linalg::Matrix & other) const {
  if (m_rows != other.m_rows || m_columns != other.m_columns) {
    return false;
  }
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_columns; ++j) {
      if ((*this)(i, j) != other(i, j)) {
        return false;
      }
    }
  }
  return true;
}

bool linalg::Matrix::operator!=(const linalg::Matrix& other) const {
  return !(*this == other);
}

linalg::Matrix::Matrix() {
  m_rows = 1;
  m_columns = 1;
  m_ptr = new double[1];
}

linalg::Matrix::Matrix(int rows) {
  m_rows = std::max(rows, 1);
  m_columns = 1;
  m_ptr = new double[rows];
}

linalg::Matrix::Matrix(int rows, int cols) {
  m_rows = std::max(rows, 1);
  m_columns = std::max(cols, 1);
  m_ptr = new double[rows * cols];
}

linalg::Matrix::Matrix(const Matrix& other) {
  m_rows = other.m_rows;
  m_columns = other.m_columns;
  int sz = m_rows * m_columns;
  m_ptr = new double[sz];
  for (int i = 0; i < sz; ++i) {
    m_ptr[i] = other.m_ptr[i];
  }
}

linalg::Matrix::Matrix(Matrix&& other) {
  m_ptr = other.m_ptr;
  m_rows = other.m_rows;
  m_columns = other.m_columns;
  other.m_ptr = 0;
  other.m_rows = 0;
  other.m_columns = 0;
}

linalg::Matrix::Matrix(std::initializer_list<double> lst) {
  m_ptr = new double[lst.size()];
  m_rows = lst.size();
  m_columns = 1;
  int ptr = 0;
  for (auto& value : lst) {
    m_ptr[ptr++] = value;
  }
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
  m_rows = lst.size();
  if (m_rows <= 0) {
    throw "Matrix cannot be empty";
  }
  m_columns = lst.begin()->size();
  if (m_columns <= 0) {
    throw "Matrix cannot be empty";
  }
  m_ptr = new double[m_rows * m_columns];
  int ptr = 0;
  for (auto& row : lst) {
    if (row.size() != m_columns) {
      delete[] m_ptr;
      throw "All rows must have the same number of columns";
    }
    for (auto& value : row) {
      m_ptr[ptr++] = value;
    }
  }
}

linalg::Matrix::~Matrix() {
  delete[] m_ptr;
}

linalg::Matrix linalg::transpose(linalg::Matrix& m) {
  linalg::Matrix result(m.columns(), m.rows());
  m.printMatrixInt();
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.columns(); ++j) {
      result(j, i) = m(i, j);
    }
  }
  return result;
}
