#pragma once
#include <initializer_list>
#include <iostream>

namespace linalg {
  class Matrix {
  private:
    double* m_ptr;
    int m_rows;
    int m_columns;
    static double epsilon;
  public:
    int getRows() const;
    int getColumns() const;
    int getVolume() const;
    double getEpsilon() const;
    bool empty() const;
    double determinant();
    void printMatrix(std::ostream& os) const;

    void reshape(int rows, int cols);
    void addRows(int source_row, int target_row, double coef);

    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(double scalar);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator-() const;

    Matrix();
    Matrix(int rows);
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix(std::initializer_list<double> lst);
    Matrix(std::initializer_list<std::initializer_list<double>> lst);
    ~Matrix();
  };

  inline Matrix operator*(double scalar, Matrix& m) { return m * scalar; }

  std::ostream& operator<<(std::ostream& os, const Matrix& m);

  bool equalNumbers(double a, double b, double eps);

  Matrix identityMatrix(int dim);

  Matrix gaussElimination(const Matrix& m);

  Matrix transpose(const Matrix& m);

  Matrix concatenate(const Matrix& m1, const Matrix& m2);

  Matrix power(const Matrix& m, int power);
}
