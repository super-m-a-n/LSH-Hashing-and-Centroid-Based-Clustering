//file:lsh_struct.hpp//
#ifndef _LSH_STRUCT_HPP_
#define _LSH_STRUCT_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "params.hpp"
#include "hash.hpp"
#include "dataset.hpp"
#include "object.hpp"
#include <set>

// class lsh_struct contains all the data structures used by lsh
// namely L hash-tables
class lsh_struct
{
private:
	hash_table ** lsh_hash_struct;	// an array of pointers to L hashtables

public:
	// constructor, creates the L hashtables, each with number of buckets = hash_table_size
	lsh_struct(int hash_table_size);
	~lsh_struct();
	// imports dataset objects into lsh struct (into the L hash tables)
	void import_data(const Dataset & dataset);

	// executes the approximate/exact/ranged nearest neighbors algorithms using given metric function (pointer to function)
	// and outputs results and execution times in output file
	bool execute(const Dataset & dataset, const Dataset & query_dataset, const std::string & output_file, const int & N, const int & R, double (*metric)(const Object &, const Object &));

	// runs approximate nearest neighbors using given metric function and returns an array of nearest neighbors and distances found
	std::vector <std::pair <double, const Object*> > appr_nearest_neighbors(const Dataset & dataset, const Object & query_object, const int & N, double (*metric)(const Object &, const Object &));

	// runs exact nearest neighbors using given metric function and returns an array of nearest neighbors and distances found
	std::vector <std::pair <double, const Object*> > exact_nearest_neighbors(const Dataset & dataset, const Object & query_object, const int & N, double (*metric)(const Object &, const Object &));

	// runs approximate range search using given metric function 
	//There is another parameter R2. Given R and R2, this function actually only stores in the set points which belong to the ring [R2, R) with center the query_object
	// Here by ring [r, R) with center C is the set of points with r <= dist < R where dist is the distance of the point from the center
	// By default R2 is 0 so the ring [0, R) is acually the ball with radius R 
	std::set <std::pair <double, const Object*> > range_search(const Object & query_object, const int & R, double (*metric)(const Object &, const Object &), const int R2 = 0);
	
};

#endif