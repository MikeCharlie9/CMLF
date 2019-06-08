#ifndef NET_H
#define NET_H

#include "./../include/define.h"
#include "./../include/layer.h"
#include "./../include/LocalTime.h"


class Net
{
public:
    Layer *layer;
    int layer_size;
    float loss;
    float learning_rate;
    std::vector<int> layer_node;
    std::vector<int> layer_mode;
    Net();
    Net(std::vector<int> layer_node, std::vector<int> layer_mode, float learning_rate);
    ~Net();

    void init();
    void forward();
    void getLoss(std::vector<int> label);
    void backward(std::vector<int> label);
    void update(int batch_size);
    float dsigmoid(float data);
    void lossFunction(std::vector<int> label);
    // void trainBatch(std::vector<std::vector<int>> label, int batch);
};

#endif