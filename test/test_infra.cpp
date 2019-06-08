#include <iostream>
#include "./../include/CMLF.h"
#include "./../include/LocalTime.h"

int main()
{
    CMLF cmlf = CMLF();
    cmlf.setLabelSize(4);

    // initial the dataset and label
    // in the form of vector
    std::fstream file_data;
    std::fstream file_label;
    file_data.open("./../data/dataset.txt");
    file_label.open("./../data/label.txt");
    std::vector<std::vector<float> > dataset;
    std::vector<int> label;
    getTime();
    std::cout << "Initial the dataset and label, loading ..." << std::endl;
    while (!file_data.eof())
    {
        std::string temp_data;
        std::vector<float> eachdata;
        std::vector<int> eachlabel;
        getline(file_data, temp_data);
        eachdata.push_back(cmlf.str2float(temp_data));
        getline(file_data, temp_data);
        eachdata.push_back(cmlf.str2float(temp_data));
        dataset.push_back(eachdata);

        getline(file_label, temp_data);
        label.push_back(cmlf.str2int(temp_data));
    }
    file_data.close();
    file_label.close();
    getTime();
    std::cout << "Finishing initiaztion!" << std::endl;

    // feed the network dataset and label
    cmlf.setTrainSet(dataset);
    cmlf.setTestSet(dataset);
    cmlf.setTrainLabel(label);
    cmlf.setTestLabel(label);

    // read the network structure and parameters
    cmlf.init("./../config/infra_config.txt", "./../config/infra_param.txt");
    cmlf.train();

    system("pause");
    return 0;
}
