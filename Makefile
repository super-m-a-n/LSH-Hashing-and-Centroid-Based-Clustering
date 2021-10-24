CXX=g++
CXXFLAGS=-Wall -std=c++11
target: lsh

lsh: lsh.o input_check.o dataset.o object.o h_hash.o g_hash.o hash.o lsh_struct.o
	$(CXX) $(CXXFLAGS) -o lsh lsh.o input_check.o dataset.o object.o h_hash.o g_hash.o hash.o lsh_struct.o

input_check.o: input_check.cpp
	$(CXX) $(CXXFLAGS) -c input_check.cpp

dataset.o: dataset.cpp
	$(CXX) $(CXXFLAGS) -c dataset.cpp

object.o: object.cpp
	$(CXX) $(CXXFLAGS) -c object.cpp

h_hash.o: h_hash.cpp
	$(CXX) $(CXXFLAGS) -c h_hash.cpp

g_hash.o: g_hash.cpp
	$(CXX) $(CXXFLAGS) -c g_hash.cpp

hash.o: hash.cpp
	$(CXX) $(CXXFLAGS) -c hash.cpp

lsh_struct.o: lsh_struct.cpp
	$(CXX) $(CXXFLAGS) -c lsh_struct.cpp

lsh.o: lsh.cpp
	$(CXX) $(CXXFLAGS) -c lsh.cpp

.PHONY: clean

clean:
	rm -f *.o lsh
