//
// Created by Marco on 15.04.2020.
//

#ifndef GEIGERCOUNTER_ARRAY_H
#define GEIGERCOUNTER_ARRAY_H

template <typename T>
class Array {

public:
    Array();
    ~Array();

    void add(T elem);
    int get_size();

private:

    T* ptr;
    int size;
    int MAX;

};


#endif //GEIGERCOUNTER_ARRAY_H
