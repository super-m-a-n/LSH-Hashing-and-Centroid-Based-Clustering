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
	uint32_t M = 4294967291;		// large prime M = 2^32 - 5, <= 32 bits

	// following block of code does a linear combination of h_i with r_i avoiding overflow
	// by casting to int64_t before each + or * operation
	// and using the modulo property that (a op b) mod M = [(a mod M) op (b mod M)] mod M, where op = + or *
	
	// calculate right nested operand : (r[k-1] * h[k-1](p)) mod M = ( r[k-1] mod M ) * ( h[k-1](p) mod M ) mod M
	int64_t right = mod(mod((int64_t) this->r[k-1], (int64_t) M) * mod((int64_t) (this->h[k-1])(p), (int64_t) M), (int64_t) M);
	int64_t left;

	for (int i = k-2; i >= 0; --i)
	{
		// calculate left nested operand : [ r[i] * h[i](p) ] mod M = ( r[i] mod M ) * ( h[i](p) mod M ) mod M
		left = mod(mod((int64_t) this->r[i], (int64_t) M) * mod((int64_t) (this->h[i])(p), (int64_t) M), (int64_t) M);
		right = mod(left + right, (int64_t) M);		// calculate new right nested operand
	}

	object_id = (uint32_t) right; // right is always a number mod M, so positive and at most as big as M (32 bits), so this cast is safe
	p.set_id(object_id);

	return object_id % table_size;
}

g_hash::~g_hash()
{
	delete[] r;
	delete[] h;
}

int64_t mod(int64_t x, int64_t y)
{
	return (((x % y) + y) % y);		// modulo operator for negative divisor or dividend
}

