
#include "./../include/data.h"

// class Data is used to discribe the data format of the CMLF
// The data can be indexed through the variable : data
// It can be used to store weight or bias.
// Several variable and method of the class is provided


Data::Data()
{
    ;
}

// If we save weight, we use 2D
// If we save bias, we use 1D, as the first index is 0
Data::Data(int height, int width)
{
    this->height = height;
    this->width = width;
    data = new float *[height];
    for (int i = 0; i < height; i++)
    {
        data[i] = new float[width];
    }
}
Data::~Data()
{
    // for (int i = 0; i < height; i++)
    // {
    //     delete[] data[i];
    // }
}

// Initial the data matrix: random, from -1~1
void Data::init()
{
    // generate random data
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            data[i][j] = 2.0 * rand() / RAND_MAX - 1.0;
        }
    }
}

// print the data matrix, to check
void Data::print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
