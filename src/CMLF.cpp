

#include "./../include/CMLF.h"



CMLF::CMLF()
{
    ;
}
CMLF::~CMLF()
{
    ;
}

void CMLF::init(std::string config_name, std::string param_name)
{
    // read config

    ReadConfig rc = ReadConfig();
    rc.readFile(config_name);
    rc.readParameter(param_name);
    this->epoch = rc.epoch;
    this->interval = rc.interval;
    this->batch_size = rc.batch_size;
    this->learning_rate = rc.learning_rate;

    net = Net(rc.layer_node, rc.layer_mode, learning_rate);
    net.init();
    printConfig();
}

void CMLF::setLabelSize(int label_size)
{
    this->label_size = label_size;
}
void CMLF::setBatchSize(int batch_size)
{
    this->batch_size = batch_size;
}
void CMLF::setInterval(int interval)
{
    this->interval = interval;
}
void CMLF::setEpoch(int epoch)
{
    this->epoch = epoch;
}
void CMLF::setLearningRate(float learning_rate)
{
    this->learning_rate = learning_rate;
}

void CMLF::setTrainSet(std::vector<std::vector<float> > trainset)
{
    this->trainset = trainset;
}
void CMLF::setTestSet(std::vector<std::vector<float> > testset)
{
    this->testset = testset;
}
void CMLF::setTrainLabel(std::vector<int> trainlabel)
{
    for (int i = 0; i < trainlabel.size(); i++)
    {
        std::vector<int> label;
        for (int j = 0; j < label_size; j++)
        {
            if (trainlabel[i] == j)
                label.push_back(1);
            else
                label.push_back(0);
        }
        this->trainlabel.push_back(label);
    }
}
void CMLF::setTestLabel(std::vector<int> testlabel)
{
    for (int i = 0; i < testlabel.size(); i++)
    {
        std::vector<int> label;
        for (int j = 0; j < label_size; j++)
        {
            if (testlabel[i] == j)
                label.push_back(1);
            else
                label.push_back(0);
        }
        this->testlabel.push_back(label);
    }
}

void CMLF::train()
{
    int start_time, end_time;
    start_time = clock();

    iteration = 0;
    for (int i = 0; i < epoch; i++)
    {
        if (i % interval == 0)
        {
            int correct = 0;
            for (int j = 0; j < testset.size(); j++)
            {
                // read the test dataset
                for (int k = 0; k < testset[j].size(); k++)
                {
                    net.layer[0].data_in.data[0][k] = testset[j][k];
                }
                net.forward();
                if (testlabel[j][findMax(net.layer[net.layer_size].data_out.data[0], net.layer[net.layer_size].output_node)] == 1)
                    correct++;
            }
            getTime();
            std::cout << "epoch: " << i << "\tcorrect: " << correct << " / " << testset.size() << std::endl;
        }
        for (int j = 0; j < trainset.size(); j++)
        {
            // read the test dataset
            for (int k = 0; k < testset[j].size(); k++)
            {
                net.layer[0].data_in.data[0][k] = testset[j][k];
            }
            net.forward();
            net.backward(trainlabel[j]);
            iteration++;
            if (iteration % batch_size == 0)
                net.update(batch_size);
        }
    }
    end_time = clock();
    getTime();
    std::cout << "Training run time: " << end_time - start_time << std::endl;
}

void CMLF::printConfig()
{
    getTime();
    std::cout << "batch size:\t\t" << batch_size << std::endl;
    getTime();
    std::cout << "test interval:\t\t" << interval << std::endl;
    getTime();
    std::cout << "total epoch:\t\t" << epoch << std::endl;
    getTime();
    std::cout << "learning rate:\t\t" << learning_rate << std::endl;
    getTime();
    std::cout << "classified number:\t" << label_size << std::endl;
}

float CMLF::str2float(std::string data)
{
    float num;
    std::istringstream(data) >> num;
    return num;
}

int CMLF::str2int(std::string data)
{
    int num;
    std::istringstream(data) >> num;
    return num;
}

int CMLF::findMax(float *data, int size)
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