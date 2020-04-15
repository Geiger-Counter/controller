//
// Created by Marco on 15.04.2020.
//

#include "Array.h"

template <typename T>
Array::Array() {

    int start = 10;
    ptr = new T[start];
    MAX = start;
    size = 0;

}

Array::~Array() {
    ptr = nullptr;
    MAX = 0;
    size = 0;
}

template <typename T>
void Array::add(T elem) {
    if(size <= MAX) {
        
    }
}