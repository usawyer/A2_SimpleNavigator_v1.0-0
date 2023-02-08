#ifndef SRC_MODEL_MATRIX_MATRIX_H_
#define SRC_MODEL_MATRIX_MATRIX_H_

#include <cmath>
#include <iostream>

constexpr double E = 1e-7;

class Matrix {
 public:
  Matrix();
  explicit Matrix(int size);
  Matrix(int size, std::initializer_list<std::initializer_list<double>> list);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  unsigned int GetSize();
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void MulNumber(const double num);
  void SetToZero();
  Matrix& operator=(const Matrix& other);
  void operator+=(const Matrix& other);
  void operator*=(const double num);
  double& operator()(int rows, int cols);

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;

  void CreateMatrix();
  void DeleteMatrix();
  int EqLoop(const Matrix& other);
};

#endif  // SRC_MODEL_MATRIX_MATRIX_H_
