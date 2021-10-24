//file:g_hash.cpp//
#include "g_hash.hpp"
#include "params.hpp"
#include "object.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <cstdint>

g_hash::g_hash()
{
	// creates and calls default constructor for each of the k h-hash functions
	h  = new h_hash[k];		
	// creates an array of k integers
	r = new int[k];
	// picks k random positive integers and stores them into array r
	const int lower_bound = 1;
	const int upper_bound = 10000;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distr(lower_bound, upper_bound);
	
	for (int i = 0; i < k; ++i)
	{
		r[i] = distr(generator);
	}

}

int g_hash::operator()(Object& p, int table_size) const
{
	uint32_t object_id = 0;
	//uint32_t M = 4294967291;		// large prime M = 2^32 - 5, <= 32 bits

	// TODO: do a linear combination of h_i with r_i avoiding overflow
	p.set_id(object_id);

	return object_id % table_size;
}

g_hash::~g_hash()
{
	delete[] r;
	delete[] h;
}