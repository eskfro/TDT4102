#include "Matrix.h"

double Matrix::get(int row, int col) const {
    return arr[row][col];
}

void Matrix::set(int row, int col, double value) {
    arr[row][col] = value;
}

double* Matrix::operator[](int index) {
    return arr[index];
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return cols;
}
