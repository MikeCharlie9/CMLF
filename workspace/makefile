
main.exe:*.o
	g++ $^ -o main.exe

*.o: ./../src/*.cpp ./../test/test_infra.cpp
	g++ -c $^
	
clean:
	del *.o
	del main.exe