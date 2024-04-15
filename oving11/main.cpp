#include <iostream>
#include <iomanip>

#include "Stopwatch.h"
#include "func.h"
#include "optimizationTask.h"
#include "template.h"

//Dersom kjører fra cmd
// #include "Stopwatch.cpp"
// #include "func.cpp"
// #include "optimizationTask.cpp"

int main() {
    std::cout << "\n\n\n\n\nmain: --- - - - - - - - - - -  - - - - - - - - \n";
    constexpr int BIG = 1000000;

    if (1) {
        //Unngår vitenskapelig notasjon
        std::cout << std::fixed << std::setprecision(10);

        //OPPGAVE 1 og 2 - - - - - - - - - - - - -  - - - - -  - - - 

        timer_function(t_unique_ptr, BIG, "UNIQUE PTR");
        timer_function(t_shared_ptr, BIG, "SHARED PTR");

        //Konklusjon: Unique ptr er raskere.
        
        timer_function(t_stack_allocation, BIG, "STACK ALLOCATION");
        timer_function(t_heap_allocation,  BIG,  "HEAP ALLOCATION");

        //Konklusjon: Stack allocation er raskerer. 

        analyze_vector();
        timer_function(vector_test_normal,  100, "VECTOR NORMAL");
        timer_function(vector_test_reserve, 100, "VECTOR RESERVE");
        timer_function(vector_test_resize,  100, "VECTOR RESIZE");

        //OPPGAVE 3 - - -- - - -  - - - - - - - -  - - - 

        double time_before_opt_debug   = 7.312034;
        double time_before_opt_release = 4.014137;

        double time_after_opt_debug = 4.616355;
        double time_after_opt_release = 3.473728;

        timer_function(optimizationTask, 1, "OPTIMIZATION TASK");
    }
    //OPPGAVE 4 - - -- - - -  - - - - - - - -  - - - 

    int a = 1;
    int b = 2; 
    int c = maximum<int>(a, b);
    std::cout << c << "\n";

    double d = 2.4;
    double e = 3.2;
    double f = maximum<double>(d, e);
    std::cout << f << "\n\n\n";

    //For at det skal fungere med egendefinerte klasser må man overlaste 
    // [<, >] operatorene for den gitte klassen. 


    //Test av template funksjoner
    if (1) {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
        print_vec(v);
        shuffle(v);
        print_vec(v);
        std::cout << "\n";

        std::vector<double> dd{1.2, 2.2, 3.2, 4.2};
        print_vec(dd);
        shuffle(dd);
        print_vec(dd);
        std::cout << "\n";

        std::vector<std::string> ss{"one", "two", "three", "four", "five"};
        print_vec(ss);
        shuffle(ss);
        print_vec(ss);
    }

    //Test av template klasser

    if (1) {
        myArray<int, 10> array1;
        array1.print();
        array1.fill(20);
        array1.print();
        std::cout << array1.at(2) << "\n";
        array1.print();
        std::cout << "\n\n";

        myArray<std::string, 5> array2;
        array2.print();
        array2.fill("test");
        array2.print();
        std::cout << array2.at(2) << "\n";
        array2.print();
        std::cout << "\n\n";
    }
    
    return 0;
}