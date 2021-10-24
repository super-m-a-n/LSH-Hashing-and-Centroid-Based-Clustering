//file:lsh_struct.hpp//
#ifndef _LSH_STRUCT_HPP_
#define _LSH_STRUCT_HPP_
#include <iostream>
#include "params.hpp"
#include "hash.hpp"

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
	
};

#endif