

#include "./../include/layer.h"



// class Layer is used to discribe the Layer format
// One Layer contains weight, bias, diff and so on



Layer::Layer()
{
    ;
}

Layer::Layer(int input_node, int output_node)
{
    this->input_node = input_node;
    this->output_node = output_node;

    // initial input and output node
    data_in = Data(1, input_node);
    data_out = Data(1, output_node);
    loss = Data(1, output_node);
    for (int i = 0; i < input_node; i++)
    {
        data_in.data[0][i] = 0;
    }
    for (int i = 0; i < output_node; i++)
    {
        data_out.data[0][i] = 0;
        loss.data[0][i] = 0;
        // bias_diff.data[0][i] = 0;
    }
    // for (int i = 0; i < input_node; i++)
    // {
    //     for (int j = 0; j < output_node; j++)
    //     {
    //         weight_diff.data[i][j] = 0;
    //     }
    // }
}
Layer::~Layer()
{
    // delete weight.data;
    // delete bias.data;
}

void Layer::initWeight()
{
    weight = Data(input_node, output_node);
    bias = Data(1, output_node);

    weight_diff = Data(input_node, output_node);
    bias_diff = Data(1, output_node);

    for (int j = 0; j < output_node; j++)
    {
        for (int i = 0; i < input_node; i++)
        {
            weight_diff.data[i][j] = 0;
        }
        bias_diff.data[0][j] = 0;
    }

    weight.init();
    bias.init();
    // weight.print();
    // bias.print();
}

void Layer::MAC()
{
    #pragma omp parallel for
    for (int i = 0; i < output_node; i++)
    {
        data_out.data[0][i] = 0;
        for (int j = 0; j < input_node; j++)
        {
            data_out.data[0][i] += data_in.data[0][j] * weight.data[j][i];
        }
        data_out.data[0][i] += bias.data[0][i];
    }
}

void Layer::reLU()
{
    #pragma omp parallel for
    for (int i = 0; i < output_node; i++)
    {
        if (data_in.data[0][i] <= 0)
            data_out.data[0][i] = 0;
        else
            data_out.data[0][i] = data_in.data[0][i];
    }
}

void Layer::sigmoid()
{
    #pragma omp parallel for
    for (int i = 0; i < output_node; i++)
    {
        data_out.data[0][i] = 1 / (1 + exp(-data_in.data[0][i]));
    }
}

void Layer::softmax()
{
    float sum = 0;
    for (int i = 0; i < output_node; i++)
    {
        sum += exp(data_in.data[0][i]);
    }
    #pragma omp parallel for
    for (int i = 0; i < output_node; i++)
    {
        data_out.data[0][i] = exp(data_in.data[0][i]) / sum;
    }
}