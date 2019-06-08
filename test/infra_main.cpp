#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./../include/net.h"
#include "./../include/read_config.h"

float str2float(std::string data)
{
    float num;
    std::istringstream(data) >> num;
    return num;
}

int str2int(std::string data)
{
    int num;
    std::istringstream(data) >> num;
    return num;
}

int finMax(float *data, int size)
{
    float max = 0;
    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (data[i] >= max)
        {
            max = data[i];
            index = i;
        }
    }
    return index;
}

int main()
{
    // read config
    std::vector<int> layer_node, layer_mode;
    ReadConfig rc = ReadConfig();
    std::string filename = "./../config/infra_config.txt";
    bool status = rc.readFile(filename);
    layer_mode = rc.layer_mode;
    layer_node = rc.layer_node;

    std::fstream file_data;
    std::fstream file_label;
    file_data.open("./../data/dataset.txt");
    file_label.open("./../data/label.txt");
    std::vector<std::vector<float> > dataset;
    std::vector<std::vector<int> > label;
    getTime();
    std::cout << "Initial the dataset and label, loading ..." << std::endl;
    while (!file_data.eof())
    {
        std::string temp_data;
        std::vector<float> eachdata;
        std::vector<int> eachlabel;
        getline(file_data, temp_data);
        eachdata.push_back(str2float(temp_data));
        getline(file_data, temp_data);
        eachdata.push_back(str2float(temp_data));
        dataset.push_back(eachdata);

        getline(file_label, temp_data);
        for (int i = 0; i < 4; i++)
        {
            if (i == str2int(temp_data))
                eachlabel.push_back(1);
            else
                eachlabel.push_back(0);
        }
        label.push_back(eachlabel);
    }
    file_data.close();
    file_label.close();
    getTime();
    std::cout << "Finishing initiaztion!" << std::endl;
    // std::cout << dataset.size() << std::endl;
    // std::cout << label.size() << std::endl;
    // for (int i : label[291])
    //     std::cout << i << std::endl;
    // std::cout << label[292] << std::endl;
    // std::cout << dataset[0][0] << "\t" << dataset[0][1];

    Net net = Net(layer_node, layer_mode, 1.0);
    net.init();
    for (int epoch = 0; epoch < 5000; epoch++)
    {
        // *********************************************************
        // test
        if (epoch % 100 == 0)
        {
            int count = 0;
            for (int i = 0; i < dataset.size(); i++)
            {
                net.layer[0].data_in.data[0][0] = dataset[i][0];
                net.layer[0].data_in.data[0][1] = dataset[i][1];
                net.forward();
                if (label[i][finMax(net.layer[net.layer_size].data_out.data[0], net.layer[net.layer_size].output_node)] == 1)
                    count++;
            }
            getTime();
            std::cout << "epoch: " << epoch << "\tcorrect: " << count << " / " << dataset.size() << std::endl;
            if (count == dataset.size())
            {
                getTime();
                std::cout << "convergence reached! \tepoch: " << epoch << std::endl;
                break;
            }
        }
        // *********************************************************
        // train
        for (int i = 0; i < dataset.size(); i++)
        {
            net.layer[0].data_in.data[0][0] = dataset[i][0];
            net.layer[0].data_in.data[0][1] = dataset[i][1];
            net.forward();
            net.backward(label[i]);
            if ((epoch * (dataset.size()) + i) % 16 == 0)
                net.update(16);
        }
    }

    return 0;
}