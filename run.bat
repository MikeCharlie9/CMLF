cd workspace
g++ -c ./../src/data.cpp
g++ -c ./../src/layer.cpp
g++ -c ./../src/net.cpp
g++ -c ./../src/LocalTime.cpp
g++ -c ./../src/read_config.cpp
g++ -c ./../src/CMLF.cpp

g++ -c ./../test/test_infra.cpp
g++ data.o layer.o net.o LocalTime.o read_config.o test_infra.o CMLF.o -o test_infra.exe
test_infra.exe
cd ..