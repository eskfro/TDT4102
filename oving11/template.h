#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <array>

template<typename Type, int Size>
class myArray {
    Type elements[Size];
public:
    // myArray() {};
 
    int getSize() {return Size;}

    Type at(int n) {return elements[n];}

    void fill(Type t) {
        for (int i = 0; i < Size; i++) {
            elements[i] = t;
        }
    }

    void print() {
        for (int i = 0; i < Size; i++) {
            std::cout << elements[i] << "  ";
        }
        std::cout << "\n";
    }

};




template<typename T>
void shuffle(std::vector<T>& vec) {
    int size = vec.size();
    std::random_device rd;
    unsigned int seed = rd();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution dist(0, size - 1);

    for (int i = 0; i < (2 * size); i++) {
        int indx_1 = dist(engine);
        int indx_2 = dist(engine);
        // std::cout << indx_1 << "  " << indx_2 << "\n";
        std::swap(vec.at(indx_1), vec.at(indx_2));
    }
}





template<typename T>
void print_vec(std::vector<T> vec) {
    for (T i : vec) {
        std::cout << i << "   ";
    }
    std::cout << "\n";
}




template<typename T>
T maximum(T left, T right) {
    if (left > right || left == right) {return left;} 
    if (right > left)                  {return right;}
    return right;
}

