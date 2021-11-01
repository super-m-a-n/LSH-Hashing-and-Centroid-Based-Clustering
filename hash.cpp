//file:hash.cpp//
#include "hash.hpp"
#include "object.hpp"
#include "g_hash.hpp"
#include <iostream>
#include <list>
#include <utility>
#include <cstdint>

hash_table::hash_table(int numBuckets) : size(0), capacity(numBuckets)
{
	// calls default constructor for g hash function of hash table
	// allocates memory for the table of lists
	table = new std::list <std::pair <const Object*, uint32_t> >[numBuckets];
}

hash_table::~hash_table()
{
	delete[] table;
}

int hash_table::get_size() const
{
	return this->size;
}

int hash_table::get_capacity() const
{
	return this->capacity;
}
	
void hash_table::insert(const Object& p)
{
	uint32_t object_id = 0;
	int index = g(p, this->capacity, object_id);				 // g hash function is used to get index in hash-table and locality object_id of given object
	this->table[index].push_back(std::make_pair(&p, object_id)); // pointer to given point-Object and its locality ID are inserted at index
}

int hash_table::get_bucket_index(const Object& p, uint32_t & object_id)
{
	return g(p, this->capacity, object_id);
}

const std::list <std::pair <const Object*, uint32_t> > & hash_table::get_ith_bucket(int bucket_index) const
{
	return this->table[bucket_index];
}