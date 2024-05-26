#pragma once

#include <iostream>
#include <math.h>
#include <cassert>

class Matrix {
    double rows;
    double cols;
    double **arr;

public:
    Matrix(int nRows, int nColumns) {
        assert(nRows > 0 && nColumns > 0);
        rows = nRows;
        cols = nColumns;
        arr = new double*[nRows];
        for (int i = 0; i < nRows; i++) {
            arr[i] = new double[nColumns];
        }
        for (int r = 0; r < nRows; r++) {
            for (int c = 0; c < nColumns; c++) {
                arr[r][c] = 0;
            }
        }
    }   

    explicit Matrix(int nRows) : Matrix(nRows, nRows) {
        for (int i = 0; i < nRows; i++) {
            arr[i][i] = 1;
        }
    }

    Matrix(const Matrix& rhs) {
        cols = rhs.cols;
        rows = rhs.rows;
        arr = new double*[rows];
        for (int r = 0; r < rows; r++) {
            arr[r] = new double[cols];
            for (int c = 0; c < cols; c++) {
                arr[r][c] = rhs.arr[r][c];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete [] arr[i];
        }
        delete [] arr; 
    } 
    
    double get(int row, int col) const;
    void set(int row, int col, double value);
    double* operator[](int index);
    int getRows() const;
    int getColumns() const;

    friend std::ostream& operator<<(std::ostream& os, Matrix& m) {
        for (int r = 0; r < m.rows; r++) {
            for (int c = 0; c < m.cols; c++) {
                os << m[r][c] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    arr[r][c] = other.arr[r][c];
                }   
            }
        }
    return *this;
    }
    
    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < other.rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                this->arr[i][j] += other.arr[i][j];
            }
        }
    return *this;
    }

    Matrix operator+(const Matrix other) {
        assert(this->cols == other.cols && this->rows == other.rows);
        Matrix sum(rows, cols);
        sum += *this;
        sum += other;
        return sum;
    }
};
