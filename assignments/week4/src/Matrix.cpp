#include "../include/Matrix.h"

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(nullptr) {
  if (rows <= 0 || cols <= 0) {
    std::string message = "Dimensions must be positive";
    throw MatrixError(message);
  }
}

Matrix::Matrix(const Matrix &other) {
  rows = other.rows;
  cols = other.cols;

  data = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = other.data[i][j];
    }
  }
}

void Matrix::initialize() {
  data = new double* [rows];

  for (int i = 0; i < rows; ++i) {
    data[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = 0.0;
    }
  }
}

int Matrix::getRows() { return rows; }

int Matrix::getColumns() { return cols; }

void Matrix::setRows(int r) { rows = r; }

void Matrix::setCols(int c) { cols = c; }

bool Matrix::isValid() { return data != nullptr; }

void Matrix::print() {
  if (!isValid()) {
    std::string message = "Matrix must be initialized";
    throw MatrixError(message);
  }
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      std::cout<<data[i][j]<<" ";
    }
    std::cout<<"\n";
  }
}
double &Matrix::at(int row, int col) {
  if (row < 0 || row >= rows || col < 0 || col >= cols) {
    std::string msg = "Index out of bounds";
    throw MatrixError(msg);
  }
  return data[row][col];
}

Matrix Matrix::operator+(const Matrix &other) {
  if (rows != other.rows || cols != other.cols) {
    std::string msg = "Matrix dimensions must match for addition";
    throw MatrixError(msg);
  }

  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      result.data[i][j] = data[i][j] + other.data[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator*(const Matrix &other) {
  if (cols != other.rows) {
    std::string msg = "Invalid dimensions for multiplication";
    throw MatrixError(msg);
  }

  Matrix result(rows, other.cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < other.cols; ++j) {
      result.data[i][j] = 0;
      for (int k = 0; k < cols; ++k) {
        result.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  return result;
}

Matrix Matrix::operator=(const Matrix &other) {
  rows = other.rows;
  cols = other.cols;

  data = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = other.data[i][j];
    }
  }

  return *this;
}

Matrix::~Matrix() {
  for (int i = 0; i < rows; ++i) {
    delete[] data[i];
  }
  delete[] data;
}
