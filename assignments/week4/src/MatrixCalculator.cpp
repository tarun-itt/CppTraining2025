#include "MatrixCalculator.h"


const int MIN_LIMIT = 2;
const int MAX_LIMIT = 10;


inline void MatrixCalculator::printHeader(const std::string &title) {
  std::cout << "\n================== " << title << " ==================\n";
}

int MatrixCalculator::readRangedInput(const std::string &message, int min, int max) {
  int value;
  while (true) {
    std::cout << message;
    if (std::cin >> value && value >= min && value <= max) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }
    std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

double MatrixCalculator::readMatrixElement(const std::string &message) {
  double value = 0.0;
  bool valid = false;
  while (!valid) {
    std::cout << message;
    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      valid = true;
    } else {
      std::cout << "Invalid input. Please enter a valid number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return value;
}

void MatrixCalculator::enterMatrix(Matrix &matrix) {
  if (matrix.isValid()) {
    for (int row = 0; row < matrix.getRows(); row++) {
      for (int col = 0; col < matrix.getColumns(); col++) {
        std::string inputMessage = "Enter data (" + std::to_string(row + 1) + ", " + std::to_string(col + 1) + ")";
        matrix.getDataAt(row, col) = readMatrixElement(inputMessage);
      }
    }
  }
}

void MatrixCalculator::inputMatrixDimensions(int &rows, int &cols, const std::string &matrixName) {
  std::string rowMessage = "Enter the number of rows for Matrix " + matrixName + ": ";
  std::string colsMessage = "Enter the number of columns for Matrix " + matrixName + ": ";
  rows = readRangedInput(rowMessage, MIN_LIMIT, MAX_LIMIT);
  cols = readRangedInput(colsMessage, MIN_LIMIT, MAX_LIMIT);
}

void MatrixCalculator::setupMatrix(Matrix &matrix, int rows, int cols) {
  matrix.setRows(rows);
  matrix.setCols(cols);
}

void MatrixCalculator::inputMatrixData(Matrix &matrixA, Matrix &matrixB) {
  std::cout << "\n Enter Matrix-A Data: \n";
  enterMatrix(matrixA);
  std::cout << "\n Enter Matrix-B Data: \n";
  enterMatrix(matrixB);
}

void MatrixCalculator::displayMatrixOperation(Matrix &matrixA, Matrix &matrixB) {
  std::cout << "\nMatrix-A: \n";
  matrixA.print();
  std::cout << "\nMatrix-B: \n";
  matrixB.print();
  std::cout << "\n Result: \n";
}

void MatrixCalculator::performMatrixAddition(Matrix &matrixA, Matrix &matrixB) {
  try {
    displayMatrixOperation(matrixA, matrixB);
    Matrix result = (matrixA + matrixB);
    result.print();
  } catch (const Matrix::MatrixError &e) {
    std::cerr << "Error: " << e.what() << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << "\n";
  }
}

void MatrixCalculator::performMatrixMultiplication(Matrix &matrixA, Matrix &matrixB) {
  try {
    displayMatrixOperation(matrixA, matrixB);
    Matrix result = matrixA * matrixB;
    result.print();
  } catch (const Matrix::MatrixError &e) {
    std::cerr << "Error: " << e.what() << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << "\n";
  }
}

void MatrixCalculator::addMatrices(Matrix &matrixA, Matrix &matrixB) {
  printHeader("Addition");
  
  int matrixARows, matrixACols, matrixBRows, matrixBCols;
  inputMatrixDimensions(matrixARows, matrixACols, "A");
  inputMatrixDimensions(matrixBRows, matrixBCols, "B");

  if (matrixARows == matrixBRows && matrixACols == matrixBCols) {
    setupMatrix(matrixA, matrixARows, matrixACols);
    setupMatrix(matrixB, matrixBRows, matrixBCols);
    inputMatrixData(matrixA, matrixB);
    performMatrixAddition(matrixA, matrixB);
  } else {
    std::cout << "Matrices' dimensions are not compatible for addition! Must have same number of rows and columns\n";
  }
}

void MatrixCalculator::multiplyMatrices(Matrix &matrixA, Matrix &matrixB) {
  printHeader("MATRIX MULTIPLICATION");
  
  int matrixARows, matrixACols, matrixBRows, matrixBCols;
  inputMatrixDimensions(matrixARows, matrixACols, "A");
  inputMatrixDimensions(matrixBRows, matrixBCols, "B");

  if (matrixACols == matrixBRows) {
    setupMatrix(matrixA, matrixARows, matrixACols);
    setupMatrix(matrixB, matrixBRows, matrixBCols);
    inputMatrixData(matrixA, matrixB);
    performMatrixMultiplication(matrixA, matrixB);
  } else {
    std::cout << "Matrices' dimensions are not compatible for multiplication! Number of columns in Matrix A must be equal to number of rows in Matrix B\n";
    return;
  }
}

void MatrixCalculator::run() {
  Matrix matrixA;
  Matrix matrixB;
  bool loopRunning = true;

  while (loopRunning) {
    printHeader("MATRIX CALCULATOR");
    std::cout << "1. Add Matrices (A + B)\n";
    std::cout << "2. Multiply Matrices (A * B)\n";
    std::cout << "3. Exit\n\n";

    int choice = readRangedInput("Enter your choice (1-3): ", (MenuOption::ADD_MATRICES), (MenuOption::EXIT));

    switch (choice) {
      case MenuOption::ADD_MATRICES:
        addMatrices(matrixA, matrixB);
        break;
      case MenuOption::MULTIPLY_MATRICES:
        multiplyMatrices(matrixA, matrixB);
        break;
      case MenuOption::EXIT:
        std::cout << "\n\n Bye! \n";
        loopRunning = false;
        break;
      default:
        std::cout << "Invalid choice. Please enter a valid option.\n";
        break;
    }
  }
}