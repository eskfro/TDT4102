#include "Stopwatch.h"
#include <vector>
#include <iostream>

// Utdelt kode til oppgave 3

void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue){
    //Fjerner hele denne tingen 
    // for (int row = 0; row < size; row++){
    //     for (int col = 0; col < size; col++){
    //         bool isDiagonal = (row == col);
    //         if (isDiagonal){
    //             matrix.at(row).at(col) = newValue;
    //         }
    //     }
    // }

    //Dette er en litt raskere kode sikkert
    for (int i = 0; i < matrix.size(); i++) {
        matrix.at(i).at(i) = newValue;
    }

}

double sumMatrix(std::vector<std::vector<double>> matrix){
    //Trenger bare regnes ut en gang
    int size = matrix.size();
    double sum;
    //Itererer gjennom row først for å utnytte cache-minne
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            //Fjerner unødvendig linje med kode
            sum += matrix.at(row).at(col);      
        }
    }
    return sum;
}

void optimizationTask() {
    
    const int matrixSize = 10000;

    // Create a matrix with zeros
    std::vector<std::vector<double>> matrix;
    
    for (int i = 0; i < matrixSize; i++){
        std::vector<double> column;
        for (int j = 0; j < matrixSize; j++){
            column.push_back(0.0);
        }
        matrix.push_back(column);
    }

    // Set all elements on the diagonal to 0.41
    setDiagonalValue(matrix, 0.41);
    
    // Sum all elements in the matrix
    double total = sumMatrix(matrix);

    double coolerNumber = total + 2.0;
    std::cout << "TDT" << coolerNumber << std::endl;
}