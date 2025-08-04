#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include "Matrix.h"

#include <limits>

namespace MatrixCalculator {
  int readRangedInput(const std::string &message, int min, int max);
  double readMatrixElement(const std::string &message);

  void enterMatrix(Matrix &matrix);
  void inputMatrixDimensions(int &rows, int &cols, const std::string &matrixName);
  void setupMatrix(Matrix &matrix, int rows, int cols);
  void inputMatrixData(Matrix &matrixA, Matrix &matrixB);
  void displayMatrixOperation(Matrix &matrixA, Matrix &matrixB);
  void performMatrixAddition(Matrix &matrixA, Matrix &matrixB);
  void performMatrixMultiplication(Matrix &matrixA, Matrix &matrixB);
  void addMatrices(Matrix &matrixA, Matrix &matrixB);
  void multiplyMatrices(Matrix &matrixA, Matrix &matrixB);

  inline void printHeader(const std::string &title);

  enum MenuOption { ADD_MATRICES = 1, MULTIPLY_MATRICES, EXIT };

  void run();
};

#endif