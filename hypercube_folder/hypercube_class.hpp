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
#include <set>

//An enum type used in the recursion part of the hypercube so that the appropriate action is taken
enum search_type {kNN, RANGE_SEARCH};

class hypercube{
private:
    std::list<const Object*>* cube_array; //every vertex of the hypercube will store Object pointers in a similar fashion to the lsh hashtables
                                    //The array will have size 2^d1 where d1 is the dimension of the cube
    f_hash* f_array;                //create d1 functions which assign integers randomly to {0,1} 
    h_hash* h_array;                //create d1 h_hash functions

    //Find the value (0 or 1) of the i-th coordinate of the vertex of the d1-hypercube for the given object
    uint8_t get_0_or_1(int i, const Object& object);
    

    //Functions used for the recursion in which the vertices are visited in increasing hamming distance
    // Also the remaining allowed number of vertices and points-Objects which can be visited are defined by probes_rem and M_rem
    //Since the reucrsion is used for both kNN and Range search, all necessary parameters needed for both are included
    // Finally, depending on whether search_type Type is kNN or Range_search, max_heap will actually be a max heap defined as a priority queue or it will be a set
    // thus we use void* so that the appropriate cast is used
    // (Initially a template was used for references to the priority queue or set instead of void* but there waw an error of unknown origin and the template was discarded)
    void vertex_visiting_first_stage(search_type Type, const int R, int curr_vertex, int ham_dist, int M_rem, int probes_rem, uint curr_bit, void* max_heap,
								const Object & query_object, double (*metric)(const Object &, const Object &), int N, const int R2 = 0);
    
    void vertex_visiting_second_stage(search_type Type, const int R, int curr_vertex, int& M_rem, int& probes_rem, uint curr_bit, int ham_rem, void* max_heap,
								const Object & query_object, double (*metric)(const Object &, const Object &), int& N, const int R2 = 0);
    
    void vertex_visiting_third_stage(search_type Type, const int R, int curr_vertex, int& M_rem, void* max_heap,
								const Object & query_object, double (*metric)(const Object &, const Object &), int& N, const int R2 = 0);

public:

    hypercube();

    //For each object, index is which vertex of the hypercube the object will be stored, encoded in the rightmost d1 digits
    // e.g if index = 0b00001011 and d1 = 5 that means the object will be inserted at the vertex (1,1,0,1,0) where 
    // the 5 rightmost bits where taken in reverse order
    void import_data(const Dataset& obj);

    // executes the approximate/exact/ranged nearest neighbors algorithms using given metric function (pointer to function)
	// and outputs results and execution times in output file
	bool execute(const Dataset & dataset, Dataset & query_dataset, const std::string & output_file, const int & N, const int & R, double (*metric)(const Object &, const Object &));
	// runs approximate and exact nearest neighbors using given metric function and write results into file
	std::vector <std::pair <double, const Object*> > appr_nearest_neighbors(const Dataset & dataset, const Object & query_object, const int & N, double (*metric)(const Object &, const Object &));
	// run approximate range search using given metric function and save results in a set (with their distances from the query object)
    // Ignore objects whose ids are in the visited set
    // By default, the visited set will be empty which means all the objects found will be returned
	std::set <std::pair <double, const Object*> > range_search(const Object & query_object, const int & R, double (*metric)(const Object &, const Object &), const int R2 = 0);

    std::vector <std::pair <double, const Object*> > exact_nearest_neighbors(const Dataset & dataset, const Object & query_object, const int & N, double (*metric)(const Object &, const Object &));

    //void print() const;
    ~hypercube();
};

//Make sure the priority queue only stores at most N from the currently found objects since more than N are not needed
void push_at_most_N(const Object* obj_p, int N, double dist, std::priority_queue <std::pair <double, const Object*> >* max_heap);

#endif