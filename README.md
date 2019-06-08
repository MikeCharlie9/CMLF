# CMLF
Compact Machine Learning Framework

### Introduction
This is a compact machine learning framework written in C++. The motivation of writing it is that I want to create a very simply ML framework which consists no complex models. The program can be run in any machine if you have installed gcc. No more packages, models, and other dependent files. Several weeks ago, I found it's very powerful to run a NN network on caffe. The data structure in it really inspired me. So, I decided to follow it to make my own ML framework. Luckily, I made it!

The current version is 1.0(2019.5.31)

The CMLF can be used in any MLP network. You can configure the network structure by yourself.

In the following version, CNN and other machine learning framework will be supported.

### Developer
Ma Chang from SJTU, e-mail: mcsjtu2018@163.com

Shang Caijie from WHU, e-mail: 326862368@qq.com

### Acknowledgement

Lei Yuting, from School of Physics and Technology, Wuhan University

Hunag Jiaming, from Department of Micro/Nano Electronics, Shanghai Jiao Tong University

### Copyright
The whole code is open source, please quote if you want to use it. (https://github.com/MikeCharlie9/CMLF)

---
### Detail information
The CMLF provides hierarchical structure to describe a network. "Net", "Layer", "Data" are basic calsses in CMLF. Data is used to describe the basic data structure, such as weight, bias, input & output data, diff and so on. Layer is used to describe each layer of the network. It contains some basic operation of each layer, such as foward, activation and so on. Net is used to describe the whole network. Basic parameter is the node number of each layer. The class Net instantiate the layer of the network according to the parameters obtained. Any bottom data can be obtained in a way of "net.layer.data".


### Example
Two examples provided in the src can be used to test the network.

- test_main.cpp The classification of XOR gate is done, which is thought to be the easiest non-linear problem.
- infra_main.cpp The classification of infrared images. The data in the folder "data" are mean and variance got from the images.

### Bugs
- You can not print extra "enter" in the config file. Otherwise, the program may stop working

### No time to write more detail information. Sorry~
contact me by e-mail : mcsjtu2018@163.com
