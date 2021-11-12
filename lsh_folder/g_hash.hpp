//file:g_hash.hpp//
#ifndef _G_HASH_HPP_
#define _G_HASH_HPP_
#include <iostream>
#include <cstdint>
#include "object.hpp"
#include "h_hash.hpp"
#include "params.hpp"

// class g_hash is used to hold info about an amplified g hash function

class g_hash
{
private:
	h_hash * h;		// an array of h_hash functions since each amplified hash function is composed using k h hash functions
	int  * r;		// an array to hold k random numbers, coeffecients of the k h hash functions used to compose g

public:
	// default constructor
	g_hash();
	~g_hash();
	// overload of () operator, so that each g_hash object can be used as a "function"
	int operator()(const Object& p, int table_size, uint32_t & object_id) const;	
};


int64_t mod(int64_t x, int64_t y);

#endif