#include "func.h"
#include "Dummy.h"
#include "Matrix.h"

// //Bruker denne dersom jeg kjører fra cmd ...
// #include "func.cpp"
// #include "Dummy.cpp"
// #include "Matrix.cpp"

int main(){
    std::cout << "\n\n --- - - - - - MAIN - - - - - -- " << "\n\n";

    //Oppgave 5
    std::cout << "(+) OPERATOR TEST" << "\n\n";
    Matrix A = Matrix(2);
    Matrix B = Matrix(2);
    Matrix C = Matrix(2);
    A.set(0, 0, 1.0);
    A.set(0, 1, 2.0);
    A.set(1, 0, 3.0);
    A.set(1, 1, 4.0);
    B.set(0, 0, 4.0);
    B.set(0, 1, 3.0);
    B.set(1, 0, 2.0);
    B.set(1, 1, 1.0);
    C.set(0, 0, 1.0);
    C.set(0, 1, 3.0);
    C.set(1, 0, 1.5);
    C.set(1, 1, 2.0);
    std::cout << A << "\n";
    std::cout << B << "\n";
    std::cout << C << "\n";
    A += B + C;
    std::cout << "etter summering (A += B + C) " << "\n\n";
    std::cout << A << "\n";
    std::cout << B << "\n";
    std::cout << C << "\n";

    std::cout << "(+=) OPERATOR TEST" << "\n\n";
    Matrix M1 = Matrix(4);
    Matrix M2 = Matrix(4);
    M1.set(0, 3, 7.9);
    M2.set(0, 3, 1.0);
    testert(M1);
    testert(M2);
    M1 += M2;
    testert(M1);


    //Oppgave 4
    std::cout << "KOPI CONSTR. TEST" << "\n\n";
    Matrix M11 = Matrix(3, 5);
    M11.set(1, 1, 44);
    Matrix M22{M11};
    testert(M11);
    testert(M22); 

    std::cout << "(=) OPERATOR TEST" << "\n\n";
    Matrix M3 = Matrix(3, 7);
    Matrix M4 = Matrix(3, 7);
    testert(M3);
    testert(M4);
    M3.set(2, 1, 22);
    M4 = M3;
    testert(M3);
    testert(M4);


    //Oppgave 3
    std::cout << "DUMMY TEST " << "\n\n";
    dummyTest();

    //Oppgave 2
    std::cout << "MATRISE TEST" << "\n\n";
    Matrix I = Matrix(5);
    Matrix M = Matrix(3, 6);
    testert(I);
    testert(M);
    
    //Oppgave 1
    // std::cout << "FIBONACCI TEST" << "\n\n";
    // int* result = new int[10];
    // int length = 10;
    // fillInFibonacciNumbers(result, length);
    // printArray(result, length);
    // createFibonacci();

    return 0;
}
