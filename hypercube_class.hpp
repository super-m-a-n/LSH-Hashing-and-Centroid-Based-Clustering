#ifndef HYPERCUBE_CLASS_HPP
#define HYPERCUBE_CLASS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "params.hpp"
#include "f_hash.hpp"
#include "h_hash.hpp" 
#include "object.hpp"
#include "dataset.hpp"
#include <queue>
#include <list>

enum search_type {kNN, RANGE_SEARCH};

class hypercube{
private:
    std::list<Object*>* cube_array; //every vertex of the hypercube will store Object pointers in a similar fashion to the lsh hashtables
                                    //The array will have size 2^d1 where d1 is the dimension of the cube
    f_hash* f_array;                //create d1 functions which assign integers randomly to {0,1} 
    h_hash* h_array;                //create d1 h_hash functions

    //Find the value (0 or 1) of the i-th coordinate of the vertex of the d1-hypercube for the given object
    uint8_t get_0_or_1(int i, Object& object);

    void vertex_visiting_first_stage(search_type Type, const int R, int curr_vertex, int ham_dist, int M_rem, int probes_rem, uint curr_bit,
	std::priority_queue <std::pair <double, const Object*> >& max_heap,
								Object & query_object, std::ofstream & file,double (*metric)(const Object &, const Object &), int N);

    void vertex_visiting_second_stage(search_type Type, const int R, int curr_vertex, int& M_rem, int& probes_rem, uint curr_bit, int ham_rem,
	std::priority_queue <std::pair <double, const Object*> >& max_heap,
								Object & query_object, std::ofstream & file, double (*metric)(const Object &, const Object &), int& N);

    void vertex_visiting_third_stage(search_type Type, const int R, int curr_vertex, int& M_rem,
	std::priority_queue <std::pair <double, const Object*> >& max_heap,
								Object & query_object, std::ofstream & file, double (*metric)(const Object &, const Object &), int& N);

public:

    hypercube();

    //For each object, index is which vertex of the hypercube the object will be stored, encoded in the rightmost d1 digits
    // e.g if index = 0b00001011 and d1 = 5 that means the object will be inserted at the vertex (1,1,0,1,0) where 
    // the 5 rightmost bits where taken in reverse order
    void import_data(Dataset& obj);

    // executes the approximate/exact/ranged nearest neighbors algorithms using given metric function (pointer to function)
	// and outputs results and execution times in output file
	bool execute(const Dataset & dataset, Dataset & query_dataset, const std::string & output_file, const int & N, const int & R, double (*metric)(const Object &, const Object &));
	// runs approximate and exact nearest neighbors using given metric function and write results into file
	std::vector <std::pair <double, const Object*> > appr_nearest_neighbors(const Dataset & dataset, Object & query_object, std::ofstream & file, const int & N, double (*metric)(const Object &, const Object &));
	// run approximate range search using given metric function and write results into file
	void range_search(Object & query_object, std::ofstream & file, const int & R, double (*metric)(const Object &, const Object &));

    std::vector <std::pair <double, const Object*> > exact_nearest_neighbors(const Dataset & dataset, const Object & query_object, const int & N, double (*metric)(const Object &, const Object &));

    //void print() const;
    ~hypercube();
};

//Make sure the priority queue only stores at most N from the currently found objects since more than N are not needed
void push_at_most_N(Object* obj_p, int N, double dist, std::priority_queue <std::pair <double, const Object*> >& max_heap);

double euclidean(const Object & p, const Object & q);
// can easily expand to other metric function here
// and pass the name of the function as a function pointer to the execute function

#endif