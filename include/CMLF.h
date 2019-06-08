#ifndef CMLF_H
#define CMLF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "./../include/LocalTime.h"
#include "./../include/net.h"
#include "./../include/read_config.h"

class CMLF
{
public:
    CMLF();
    ~CMLF();

    Net net;

    int batch_size;
    int interval;
    int epoch;
    float learning_rate;
    int iteration;

    int label_size;
    std::vector<std::vector<float> > trainset;
    std::vector<std::vector<float> > testset;
    std::vector<std::vector<int> > trainlabel;
    std::vector<std::vector<int> > testlabel;

    void init(std::string config_name, std::string param_name);

    void setLabelSize(int label_size);
    void setBatchSize(int batch_size);
    void setInterval(int interval);
    void setEpoch(int epoch);
    void setLearningRate(float learning_rate);
    void setTrainSet(std::vector<std::vector<float> > trainset);
    void setTestSet(std::vector<std::vector<float> > testset);
    void setTrainLabel(std::vector<int> trainlabel);
    void setTestLabel(std::vector<int> testlabel);

    void printConfig();
    void train();
    float str2float(std::string data);
    int str2int(std::string data);
    int findMax(float *data, int size);
};

#endif