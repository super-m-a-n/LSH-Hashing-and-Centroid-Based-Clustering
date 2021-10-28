//file:hash.cpp//
#include "hash.hpp"
#include "object.hpp"
#include "g_hash.hpp"
#include <iostream>
#include <list>

hash_table::hash_table(int numBuckets) : size(0), capacity(numBuckets)
{
	// calls default constructor for g hash function of hash table
	// allocates memory for the table of lists
	table = new std::list<Object*>[numBuckets];
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
	
void hash_table::insert(Object& p)
{
	int index = g(p, this->capacity);	// g hash function is used to get index in hash-table
	this->table[index].push_back(&p);	// pointer to given point-Object is inserted at index
}

int hash_table::get_bucket_index(Object& p)
{
	return g(p, this->capacity);
}

const std::list<Object*> & hash_table::get_ith_bucket(int bucket_index) const
{
	return this->table[bucket_index];
}