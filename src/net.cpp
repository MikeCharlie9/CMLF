#include <vector>
#include <cmath>


#include "./../include/net.h"


// class Net is used to discribe the net structure
// It contains all layers in the net


Net::Net()
{
    ;
}

// layer_node store the number of nodes in each layer,
// including input nodes and output nodes.
// layer_mode store the mode of the layer, determing the
// function of the layer, such as MLP, RELU, SIGMOID and so on
// Please refer to the define.h
// So, you can find that the size of layer_mode is smaller than layer_node
Net::Net(std::vector<int> layer_node, std::vector<int> layer_mode, float learning_rate)
{
    this->layer_node = layer_node;
    this->layer_mode = layer_mode;
    this->learning_rate = learning_rate;
}

Net::~Net()
{
    // delete layer;
}

void Net::init()
{
    layer_size = layer_mode.size();
    getTime();
    std::cout << "layer number: " << layer_size << std::endl;
    layer = new Layer[layer_size + 1];
    for (int i = 0; i < layer_size; i++)
    {
        layer[i] = Layer(layer_node[i], layer_node[i + 1]);
        if (layer_mode[i] == MLP)
            layer[i].initWeight();
        getTime();
        std::cout << "layer " << i << " initial done\tlayer mode: " << layer_mode[i] << "\tlayer node: " << layer_node[i] << std::endl;
    }
    // The last layer of the network is defined as softmax
    layer[layer_size] = Layer(layer_node[layer_size], layer_node[layer_size]);
}

void Net::forward()
{
    for (int i = 0; i < layer_size; i++)
    {
        switch (layer_mode[i])
        {
        case MLP:
            layer[i].MAC();
            break;
        case RELU:
            layer[i].reLU();
            break;
        case SIGMOID:
            layer[i].sigmoid();
            break;
        default:
            break;
        }

        // put the output data of the current layer
        // to the next layer's input
        for (int j = 0; j < layer[i].output_node; j++)
        {
            layer[i + 1].data_in.data[0][j] = layer[i].data_out.data[0][j];
        }
    }
    // the last layer is softmax
    layer[layer_size].softmax();
}

void Net::lossFunction(std::vector<int> label)
{
    int index = 0;
    for (int i = 0; i < label.size(); i++)
    {
        if (label[i] == 1)
        {
            index = i;
            break;
        }
    }
    // cross entropy
    loss = -log(layer[layer_size].data_out.data[0][index]);
}

// calculate the loss of each layer
void Net::getLoss(std::vector<int> label)
{
    // loss of the last layer(softmax)
    for (int i = 0; i < layer[layer_size].output_node; i++)
    {
        layer[layer_size - 1].loss.data[0][i] = layer[layer_size].data_out.data[0][i] - label[i];
    }
    for (int i = layer_size - 1; i > 0; i--)
    {
        switch (layer_mode[i])
        {
        case MLP:
            // backward the loss
            for (int j = 0; j < layer[i - 1].output_node; j++)
            {
                layer[i - 1].loss.data[0][j] = 0;
                for (int k = 0; k < layer[i].output_node; k++)
                {
                    layer[i - 1].loss.data[0][j] += layer[i].loss.data[0][k] * layer[i].weight.data[j][k];
                }
            }

            break;
        case RELU:
            for (int j = 0; j < layer[i - 1].output_node; j++)
            {
                // when x is 0, the gradient is 1
                // otherwise , the classification will be wrong
                if (layer[i].loss.data[0][j] = 0)
                    layer[i - 1].loss.data[0][j] = 0;
                else
                    layer[i - 1].loss.data[0][j] = layer[i].loss.data[0][j];
            }
            break;
        case SIGMOID:
            for (int j = 0; j < layer[i - 1].output_node; j++)
            {
                layer[i - 1].loss.data[0][j] = layer[i].loss.data[0][j] * dsigmoid(layer[i].data_out.data[0][j]);
            }
            break;
        default:
            break;
        }
    }
}

// calculate the diff of each layer
void Net::backward(std::vector<int> label)
{
    getLoss(label);
    for (int i = layer_size - 1; i >= 0; i--)
    {
        switch (layer_mode[i])
        {
        case MLP:
            for (int j = 0; j < layer[i].output_node; j++)
            {
                for (int k = 0; k < layer[i].input_node; k++)
                {
                    layer[i].weight_diff.data[k][j] += -learning_rate * layer[i].loss.data[0][j] * layer[i].data_in.data[0][k];
                }
                layer[i].bias_diff.data[0][j] += -learning_rate * layer[i].loss.data[0][j];
            }
            break;

        default:
            break;
        }
    }
}

// update the weight of each layer
void Net::update(int batch_size)
{
    for (int i = layer_size - 1; i >= 0; i--)
    {
        switch (layer_mode[i])
        {
        case MLP:
            for (int j = 0; j < layer[i].output_node; j++)
            {
                for (int k = 0; k < layer[i].input_node; k++)
                {
                    layer[i].weight.data[k][j] += layer[i].weight_diff.data[k][j] / batch_size;
                    layer[i].weight_diff.data[k][j] = 0;
                }
                layer[i].bias.data[0][j] += layer[i].bias_diff.data[0][j] / batch_size;
                layer[i].bias_diff.data[0][j] = 0;
            }
            break;
        case RELU:
            // std::cout << "relu layer updating" << std::endl;
            break;

        default:
            break;
        }
    }
}

float Net::dsigmoid(float data)
{
    return data * (1 - data);
}

// void Net::trainBatch(std::vector<std::vector<int>> label, int batch)
// {
//     for (int iter = 0; iter < batch; iter++)
//     {
//         backward(label[iter]);
//     }
//     // if reach the point of a batch size,
//     // updata the weight and clean the diff
//     for (int i = layer_size - 1; i >= 0; i--)
//     {
//         for (int j = 0; j < layer[i].output_node; j++)
//         {
//             for (int k = 0; k < layer[i].input_node; k++)
//             {
//                 layer[i].weight.data[k][j] += (layer[i].weight_diff.data[k][j] / batch);
//                 layer[i].weight_diff.data[k][j] = 0;
//             }
//             layer[i].bias.data[0][j] += (layer[i].bias_diff.data[0][j] / batch);
//             layer[i].bias_diff.data[0][j] = 0;
//         }
//     }
// }