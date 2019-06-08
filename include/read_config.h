#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "./../include/define.h"
#include "./../include/LocalTime.h"

class ReadConfig
{
public:
    ReadConfig();
    ~ReadConfig();
    std::vector<int> layer_node;
    std::vector<int> layer_mode;
    int batch_size;
    int interval;
    int epoch;
    float learning_rate;

    bool readFile(std::string filename);
    bool readParameter(std::string filename);

private:
    std::vector<std::string> split(const std::string &str, const char charac);
    void set_mode(std::string mode);
    void set_node(std::string node);
};

#endif