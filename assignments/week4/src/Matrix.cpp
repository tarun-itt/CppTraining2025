#include "Matrix.h"

Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(nullptr) {
  if (rows <= 0 || cols <= 0) {
    std::string message = "Dimensions must be positive";
    throw MatrixError(message);
  }
  initialize();
}

Matrix::Matrix(const Matrix &other) {
  rows = other.rows;
  cols = other.cols;
  data = nullptr;

  if (other.data != nullptr && rows > 0 && cols > 0) {
    data = new double *[rows];
    for (int currentRow = 0; currentRow < rows; ++currentRow) {
      data[currentRow] = new double[cols];
      for (int currentCol = 0; currentCol < cols; ++currentCol) {
        data[currentRow][currentCol] = other.data[currentRow][currentCol];
      }
    }
  }
}

void Matrix::initialize() {
  if (data != nullptr) {
    for (int currentRow = 0; currentRow < rows; ++currentRow) {
      delete[] data[currentRow];
    }
    delete[] data;
  }

  if (rows > 0 && cols > 0) {
    data = new double *[rows];
    for (int currentRow = 0; currentRow < rows; ++currentRow) {
      data[currentRow] = new double[cols];
      for (int currentCol = 0; currentCol < cols; ++currentCol) {
        data[currentRow][currentCol] = 0.0;
      }
    }
  } else {
    data = nullptr;
  }
}

int Matrix::getRows() { 
  return rows; 
}

int Matrix::getColumns() { 
  return cols; 
}

void Matrix::setRows(int rows) { 
  this->rows = rows; 
  initialize(); 
}

void Matrix::setCols(int cols) { 
  this->cols = cols; 
  initialize(); 
}

bool Matrix::isValid() { 
  return data != nullptr; 
}

void Matrix::print() {
  if (!isValid()) {
    std::string message = "Matrix must be initialized";
    throw MatrixError(message);
  }

  for (int currentRow = 0; currentRow < rows; currentRow++) {
    for (int currentCol = 0; currentCol < cols; currentCol++) {
      std::cout << data[currentRow][currentCol] << " ";
    }
    std::cout << "\n";
  }
}

double &Matrix::getDataAt(int row, int col) {
  if (!isValid()) {
    throw MatrixError("Matrix not initialized");
  }

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
  for (int currentRow = 0; currentRow < rows; ++currentRow) {
    for (int currentCol = 0; currentCol < cols; ++currentCol) {
      result.data[currentRow][currentCol] = data[currentRow][currentCol] + other.data[currentRow][currentCol];
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
  for (int currentRow = 0; currentRow < rows; ++currentRow) {
    for (int currentCol = 0; currentCol < other.cols; ++currentCol) {
      result.data[currentRow][currentCol] = 0;
      for (int currentCol = 0; currentCol < cols; ++currentCol) {
        result.data[currentRow][currentCol] += data[currentRow][currentCol] * other.data[currentCol][currentCol];
      }
    }
  }
  return result;
}

Matrix& Matrix::operator=(const Matrix &other) {
  if (this != &other) {

    if (data != nullptr) {
      for (int currentRow = 0; currentRow < rows; ++currentRow) {
        delete[] data[currentRow];
      }
      delete[] data;
    }

    rows = other.rows;
    cols = other.cols;
    data = nullptr;

    if (other.data != nullptr && rows > 0 && cols > 0) {
      data = new double *[rows];
      for (int currentRow = 0; currentRow < rows; ++currentRow) {
        data[currentRow] = new double[cols];
        for (int currentCol = 0; currentCol < cols; ++currentCol) {
          data[currentRow][currentCol] = other.data[currentRow][currentCol];
        }
      }
    }
  }
  return *this;
}

Matrix::~Matrix() {
  if (data != nullptr) {
    for (int currentRow = 0; currentRow < rows; ++currentRow) {
      delete[] data[currentRow];
    }
    delete[] data;
  }
}
