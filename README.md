# CMLF
Compact Machine Learning Framework

### Introduction
This is a compact machine learning framework written in C++. The motivation of writing it is that I want to create a very simply ML framework which consists no complex models. The program can be run in any machine if you have installed gcc. No more packages, models, and other dependent files. Several weeks ago, I found it's very powerful to run a NN network on caffe. The data structure in it really inspired me. So, I decided to follow it to make my own ML framework. Luckily, I made it!

The current version is 1.2 (2019.7.14)

The CMLF can be used in any MLP network. You can configure the network structure by yourself.

In the following version, CNN and other machine learning framework will be supported.

### Developer
Ma Chang from SJTU, e-mail: mcsjtu2018@163.com

Shang Caijie from WHU, e-mail: 326862368@qq.com

### Acknowledgement

Lei Yuting, from School of Physics and Technology, Wuhan University

Hunag Jiaming, from Department of Micro/Nano Electronics, Shanghai Jiao Tong University

Yang Weidong, from Department of Micro/Nano Electronics, Shanghai Jiao Tong University

### Copyright
The whole code is open source, please quote if you want to use it. (https://github.com/MikeCharlie9/CMLF)

### Version information
- version 1.2 (2019.7.14)

  Support OpenMP. Add an example than can classify MNIST with CMLF. Add bat file for MNIST. Modify the src.

- version 1.1 (2019.6.8)
  Resort files with standards. Add a top class "Class CMLF" for easy use. Add makefile and bat file for linux and windows users.

- version 1.0 (2019.5.31)
  Support MLP

---
### Detail information
The CMLF provides hierarchical structure to describe a network. "Net", "Layer", "Data" are basic clssses in CMLF. Data is used to describe the basic data structure, such as weight, bias, input & output data, diff and so on. Layer is used to describe each layer of the network. It contains some basic operation of each layer, such as foward, activation and so on. Net is used to describe the whole network. Basic parameter are node number and layer type of each layer. The class Net instantiate the layer of the network according to the parameters obtained. The class CMLF encapsulates some common methods. You can use `cmlf.train()` to train the network. Network structures and super parameters are loaded from config files.

### File list
```
./src               //contains cpp files
./include           //contains header files
./config            //you can write config file in this folder
./data              //dataset and label for example
./test              //several examples for test
./workspace         //running workspace, contains makefile
```

### Data structure
```
-main.cpp
  |-class CMLF
      |-class Net
          |-class Layer
              |-class Data
```
Access for any variables is allowed in the format `cmlf.net.layer[0].data`

### Example
Examples provided in the test can be used to test the network.

`./workspace/makefile` is provided for linux or windows users(if you have installed the mingw32-make). For windows users, you can also use bat to run the example.

### Bugs
- You cannot print extra "enter" in the config file. Otherwise, the program may stop working

### Any questions?
contact me by e-mail : mcsjtu2018@163.com
