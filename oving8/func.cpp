#include "func.h"

void createFibonacci() {
    int n;
    std::cout << "insert wanted array size:  ";
    std::cin >> n;

    int* result = new int[n];
    fillInFibonacciNumbers(result, n);
    printArray(result, n);
}

void printArray(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " , ";
    }
    std::cout << std::endl;
}
void fillInFibonacciNumbers(int* result, int length) {
    result[0] = 0;
    if (length == 0) {
        return;
    }
    result[1] = 1;
    if (length == 1) {
        return;
    }
    for (int i = 2; i < length + 2; i++) {
        result[i] = result[i - 1] + result[i - 2];
    }
}

void testert(Matrix m) {
    std::cout << " ~ matrise: " << m.getRows() << " x " << m.getColumns() << "\n";
    std::cout << m << "\n";
    std::cout << "[ ] overlasting: " << m[1][1] << "\n\n";
    std::cout << std::endl;
}


