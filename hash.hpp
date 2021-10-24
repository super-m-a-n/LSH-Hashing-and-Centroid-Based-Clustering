//file:hash.hpp//
#ifndef _HASH_HPP_
#define _HASH_HPP_
#include <iostream>
#include <list>
#include "g_hash.hpp"
#include "object.hpp"


class hash_table
{
private:
	std::list<Object*> * table;		// hash table implemented as an array of linked lists containing pointers to points-Objects
	int size;						// number of elements added
	int capacity;					// number of buckets
	g_hash g;						// amplified g hash function for hash table


public:
	// constructor
	hash_table(int numBuckets);
	// destructor
	~hash_table();
	// returns number of elements currently in hash table
	int get_size() const;
	// returns number of buckets currently in hash table
	int get_capacity() const;
	// inserts given point-object into hash table
	void insert(Object& p);
};

#endif