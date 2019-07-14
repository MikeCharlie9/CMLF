#include <iostream>
#include "./../include/CMLF.h"
#include "./../include/net.h"
#include "./../include/read_config.h"
#include "./../include/LocalTime.h"

typedef unsigned int uint;
typedef unsigned char uchar;

int find_max(float *data, int size)
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

int test(Net net)
{
    FILE *test_image=fopen("./../data/t10k-images.idx3-ubyte","rb");
    FILE *test_label=fopen("./../data/t10k-labels.idx1-ubyte","rb");

    uint image_header[4];
    uint label_header[2];    
    fread(&image_header[0],sizeof(uint),4,test_image);
    fread(&label_header[0],sizeof(uint),2,test_label);

    int L1=net.layer[0].input_node;

    uchar image_data[L1];
    uchar label_data;
    int COUNT=0;
    for(int var=0;var<10000;var++)
    {
        fread(&image_data[0],sizeof(uchar),L1,test_image);
        for(int i=0;i<L1;i++)
        {
            net.layer[0].data_in.data[0][i]=((float)image_data[i])/255.0;
        }
        net.forward();
        int location=find_max(net.layer[net.layer_size].data_out.data[0],net.layer[net.layer_size].output_node);
        fread(&label_data,sizeof(uchar),1,test_label);
        if(location==label_data)COUNT++;
    }

    fclose(test_image);
    fclose(test_label);

    return COUNT;
}

void train(Net net,int batch_size)
{
    FILE *train_image=fopen("./../data/train-images.idx3-ubyte","rb");
    FILE *train_label=fopen("./../data/train-labels.idx1-ubyte","rb");
    
    uint image_header[4];
    uint label_header[2];
    fread(&image_header[0],sizeof(uint),4,train_image);
    fread(&label_header[0],sizeof(uint),2,train_label);

    int L1=net.layer[0].input_node;
    int L2=net.layer[net.layer_size].output_node;

    uchar image_data[L1];
    uchar label_data;

    for(int var=0;var<60000;var++)
    {
        fread(&label_data,sizeof(uchar),1,train_label);
        int index=(int)label_data;
        std::vector<int> label;
        for(int i=0;i<L2;i++)
        {
            if(i == index)
                label.push_back(1);
            else 
                label.push_back(0);
        }
        fread(&image_data[0],sizeof(uchar),L1,train_image);
        for(int i=0;i<L1;i++)
        {
            net.layer[0].data_in.data[0][i]=((float)image_data[i])/255.0;           
        }
        net.forward();
        net.backward(label);
        net.lossFunction(label);
        if(var%batch_size==0)
            net.update(batch_size);
    }  
    fclose(train_image);
    fclose(train_label);

}

int main()
{
    std::vector<int> layer_node,layer_mode;
    ReadConfig rc=ReadConfig();
    std::string config_name="./../config/mnist_config.txt";
    rc.readFile(config_name);
    layer_mode=rc.layer_mode;
    layer_node=rc.layer_node;


    Net net=Net(layer_node,layer_mode,0.1);
    net.init();

    getTime();
    std::cout<<"initial\t acc : "<<test(net)<<std::endl;
    
    for (int epoch=0;epoch<20;epoch++)
    {
        train(net,16);
        // getTime();
        // std::cout<<"epoch : "<<epoch<<"\t loss : "<<net.loss<<std::endl;
        getTime();
        std::cout<<"epoch : "<<epoch<<"\tacc : "<<test(net)<<std::endl;
    }

    return 0;
}