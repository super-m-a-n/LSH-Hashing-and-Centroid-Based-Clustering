CXX=g++
CXXFLAGS=-Wall -std=c++11

all: lsh cube cluster

target1: lsh

target2: cube

target3: cluster


lsh: lsh.o input_check.o dataset.o object.o h_hash.o g_hash.o hash.o lsh_struct.o
	$(CXX) $(CXXFLAGS) -o lsh lsh.o input_check.o dataset.o object.o h_hash.o g_hash.o hash.o lsh_struct.o

cube: cube.o input_check2.o dataset.o object.o h_hash.o f_hash.o hypercube_class.o assist_functions.o
	$(CXX) $(CXXFLAGS) -o cube cube.o input_check2.o dataset.o object.o h_hash.o f_hash.o hypercube_class.o assist_functions.o

cluster: cluster.o input_check.o dataset.o object.o cluster_info.o
	$(CXX) $(CXXFLAGS) -o cluster cluster.o input_check.o dataset.o object.o cluster_info.o

assist_functions.o: assist_functions.cpp
	$(CXX) $(CXXFLAGS) -c assist_functions.cpp

input_check.o: input_check.cpp
	$(CXX) $(CXXFLAGS) -c input_check.cpp

input_check2.o: input_check2.cpp
	$(CXX) $(CXXFLAGS) -c input_check2.cpp

dataset.o: dataset.cpp
	$(CXX) $(CXXFLAGS) -c dataset.cpp

object.o: object.cpp
	$(CXX) $(CXXFLAGS) -c object.cpp

h_hash.o: h_hash.cpp
	$(CXX) $(CXXFLAGS) -c h_hash.cpp

g_hash.o: g_hash.cpp
	$(CXX) $(CXXFLAGS) -c g_hash.cpp

f_hash.o: f_hash.cpp
	$(CXX) $(CXXFLAGS) -c f_hash.cpp

hash.o: hash.cpp
	$(CXX) $(CXXFLAGS) -c hash.cpp

lsh_struct.o: lsh_struct.cpp
	$(CXX) $(CXXFLAGS) -c lsh_struct.cpp

lsh.o: lsh.cpp
	$(CXX) $(CXXFLAGS) -c lsh.cpp

hypercube_class.o: hypercube_class.cpp
	$(CXX) $(CXXFLAGS) -c hypercube_class.cpp

cube.o: cube.cpp
	$(CXX) $(CXXFLAGS) -c cube.cpp

cluster_info.o: cluster_info.cpp
	$(CXX) $(CXXFLAGS) -c cluster_info.cpp

cluster.o: cluster.cpp
	$(CXX) $(CXXFLAGS) -c cluster.cpp

.PHONY: clean

clean:
	rm -f *.o lsh cube cluster output_id
