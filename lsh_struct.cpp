//file:lsh_struct.cpp//
#include <iostream>
#include "params.hpp"
#include "lsh_struct.hpp"
#include "hash.hpp"

lsh_struct::lsh_struct(int hash_table_size)
{
	// lsh_hash_struct is an array of pointers to L hash tables
	lsh_hash_struct = new hash_table*[L];

	for (int i = 0; i < L; ++i)
	{
		lsh_hash_struct[i] = new hash_table(hash_table_size);
	}
}

lsh_struct::~lsh_struct()
{

	for (int i = 0; i < L; ++i)
		delete lsh_hash_struct[i];

	delete[] lsh_hash_struct;
}