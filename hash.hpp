//file:hash.hpp//
#ifndef _HASH_HPP_
#define _HASH_HPP_
#include <iostream>
#include <list>
#include <utility>
#include <cstdint>
#include "g_hash.hpp"
#include "object.hpp"


class hash_table
{
private:
	std::list <std::pair <const Object*, uint32_t> > * table;		// hash table implemented as an array of linked lists containing pointers to points-Objects and locality ID for each object
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
	void insert(const Object& p);
	// returns bucket index in which given object p hashes in and its locality ID in object_id
	int get_bucket_index(const Object& p, uint32_t & object_id);
	// returns bucket-list indicated by bucket index
	const std::list <std::pair <const Object*, uint32_t> > & get_ith_bucket(int bucket_index) const;
};

#endif