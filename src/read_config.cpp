

#include "./../include/read_config.h"



ReadConfig::ReadConfig()
{
    ;
}

ReadConfig::~ReadConfig()
{
    ;
}

std::vector<std::string> ReadConfig::split(const std::string &str, const char charac)
{
    std::vector<std::string> vec;
    std::string tmpStr;
    for (int i=0;i<str.size();i++)
    {
        char c=str[i];
        if (c == charac)
        {
            if (!tmpStr.empty())
            {
                vec.push_back(tmpStr);
                tmpStr.clear();
            }
        }
        else
        {
            tmpStr += c;
        }
    }
    if (!tmpStr.empty())
    {
        vec.push_back(tmpStr);
    }
    return vec;
}

// read the network parameters
bool ReadConfig::readParameter(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str());
    if (!file.is_open())
    {
        getTime();
        std::cout << "Cannot open the file! Please check the path!" << std::endl;
        return false;
    }
    else
    {
        getTime();
        std::cout << "Loading the network parameters ..." << std::endl;
        std::vector<std::string> cut;
        while (!file.eof())
        {
            std::string buffer;
            getline(file, buffer);
            cut = split(buffer, ' ');
            int num;
            std::istringstream(cut[1]) >> num;
            if (cut[0].find("learning_rate") != -1)
                learning_rate = num;
            else if (cut[0].find("batch_size") != -1)
                batch_size = num;
            else if (cut[0].find("interval") != -1)
                interval = num;
            else if (cut[0].find("epoch") != -1)
                epoch = num;
            else
                ;
        }
        getTime();
        std::cout << "Network parameters loading finished" << std::endl;
        return true;
    }
}

// read the network structure
bool ReadConfig::readFile(std::string filename)
{
    std::fstream file;

    file.open(filename.c_str());
    if (!file.is_open())
    {
        getTime();
        std::cout << "Cannot open the file! Please check the path!" << std::endl;
        return false;
    }
    else
    {
        getTime();
        std::cout << "Loading the network structure ..." << std::endl;
        std::vector<std::string> cut;
        while (!file.eof())
        {
            std::string buffer;
            getline(file, buffer);

            cut = split(buffer, ' ');
            // std::cout << cut[0] << std::endl;
            set_mode(cut[0]);
            set_node(cut[1]);
        }
        int num;
        std::istringstream(cut[2]) >> num;
        layer_node.push_back(num);
        file.close();
        getTime();
        std::cout << "Network structure loading finished" << std::endl;
        return true;
    }
}

void ReadConfig::set_mode(std::string mode)
{
    if (mode.find("MLP") != -1)
        layer_mode.push_back(MLP);
    else if (mode.find("SIGMOID") != -1)
        layer_mode.push_back(SIGMOID);
    else if (mode.find("RELU") != -1)
        layer_mode.push_back(RELU);
    else
        ;
}

void ReadConfig::set_node(std::string node)
{
    int num;
    std::istringstream(node) >> num;
    layer_node.push_back(num);
}
