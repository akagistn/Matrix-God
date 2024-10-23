#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <cmath>
#include <iomanip>

namespace linalg {

  double Matrix::epsilon = 1e-9;

  int Matrix::getRows() const { return m_rows; }

  int Matrix::getColumns() const { return m_columns; }

  int Matrix::getVolume() const { return m_rows * m_columns; }

  double Matrix::getEpsilon() const { return epsilon; }

  double Matrix::determinant() const {
    return matrixGaussDeterminant(*this);
  }

  bool Matrix::empty() const { return m_rows != 0 && m_columns != 0; }

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

  void Matrix::reshape(int rows, int cols) {
    if (rows <= 0 || cols <= 0 || rows * cols != m_rows * m_columns) { return; } // exception
    m_rows = rows;
    m_columns = cols;
    return;
  }

  void Matrix::addRows(int source_row, int target_row, double coef) {
    //std::cout << "adding rows(" << source_row << ", " 
    //          << target_row << ", " << coef << ")\n";
    for (int i = 0; i < this->m_columns; ++i) {
      (*this)(target_row, i) += (((*this)(source_row, i)) * coef);
    }
  }

  void Matrix::swapRows(int row1, int row2) {
    int len = this->m_rows;
    for (int i = 0; i < len; ++i) {
      std::swap((*this)(row1, i), (*this)(row2, i));
    }
  }

  void Matrix::swapColumns(int col1, int col2) {
    int len = this->m_columns;
    for (int i = 0; i < len; ++i) {
      std::swap((*this)(i, col1), (*this)(i, col2));
    }
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
        if (equalNumbers(this->m_ptr[i * m_columns + j], other.m_ptr[i * m_columns + j], this->epsilon)) {
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
    if (this->m_columns != other.getRows()) {
      throw std::runtime_error("Matrix dimensions do not match (for multiplication)");
    }
    Matrix result(this->m_rows, other.getColumns());
    for (int i = 0; i < this->m_rows; ++i) {
      for (int j = 0; j < other.getColumns(); ++j) {
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

  Matrix Matrix::operator/(double scalar) const {
    if (scalar == 0) {
      throw std::runtime_error("cannot divide by 0");
    }
    return (*this) * (1.0 / scalar);
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

  std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    m.printMatrix(os);
    return os;
  }

  bool equalNumbers(double a, double b, double eps) {
    return std::fabs(a - b) < eps;
  }

  double minor(const Matrix& m, int row, int col) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("Minor is available only for square matrices");
    }
    int dim = m.getRows();
    if (dim == 1) {
      throw std::runtime_error("Minor is not available for 1-dim matrices");
    }
    Matrix minor_(dim - 1, dim - 1);
    for (int row_ = 0; row_ < dim; ++row_) {
      for (int col_ = 0; col_ < dim; ++col_) {
        if (row_ == row || col_ == col) continue;
        int row__ = row_, col__ = col_;
        if (row_ > row) --row__;
        if (col_ > col) --col__;
        minor_(row__, col__) = m(row_, col_);
      }
    }
    return matrixGaussDeterminant(minor_);
  }

  double cofractor(const Matrix& m, int row, int col) {
    if ((row + col) % 2) return -minor(m, row, col);
    else return minor(m, row, col);
  }

  Matrix identityMatrix(int dim) {
    if (dim <= 0) {
      throw std::runtime_error("Matrix dimensions can only be positive [identityMatrix]");
    }
    Matrix result(dim, dim);
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        result(i, j) = i == j ? 1 : 0;
      }
    }
    return result;
  }
  
  // This does not exactly works as Gauss elimination method because it does not transmute rows
  // Since it is not practical with single array realisation
  Matrix gaussElimination(const Matrix& m) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("Gauss elimination is available only for square matrices");
    }
    // This function treats Matrix determinant as invariant
    Matrix result = m;
    // int* row_transmutation;
    int dim = result.getRows();
    int available_row = 0;
    // row_transmutation = new int[dim];

    int* fixed_rows;
    fixed_rows = new int[dim];
    for (int i = 0; i < dim; ++i) {
      fixed_rows[i] = 0;
    }

    for (int col = 0; col < dim; ++col) {
      int main_row = -1;
      for (int row = 0; row < dim; ++row) {
        if (fixed_rows[row]) {
          continue;
        }
        if (!equalNumbers(result(row, col), 0, result.getEpsilon())) {
          main_row = row;
          break;
        }
      }
      if (main_row == -1) {
        continue;
      }
      // std::cout << "[." << main_row << ".]";
      for (int row = available_row; row < dim; ++row) {
        if (!equalNumbers(result(row, col), 0, result.getEpsilon()) 
          && row != main_row  && !fixed_rows[row]) {
          double coef = (result(row, col) / result(main_row, col));
          result.addRows(main_row, row, -coef);
        }
      }
      fixed_rows[main_row] = 1;
    }

    return result;
  }

  Matrix upperTriangle(const Matrix& m) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("upperTriangle is available only for square matrices");
    }
    Matrix result = gaussElimination(m);
    int dim = result.getRows();

    int* fixed_rows = 0;
    fixed_rows = new int[dim];
    for (int i = 0; i < dim; ++i) {
      fixed_rows[i] = 0;
    }

    int cur_row = 0;
    for (int col = 0; col < dim; ++col) {
      int main_row = -1;
      for (int row = cur_row; row < dim; ++row) {
        if (!equalNumbers(result(row, col), 0, result.getEpsilon())) {
          main_row = row;
          break;
        }
      }
      if (main_row != -1) {
        result.swapRows(main_row, cur_row++);
      }
    }

    return result;
  }

  double matrixGaussDeterminant(const Matrix& m) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("Determinant is available only for square matrices");
    }
    Matrix triangle = upperTriangle(m);
    int dim = triangle.getRows();
    double result = 1;
    for (int i = 0; i < dim; ++i) {
      result *= triangle(i, i);
    }
    return result;
  }

  double trace(const Matrix& m) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("Trace is available only for square matrices");
    }
    int dim = m.getRows();
    double result = 0;
    for (int i = 0; i < dim; ++i) {
      result += m(i, i);
    }
    return result;
  }

  Matrix invert(const Matrix& m) {
    if (m.getRows() != m.getColumns()) {
      throw std::runtime_error("Inversion is available only for square matrices");
    }
    double det = matrixGaussDeterminant(m);
    if (equalNumbers(det, 0, m.getEpsilon())) {
      throw std::runtime_error("Determinant == 0, cannot invert matrix");
    }
    int dim = m.getRows();
    Matrix result(dim, dim);
    double det_m = m.determinant();
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        result(i, j) = cofractor(m, i, j) / det_m;
      }
    }
    result = transpose(result);
    return result;
  }

  Matrix transpose(const linalg::Matrix& m) {
    linalg::Matrix result(m.getColumns(), m.getRows());
    for (int i = 0; i < m.getRows(); ++i) {
      for (int j = 0; j < m.getColumns(); ++j) {
        result(j, i) = m(i, j);
      }
    }
    return result;
  }

  Matrix concatenate(const Matrix& m1, const Matrix& m2) {
    if (m1.getRows() != m2.getRows()) {
      throw std::runtime_error("Cannot concatenate matrices, row numbers do not match");
    }
    Matrix result(m1.getRows(), m1.getColumns() + m2.getColumns());
    for (int i = 0; i < m1.getRows(); ++i) {
      for (int j = 0; j < m1.getColumns() + m2.getColumns(); ++j) {
        if (j < m1.getColumns()) {
          result(i, j) = m1(i, j);
        }
        else {
          result(i, j) = m2(i, j - m1.getColumns());
        }
      }
    }
    return result;
  }

  Matrix power(const Matrix& m, int pow) {
    if (m.getRows() != m.getColumns()) {
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
