#include "../include/MatrixCalculator.h"

#include <exception>

const int MIN_LIMIT = 2;
const int MAX_LIMIT = 10;

inline void MatrixCalculator::printHeader(const std::string &title) {
  std::cout << "\n================== " << title << " ==================\n";
}

int MatrixCalculator::readIntInput(const std::string &message, int min,
                                   int max) {
  int value;
  while (true) {
    std::cout << message;
    if (std::cin >> value && value >= min && value <= max) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }
    std::cout << "Invalid input. Please enter a number between " << min
              << " and " << max << ".\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

double MatrixCalculator::readDoubleInput(const std::string &message) {
  double value;
  while (true) {
    std::cout << message;
    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }
    std::cout << "Invalid input. Please enter a valid number.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void MatrixCalculator::enterMatrix(Matrix &matrix) {
  matrix.initialize();

  if (matrix.isValid()) {
    for (int row = 0; row < matrix.getRows(); row++) {
      for (int col = 0; col < matrix.getColumns(); col++) {
        std::string inputMessage = "Enter data (" + std::to_string(row + 1) +
                                   ", " + std::to_string(col + 1) + ")";
        matrix.at(row, col) = readDoubleInput(inputMessage);
      }
    }
  }
}

void MatrixCalculator::displayMatrices(Matrix &matrixA, Matrix &matrixB) {
  printHeader("CURRENT MATRICES");
  try {
    std::cout << "\n Matrix A: \n";
    matrixA.print();

    std::cout << "\n Matrix B: \n";
    matrixA.print();
  } catch (const Matrix::MatrixError &e) {
    std::cout << e.what();
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << "\n";
  }
}

void MatrixCalculator::addMatrices(Matrix &matrixA, Matrix &matrixB) {
  printHeader("Addition");
  std::string rowMessageMatrixA = "Enter the number of rows for Matrix A: ";
  std::string colsMessageMatrixA = "Enter the number of columns for Matrix A: ";
  int matrixARows = readIntInput(rowMessageMatrixA, MIN_LIMIT, MAX_LIMIT);
  int matrixACols = readIntInput(colsMessageMatrixA, MIN_LIMIT, MAX_LIMIT);

  std::string rowMessageMatrixB = "Enter the number of rows for Matrix B: ";
  std::string colsMessageMatrixB = "Enter the number of columns for Matrix B: ";
  int matrixBRows = readIntInput(rowMessageMatrixB, MIN_LIMIT, MAX_LIMIT);
  int matrixBCols = readIntInput(colsMessageMatrixB, MIN_LIMIT, MAX_LIMIT);

  if (matrixARows == matrixBRows && matrixACols == matrixBCols) {
    matrixA.setRows(matrixARows);
    matrixA.setCols(matrixACols);
    matrixB.setRows(matrixBRows);
    matrixB.setCols(matrixBCols);

    std::cout << matrixA.getRows()<<"\n Enter Matrix-A Data: \n";
    enterMatrix(matrixA);
    std::cout << "\n Enter Matrix-B Data: \n";
    enterMatrix(matrixB);

    try {
      std::cout<<"\n Matrix-A: \n";
      matrixA.print();

      std::cout<<"\n Matrix-B: \n";
      matrixB.print();

      std::cout << "\n Result: \n";
      Matrix result = (matrixA + matrixB);
      result.print();

    } catch (const Matrix::MatrixError &e) {
      std::cerr << "Error: " << e.what() << "\n";
    } catch (const std::exception &e) {
      std::cerr << "Unexpected error: " << e.what() << "\n";
    }
  } else {
    std::cout << "Both matrices are not addition compatible!\n";
  }
}

void MatrixCalculator::multiplyMatrices(Matrix &matrixA, Matrix &matrixB) {
  printHeader("MATRIX MULTIPLICATION");
  std::string rowMessageMatrixA = "Enter the number of rows for Matrix A: ";
  std::string colsMessageMatrixA = "Enter the number of columns for Matrix A: ";
  int matrixARows = readIntInput(rowMessageMatrixA, MIN_LIMIT, MAX_LIMIT);
  int matrixACols = readIntInput(colsMessageMatrixA, MIN_LIMIT, MAX_LIMIT);

  std::string rowMessageMatrixB = "Enter the number of rows for Matrix B: ";
  std::string colsMessageMatrixB = "Enter the number of columns for Matrix B: ";
  int matrixBRows = readIntInput(rowMessageMatrixB, MIN_LIMIT, MAX_LIMIT);
  int matrixBCols = readIntInput(colsMessageMatrixB, MIN_LIMIT, MAX_LIMIT);

  if (matrixACols == matrixBRows) {
    matrixA.setRows(matrixARows);
    matrixA.setCols(matrixACols);
    matrixB.setRows(matrixBRows);
    matrixB.setCols(matrixBCols);

    std::cout << "\n Enter Matrix-A Data: \n";
    enterMatrix(matrixA);
    std::cout << "\n Enter Matrix-B Data: \n";
    enterMatrix(matrixB);
    try{
      Matrix result = matrixA * matrixB;

      std::cout << "\n Result: \n";
      result.print();

    } catch (const Matrix::MatrixError &e) {
      std::cerr << "Error: " << e.what() << "\n";
    } catch (const std::exception &e) {
      std::cerr << "Unexpected error: " << e.what() << "\n";
    }
  } else {
    std::cout << "Both matrices must be initialized first!\n";
    return;
  }
}

void MatrixCalculator::run() {
  Matrix matrixA;
  Matrix matrixB;

  while (true) {
    printHeader("MATRIX CALCULATOR");
    std::cout << "1. Add Matrices (A + B)\n";
    std::cout << "2. Multiply Matrices (A * B)\n";
    std::cout << "3. Exit\n\n";

    int choice =
        readIntInput("Enter your choice (1-3): ", (MenuOption::ADD_MATRICES),
                     (MenuOption::EXIT));
    switch (choice) {
    case MenuOption::ADD_MATRICES:
      addMatrices(matrixA, matrixB);
      break;
    case MenuOption::MULTIPLY_MATRICES:
      multiplyMatrices(matrixA, matrixB);
      break;
    case MenuOption::EXIT:
      std::cout << "\n\n Bye! \n";
      return;
    }
  }
}
