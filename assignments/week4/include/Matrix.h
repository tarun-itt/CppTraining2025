#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <string>

class Matrix {

private:
  int rows;
  int cols;
  double **data;

public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix &other);

  int getRows();
  int getColumns();
  void setRows(int rows);
  void setCols(int cols);
  double &at(int row, int col);
  void initialize();
  bool isValid();
  void print();

  Matrix operator+(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator=(const Matrix &other);

  ~Matrix();

  class MatrixError : public std::runtime_error {
  public:
    explicit MatrixError(std::string &message)
        : std::runtime_error("Matrix Error:" + message) {}
  };
};

#endif