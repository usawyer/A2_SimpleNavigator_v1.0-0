#include "matrix.h"

Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = NULL;
}

Matrix::Matrix(int size) : rows_(size), cols_(size) {
  if (rows_ < 1 || cols_ < 1)
    throw std::out_of_range("Incorrect matrix size value");
  CreateMatrix();
}

Matrix::Matrix(int size,
               std::initializer_list<std::initializer_list<double>> list)
    : Matrix(size) {
  int i = 0, j = 0;
  for (const auto& r : list) {
    for (const auto& c : r) {
      matrix_[i][j] = c;
      ++j;
    }
    j = 0;
    ++i;
  }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.cols_ = other.rows_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() {
  if (matrix_) {
    DeleteMatrix();
  }
  rows_ = 0;
  cols_ = 0;
}

unsigned int Matrix::GetSize() { return rows_; }

void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  SetToZero();
}

void Matrix::SetToZero() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}

void Matrix::DeleteMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool Matrix::EqMatrix(const Matrix& other) {
  bool result = true;
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    result = false;
  } else {
    if (EqLoop(other) != cols_ * rows_) {
      result = false;
    }
  }
  return result;
}

int Matrix::EqLoop(const Matrix& other) {
  int match = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) < E) {
        match++;
      }
    }
  }
  return match;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::out_of_range("Different matrix dimensions!");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  if (std::isnan(num) || std::isinf(num))
    throw std::out_of_range("Invalid number!");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

Matrix& Matrix::operator=(const Matrix& other) {
  DeleteMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

void Matrix::operator+=(const Matrix& other) { return SumMatrix(other); }

void Matrix::operator*=(const double num) { return MulNumber(num); }

double& Matrix::operator()(int rows, int cols) {
  if (rows_ <= rows || cols_ <= cols || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect matrix indices!");
  }
  return matrix_[rows][cols];
}
