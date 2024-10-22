#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <cmath>
#include <iomanip>

namespace linalg {

  double Matrix::epsilon = 1e-9;

  bool Matrix::equal_numbers(double a, double b) const {
    return std::fabs(a - b) < epsilon;
  }

  int Matrix::rows() const { return m_rows; }

  int Matrix::columns() const { return m_columns; }

  int Matrix::volume() const { return m_rows * m_columns; }

  bool Matrix::empty() const { return m_rows != 0 && m_columns != 0; }

  void Matrix::reshape(int rows, int cols) {
    if (rows <= 0 || cols <= 0 || rows * cols != m_rows * m_columns) { return; } // exception
    m_rows = rows;
    m_columns = cols;
    return;
  }

  double Matrix::determinant() {
    if (m_columns != m_rows) {
      throw std::runtime_error("rows and columns do not match");
    }
  }

  void Matrix::printMatrix(std::ostream& os) const {
    int* max_lenght;
    max_lenght = new int[m_columns];
    for (int col = 0; col < m_columns; ++col) {
      int ans = 1;
      for (int row = 0; row < m_rows; ++row) {
        std::string str = std::to_string(m_ptr[m_columns * row + col]);
        while (str.size() > 0) {
          if (str == "0" || !(str.back() == '0' || str.back() == '.')) {
            break;
          }
          str.pop_back();
        }
        ans = std::max(int(str.size()), ans);
      }
      max_lenght[col] = ans;
    }
    for (int row = 0; row < m_rows; ++row) {
      os << "| ";
      for (int col = 0; col < m_columns; ++col) {
        std::string str = std::to_string(m_ptr[m_columns * row + col]);
        while (str.size() > 0) {
          if (str == "0" || !(str.back() == '0' || str.back() == '.')) {
            break;
          }
          str.pop_back();
        }
        if (col + 1 == m_columns) {
          os << std::string(max_lenght[col] - str.size(), ' ') << str;
          break;
        }
        os << std::string(max_lenght[col] - str.size(), ' ') << str << "  ";
      }
      os << " |\n";
    }
    delete max_lenght;
  }

  double& Matrix::operator()(int row, int col) {
    if (row < 0 || col < 0 || row >= m_rows || col >= m_columns) {
      throw std::runtime_error("out of range");
    }
    return m_ptr[m_columns * row + col];
  }

  const double& Matrix::operator()(int row, int col) const {
    if (row < 0 || col < 0 || row >= m_rows || col >= m_columns) {
      throw std::runtime_error("out of range");
    }
    return m_ptr[row * m_columns + col];
  }

  Matrix& linalg::Matrix::operator=(Matrix&& other) {
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

  Matrix& linalg::Matrix::operator=(const linalg::Matrix& other) {
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

  Matrix& Matrix::operator+=(const Matrix& other) {
    if (this->m_rows != other.m_rows || this->m_columns != other.m_columns) {
      throw std::runtime_error("Matrix dimensions do not match (cannot perform +/- = assignment)");
    }
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        (*this)(i, j) += other(i, j);
      }
    }
    return *this;
  }

  Matrix& Matrix::operator-=(const Matrix& other) {
    *(this) += -other;
    return *this;
  }

  Matrix& Matrix::operator*=(const Matrix& other) {
    (*this) = (*this) * other;
    return (*this);
  }

  Matrix& Matrix::operator*=(double scalar) {
    (*this) = (*this) * scalar;
    return (*this);
  }

  bool Matrix::operator==(const Matrix& other) const {
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
      return false;
    }
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        if (!this->equal_numbers(this->m_ptr[i * m_columns + j], other.m_ptr[i * m_columns + j])) {
          return false;
        }
      }
    }
    return true;
  }

  bool Matrix::operator!=(const linalg::Matrix& other) const {
    return !(*this == other);
  }

  Matrix Matrix::operator+(const Matrix& other) const {
    if (this->m_rows != other.m_rows ||
      this->m_columns != other.m_columns) {
      throw std::runtime_error("Matrix dimensions do not match (for addition)");
    }
    Matrix result(this->m_rows, this->m_columns);
    for (int i = 0; i < this->m_rows; ++i) {
      for (int j = 0; j < this->m_columns; ++j) {
        result(i, j) = (*this)(i, j) + other(i, j);
      }
    }
    return result;
  }

  Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = (*this) + (-other);
    return result;
  }

  Matrix Matrix::operator*(const Matrix& other) const {
    if (this->m_columns != other.rows()) {
      throw std::runtime_error("Matrix dimensions do not match (for multiplication)");
    }
    Matrix result(this->m_rows, other.columns());
    for (int i = 0; i < this->m_rows; ++i) {
      for (int j = 0; j < other.columns(); ++j) {
        double cell_result = 0;
        for (int cnt = 0; cnt < this->m_columns; ++cnt) {
          cell_result += (*this)(i, cnt) * other(cnt, j);
        }
        result(i, j) = cell_result;
      }
    }
    return result;
  }

  Matrix Matrix::operator*(double scalar) const {
    Matrix result(m_rows, m_columns);
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        result(i, j) = (*this)(i, j) * scalar;
      }
    }
    return result;
  }

  Matrix Matrix::operator-() const {
    Matrix result(m_rows, m_columns);
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        result(i, j) = -(*this)(i, j);
      }
    }
    return result;
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

  Matrix::Matrix(std::initializer_list<double> lst) {
    m_ptr = new double[lst.size()];
    m_rows = lst.size();
    m_columns = 1;
    int ptr = 0;
    for (auto& value : lst) {
      m_ptr[ptr++] = value;
    }
  }

  Matrix::Matrix(std::initializer_list<std::initializer_list<double>> lst) {
    m_rows = lst.size();
    if (m_rows <= 0) {
      throw std::runtime_error("Matrix cannot be empty");
    }
    m_columns = lst.begin()->size();
    if (m_columns <= 0) {
      throw std::runtime_error("Matrix cannot be empty");
    }
    m_ptr = new double[m_rows * m_columns];
    int ptr = 0;
    for (auto& row : lst) {
      if (row.size() != m_columns) {
        delete[] m_ptr;
        throw std::runtime_error("All rows must have the same number of columns");
      }
      for (auto& value : row) {
        m_ptr[ptr++] = value;
      }
    }
  }

  Matrix::~Matrix() {
    delete[] m_ptr;
  }

  std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    matrix.printMatrix(os);
    return os;
  }

  Matrix linalg::transpose(linalg::Matrix& m) {
    linalg::Matrix result(m.columns(), m.rows());
    for (int i = 0; i < m.rows(); ++i) {
      for (int j = 0; j < m.columns(); ++j) {
        result(j, i) = m(i, j);
      }
    }
    return result;
  }

  Matrix concatenate(const Matrix& m1, const Matrix& m2) {
    if (m1.rows() != m2.rows()) {
      throw std::runtime_error("Cannot concatenate matrices, row numbers do not match");
    }
    Matrix result(m1.rows(), m1.columns() + m2.columns());
    for (int i = 0; i < m1.rows(); ++i) {
      for (int j = 0; j < m1.columns() + m2.columns(); ++j) {
        if (j < m1.columns()) {
          result(i, j) = m1(i, j);
        }
        else {
          result(i, j) = m2(i, j - m1.columns());
        }
      }
    }
    return result;
  }

  Matrix power(const Matrix& m, int pow) {
    if (m.rows() != m.columns()) {
      throw(std::runtime_error("Non-square matrix cannot be raised to a power"));
    }
    if (pow == 0) {
      //identity matrix
    }
    if (pow == 1) {
      return m;
    }
    else if (pow < 0) {
      //
    }
    else {
      if (pow % 2) {
        return m * power(m, pow - 1);
      }
      else {
        Matrix sq_root = power(m, pow / 2);
        return sq_root * sq_root;
      }
    }
  }
  
}
