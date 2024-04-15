#include "Stopwatch.h"
#include "func.h"

void timer_function(void (*funcPtr)(), int n, std::string title) {
    Stopwatch s;
    std::cout << "    timer_function: " << title << "\n";
    s.start();
    for (int i = 0; i < n; i++) {
        funcPtr();
    }
    double duration_ms = s.stop() * 1000.0;
    std::cout << "        # of repetitions: " << n << " | average duration: "
    << duration_ms / n << " [ms]\n\n";
}


void vector_test_normal() {
    std::vector<int> v;
    for (int i = 0; i < 1000000; i++) {
        v.push_back(5);
    }
}


void vector_test_reserve() {
    std::vector<int> v;
    v.reserve(1000000);
    for (int i = 0; i < 1000000; i++) {
        v.push_back(5);
    }
}


void vector_test_resize() {
    std::vector<int> v;
    v.resize(1000000);
    for (int i = 0; i < 1000000; i++) {
        v.at(i) = 5;
    }
}


void analyze_vector() {
    std::cout << "    analyze_vector: \n";
    std::vector<int> v;
    
    //Denne
    v.reserve(20);
    // v.resize(20);

    for (int i = 0; i<20; i++) {
        std::cout << "        size: " << v.size() << " | capacity: " << v.capacity() << "\n";
        v.push_back(i); 
    }
}


void t_stack_allocation() {
    constexpr int size = 10000;
    std::array<int, size> arr1;
}


void t_heap_allocation() {
    constexpr int size = 10000;
    std::array<int, size>* arr2 = new std::array<int, size>;
    delete arr2;
}


void t_unique_ptr() {
    std::unique_ptr<int> p = std::make_unique<int>(5);
}


void t_shared_ptr() {
    std::shared_ptr<int> p = std::make_shared<int>(5);
}


void test() {
    int p = 0;
    for (int i = 0; i < 100000; i++) {
        p++;
    }
}

