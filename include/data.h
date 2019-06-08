#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <stdlib.h>

class Data
{
public:
    float **data;
    int height;
    int width;
    Data(int height, int width);
    Data();
    ~Data();

    void init();
    void print();
};

#endif