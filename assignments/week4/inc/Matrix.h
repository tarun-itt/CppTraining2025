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
    Matrix(int rows, int cols);
    Matrix(const Matrix &other);

    int getRows();
    int getColumns();
    void setRows(int rows);
    void setCols(int cols);
    double &getDataAt(int row, int col);
    void initialize();
    bool isValid();
    void print();

    Matrix operator+(const Matrix &other);
    Matrix operator*(const Matrix &other);
    Matrix& operator=(const Matrix &other);

    ~Matrix();

    class MatrixError : public std::runtime_error {
      public: 
        explicit MatrixError(const std::string &message): std::runtime_error("Matrix Error:" + message) {}
    };
};

#endif