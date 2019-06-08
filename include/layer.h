#ifndef LAYER_H
#define LAYER_H

#include <cmath>
#include "./../include/data.h"

class Layer
{
public:
    Data weight;
    Data bias;
    Data weight_diff;
    Data bias_diff;
    Data data_in;
    Data data_out;
    Data loss;
    int input_node;
    int output_node;
    Layer(int input_node, int output_node);
    Layer();
    ~Layer();

    void initWeight();

    void MAC();
    void reLU();
    void sigmoid();
    void softmax();
};

#endif