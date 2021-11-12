CXX=g++
CXXFLAGS =-Wall -Wextra -Wno-unused-parameter -Wno-format-truncation -std=c++11
CXXFLAGS += -I. -I./common -I./lsh_folder -I./hypercube_folder -I./cluster_folder
OBJS_FOLDER = ./objects 
OBJ_COMMON =  ./common/object.o ./common/assist_functions.o ./common/h_hash.o ./common/dataset.o ./common/input_check.o
OBJ_LSH = ./lsh_folder/g_hash.o ./lsh_folder/hash.o ./lsh_folder/lsh_struct.o
OBJ_HYPERCUBE = ./hypercube_folder/f_hash.o ./hypercube_folder/hypercube_class.o
OBJ_CLUSTER = ./cluster_folder/cluster_info.o 
PROGRAMS = lsh cube cluster

all: $(PROGRAMS) mv_objs

target1: lsh mv_objs

target2: cube mv_objs

target3: cluster mv_objs

mv_objs:
	mkdir -p $(OBJS_FOLDER)
	mv -f $(OBJ_CLUSTER) $(OBJS_FOLDER) 2>/dev/null; true
	mv -f $(OBJ_HYPERCUBE) $(OBJS_FOLDER) 2>/dev/null; true
	mv -f $(OBJ_LSH) $(OBJS_FOLDER) 2>/dev/null; true
	mv -f $(OBJ_COMMON) $(OBJS_FOLDER) 2>/dev/null; true
	mv -f lsh.o $(OBJS_FOLDER) 2>/dev/null; true
	mv -f cube.o $(OBJS_FOLDER) 2>/dev/null; true
	mv -f cluster.o $(OBJS_FOLDER) 2>/dev/null; true


lsh:  $(OBJ_COMMON) $(OBJ_LSH) lsh.o
	$(CXX) $(CXXFLAGS) -o lsh lsh.o $(OBJ_COMMON) $(OBJ_LSH)

cube: $(OBJ_COMMON) $(OBJ_HYPERCUBE) cube.o
	$(CXX) $(CXXFLAGS) -o cube cube.o $(OBJ_COMMON) $(OBJ_HYPERCUBE)

cluster: $(OBJ_COMMON) $(OBJ_HYPERCUBE) $(OBJ_LSH) $(OBJ_CLUSTER) cluster.o 
	$(CXX) $(CXXFLAGS) -o cluster cluster.o $(OBJ_COMMON) $(OBJ_HYPERCUBE) $(OBJ_LSH) $(OBJ_CLUSTER)

.PHONY: clean

clean:
	rm -rf *.o lsh cube cluster output* $(OBJS_FOLDER)




cluster_s_c: target3
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m Classic

cluster_b_c: target3
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m Classic

cluster_s_lsh: target3
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m LSH

cluster_b_lsh: target3
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m LSH

cluster_s_cube: target3
	./cluster -i ./data/input_small_id -c ./data/cluster.config -o output_s_cl -complete -m Hypercube

cluster_b_cube: target3
	./cluster -i ./data/input_b_id -c ./data/cluster.config -o output_b_cl -complete -m Hypercube

lsh_s_s: target1
	./lsh -i ./data/input_small_id -q ./data/query_small_id -o output_s_cl  

lsh_s_b: target1
	./lsh -i ./data/input_small_id -q ./data/query_b_id -o output_s_cl   

lsh_b_s: target1
	./lsh -i ./data/input_b_id -q ./data/query_small_id -o output_s_cl  

lsh_b_b: target1
	./lsh -i ./data/input_b_id -q ./data/query_b_id -o output_s_cl 


cube_s_s: target2
	./cube -i ./data/input_small_id -q ./data/query_small_id o output_s_cl 

cube_s_b: target2
	./cube -i ./data/input_small_id -q ./data/query_b_id -o output_s_cl 

cube_b_s: target2
	./cube -i ./data/input_b_id -q ./data/query_small_id -o output_s_cl 

cube_b_b: target2
	./cube -i ./data/input_b_id -q ./data/query_b_id -o output_s_cl 