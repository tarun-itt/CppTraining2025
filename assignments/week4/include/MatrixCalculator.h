#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include "Matrix.h"

#include <iostream>
#include <limits>
#include <string.h>

namespace MatrixCalculator {

int readIntInput(const std::string &message, int min, int max);
double readDoubleInput(const std::string &message);

void enterMatrix(Matrix &matrix);
void displayMatrices(Matrix &matrixA, Matrix &matrixB);
void addMatrices(Matrix &matrixA, Matrix &matrixB);
void multiplyMatrices(Matrix &matrixA, Matrix &matrixB);

inline void printHeader(const std::string &title);

enum MenuOption { ADD_MATRICES = 1, MULTIPLY_MATRICES, EXIT };

void run();
};

#endif