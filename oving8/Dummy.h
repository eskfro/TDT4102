#pragma once
#include <iostream>

class Dummy {
public:
    int *num;
    Dummy() {
        num = new int{0};
    }
    Dummy(const Dummy& d) : Dummy() {
        delete num;
        num = new int{*d.num};
    }

    ~Dummy() {
        delete num;
    }

    Dummy& operator=(const Dummy& other) {
        if (this != &other) {
            delete num;
            this->num = new int{*other.num};
        }
        return *this;
    }
};

void dummyTest();