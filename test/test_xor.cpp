#include <iostream>
#include <vector>
#include "./../include/net.h"
#include "./../include/read_config.h"

int main()
{
    std::vector<int> layer_node, layer_mode;
    ReadConfig rc = ReadConfig();
    std::string filename = "./../config/xor_config.txt";
    bool status = rc.readFile(filename);
    layer_mode = rc.layer_mode;
    layer_node = rc.layer_node;

    std::vector<int> label1;
    std::vector<int> label2;

    label1.push_back(1);
    label1.push_back(0);
    label2.push_back(0);
    label2.push_back(1);

    Net net = Net(layer_node, layer_mode, 1.0);
    net.init();
    for (int iter = 0; iter < 10000; iter++)
    {
        net.layer[0].data_in.data[0][0] = 0;
        net.layer[0].data_in.data[0][1] = 1;
        net.forward();
        net.backward(label1);
        // net.update();

        net.layer[0].data_in.data[0][0] = 0;
        net.layer[0].data_in.data[0][1] = 0;
        net.forward();
        net.backward(label2);
        // net.update();

        net.layer[0].data_in.data[0][0] = 1;
        net.layer[0].data_in.data[0][1] = 1;
        net.forward();
        net.backward(label2);
        // net.update();

        net.layer[0].data_in.data[0][0] = 1;
        net.layer[0].data_in.data[0][1] = 0;
        net.forward();
        net.backward(label1);
        // train a batch(contains 16 sample)
        if (iter % 4 == 0)
            net.update(16);
    }

    std::cout << "test out" << std::endl;
    net.layer[0].data_in.data[0][0] = 0;
    net.layer[0].data_in.data[0][1] = 1;
    net.forward();
    std::cout << net.layer[net.layer_size].data_out.data[0][0] << "\t";
    std::cout << net.layer[net.layer_size].data_out.data[0][1] << std::endl;

    net.layer[0].data_in.data[0][0] = 1;
    net.layer[0].data_in.data[0][1] = 1;
    net.forward();
    std::cout << net.layer[net.layer_size].data_out.data[0][0] << "\t";
    std::cout << net.layer[net.layer_size].data_out.data[0][1] << std::endl;

    net.layer[0].data_in.data[0][0] = 1;
    net.layer[0].data_in.data[0][1] = 0;
    net.forward();
    std::cout << net.layer[net.layer_size].data_out.data[0][0] << "\t";
    std::cout << net.layer[net.layer_size].data_out.data[0][1] << std::endl;

    net.layer[0].data_in.data[0][0] = 0;
    net.layer[0].data_in.data[0][1] = 0;
    net.forward();
    std::cout << net.layer[net.layer_size].data_out.data[0][0] << "\t";
    std::cout << net.layer[net.layer_size].data_out.data[0][1] << std::endl;

    // ********************************************************************************
    // the codes below is used to print the weight and loss of each layer
    // it is used to test whether the network functions well

    // std::cout << "output of each layer:" << std::endl;
    // for (int i = 0; i < net.layer_size + 1; i++)
    // {
    //     std::cout << "layer: " << i << "\t";
    //     for (int j = 0; j < net.layer[i].output_node; j++)
    //     {
    //         std::cout << net.layer[i].data_out.data[0][j] << "\t";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "loss of each layer:" << std::endl;

    // for (int i = 0; i < net.layer_size; i++)
    // {
    //     for (int j = 0; j < net.layer[i].output_node; j++)
    //     {
    //         std::cout << net.layer[i].loss.data[0][j] << "\t";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "weight:" << std::endl;
    // for (int i = 0; i < net.layer_size; i++)
    // {
    //     if (layer_mode[i] == MLP)
    //     {
    //         net.layer[i].weight.print();
    //         net.layer[i].bias.print();
    //     }
    // }
    // ********************************************************************************

    system("pause");
    return 1;
}