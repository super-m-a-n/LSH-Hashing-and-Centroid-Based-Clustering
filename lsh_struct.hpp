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

	// runs approximate range search using given metric function and write results into file
	void range_search(const Object & query_object, std::ofstream & file, const int & R, double (*metric)(const Object &, const Object &));
	
};

double euclidean(const Object & p, const Object & q);
// can easily expand to other metric function here
// and pass the name of the function as a function pointer to the execute function

#endif