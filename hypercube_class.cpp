#include "hypercube_class.hpp"
#include <string>
#include <chrono>
#include <queue>
#include <utility>
#include <vector>
#include <fstream>

hypercube::hypercube(){
    this->cube_array = new std::list<Object*>[1 << d1]; //size 2^d1 (di is the global variable which stores the dimension of the hypercube)
    this->f_array = new f_hash[d1];
    this->h_array = new h_hash[d1];
}

uint8_t hypercube::get_0_or_1(int index, Object& object){
    return (this->f_array[index])(this->h_array[index](object));
}

//For each object, index is which vertex of the hypercube the object will be stored, encoded in the rightmost d1 digits
// e.g if index = 0b001011 and d1 = 5 that means the object will be inserted at the vertex (0,1,0,1,1) where 
// the 5 rightmost bits are read from left to right
void hypercube::import_data(Dataset& dataset){
    int num_of_objects = dataset.get_num_of_Objects();
    for (int i = 0 ; i < num_of_objects ; i++ ){
        int index = 0; //the index holds the encoding of the coordinates of the vertex 
        Object& obj = dataset.get_ith_object(i); //Get the i-th object of the dataset
        for (int j = 0 ; j < d1 ; j++){
            index = (index << 1) + this->get_0_or_1(j, obj);
        }
        this->cube_array[index].push_back(&obj);  //Add the object to the vertex (given by the index) 
    }
}
//void print() const;

bool hypercube::execute(const Dataset & dataset, Dataset & query_dataset, const std::string & output_file, const int & N, const int & R, double (*metric)(const Object &, const Object &))
{

	std::ofstream file (output_file, std::ios::out);		// open output file for output operations
	
	if (!file.is_open())			// check if file was opened properly
	    return false;				// error occured

	int num_of_objects = query_dataset.get_num_of_Objects();

	for (int i = 0; i < num_of_objects; i++)		// run for each of the query Objects
	{
        Object& obj = query_dataset.get_ith_object(i);
		file << "Query: query Object " << obj.get_name() << "\n\n";
		// run approximate and exact nearest neighbors and write results into file
		this->nearest_neighbors(dataset, obj, file, N, metric);
		// run approximate range search and write results into file
		this->range_search(obj, file, R, metric);
	}

	return true;
}

//Iterate through all verteces with hamming distance ham_dist from init_vertex and visit the objects in the nodes
//init_vertex: The vertex of the query object
//ham_dist: the hamming distance from the int_vertex
//M_rem: how many objects remaining are allowed to be checked
//probes_rem: How many vertices remaining are allowed to be checked
//curr_bit: The current bit of the curr_vertex which is to be decided whether it will be change (thus increasing the hamming distance by 1)
//ham_rem: how many bits still have to be changed

//The function recursively iterates through all vertices with increasing hamming distance until all are checked or M_rem or probes_rem becomes 0 
void hypercube::vertex_visiting_first_stage(search_type Type, const int R, int curr_vertex, int ham_dist, int M_rem, int probes_rem, uint curr_bit,
	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > & min_heap,
								Object & query_object, std::ofstream & file, double (*metric)(const Object &, const Object &)){

	this->vertex_visiting_second_stage(Type, R, curr_vertex, M_rem, probes_rem, curr_bit, ham_dist, min_heap, query_object, file, metric);

	//If all the allowed nodes or verices have been checked or
	//if we checked the vertex with all the bits having changed, which implies all the vertices have been visited, then end the recursion
	if (M_rem == 0 || probes_rem == 0 || ham_dist == d1) return;

	this->vertex_visiting_first_stage(Type, R, curr_vertex, ham_dist +1, M_rem, probes_rem, curr_bit, min_heap, query_object, file, metric);


}

void hypercube::vertex_visiting_second_stage(search_type Type, const int R, int curr_vertex, int& M_rem, int& probes_rem, uint curr_bit, int ham_rem,
	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > & min_heap,
								Object & query_object, std::ofstream & file, double (*metric)(const Object &, const Object &)){


	if (ham_rem == 0){
		this->vertex_visiting_third_stage(Type, R, curr_vertex, M_rem, min_heap, query_object, file, metric);
		probes_rem -= 1;
		return;
	}

	//If there at at least ham_rem  bits left besides the curr_bit, it is possible to not change the curr_bit of the curr_vertex and change others
	if ((curr_bit >> ham_rem) != 0){
		this->vertex_visiting_second_stage(Type, R, curr_vertex, M_rem, probes_rem, curr_bit >> 1, ham_rem, min_heap, query_object, file, metric);
		if (M_rem == 0 || probes_rem == 0) return;
	}

	this->vertex_visiting_second_stage(Type, R, curr_vertex xor curr_bit, M_rem, probes_rem, curr_bit >> 1, ham_rem -1, min_heap, query_object, file, metric);
}

void hypercube::vertex_visiting_third_stage(search_type Type, const int R, int curr_vertex, int& M_rem,
	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > & min_heap,
								Object & query_object, std::ofstream & file, double (*metric)(const Object &, const Object &)){

	std::list<Object*>& vertex_list = this->cube_array[curr_vertex];
	for(auto const& obj_p : vertex_list){
		double dist = (*metric)(query_object, *obj_p);

		// If the search type is kNN we don't care about the distance, just put it in the heap.
		// Otherwise, the search type is range search thus we want the distance to be smaller than R
		if (Type == kNN){
			min_heap.push(std::make_pair(dist, obj_p->get_name()));
		}
		else if (dist < R){
			file << "Point-Object " << obj_p->get_name() << '\n';
		}
		M_rem -= 1;
		if (M_rem == 0) return;
	}
}


void hypercube::nearest_neighbors(const Dataset & dataset, Object & query_object, std::ofstream & file, const int & N, double (*metric)(const Object &, const Object &))
{

	// run approximate kNN

	// initialize a min heap priority queue, that will store the Object identifier string name and the distance of Object from query object
	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > min_heap;

	//start timer
	auto t_cube_start = std::chrono::high_resolution_clock::now();


	int query_vertex = 0;

	for (int j = 0 ; j < d1 ; j++){
            query_vertex = (query_vertex << 1) + this->get_0_or_1(j, query_object);
    }

	this->vertex_visiting_first_stage(kNN, 0, query_vertex, 0, M, probes, 1 << (d1-1), min_heap, query_object, file, metric);


	// if Objects with same locality ID, are fewer than N
	//if (min_heap.size() < N)
	//{
		// TODO : run again perhaps
	//}

	// end timer
	auto t_cube_end = std::chrono::high_resolution_clock::now();

	// run brute force exact kNN
	int num_of_Objects = dataset.get_num_of_Objects();

	// initialize a min heap priority queue, that will store the distances of Objects from query object
	std::priority_queue <double, std::vector<double>, std::greater<double> > brute_force_min_heap;

	// start timer
	auto t_true_start = std::chrono::high_resolution_clock::now();

	// check each of the dataset objects by brute force
	for (int i = 0; i < num_of_Objects; ++i)
	{
		// find its distance from query object
		double dist = (*metric)(query_object, dataset.get_ith_object(i));
		// and insert it into min heap (memory inefficient but faster than keeping an array sorted through iterations, further testing required)
		brute_force_min_heap.push(dist);
	}

	// end timer
	auto t_true_end = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; ++i)
	{
		if (!min_heap.empty())		// neighbors found maybe less than N
		{
			std::string object_name = std::get<1>(min_heap.top());
			double dist = std::get<0>(min_heap.top());
			min_heap.pop();

			file << "Nearest neighbor-" << i+1 << " : Point-Object " << object_name << '\n';
			file << "distanceLSH : " << dist << '\n';
		}

		if (!brute_force_min_heap.empty())
		{
			double dist = brute_force_min_heap.top();
			brute_force_min_heap.pop();
			file << "distanceTrue : " << dist << "\n\n";
		}
	}

	// get execution for LSH in milliseconds 
    std::chrono::duration <double, std::milli> tLSH = t_cube_end - t_cube_start;
    // get execution for brute force in milliseconds
    std::chrono::duration <double, std::milli> tTrue = t_true_end - t_true_start;
    // write times of execution in file
    file << "tLSH : " << tLSH.count() << "ms\n";
    file << "tTrue : " << tTrue.count() << "ms\n\n";
}


void hypercube::range_search(Object & query_object, std::ofstream & file, const int & R, double (*metric)(const Object &, const Object &))
{
	file << "R-near neighbors: (R = " << R << ")" << '\n';

	int query_index = 0;

	for (int j = 0 ; j < d1 ; j++){
            query_index = (query_index << 1) + this->get_0_or_1(j, query_object);
    }

	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > min_heap;

	this->vertex_visiting_first_stage(kNN, R, query_index, 0, M, probes, 1 << (d1-1), min_heap, query_object, file, metric);

	file << "\n\n";
}


hypercube::~hypercube(){
    delete this->cube_array;
    delete this->f_array;
    delete this->h_array;

}

double euclidean(const Object & p, const Object & q){
	return p.euclidean_distance(q);
}