//file:h_hash.hpp//
#ifndef _H_HASH_HPP_
#define _H_HASH_HPP_
#include <iostream>
#include "object.hpp"

// class h_hash is used to hold info about an h hash function

class h_hash
{
private:
	Object v;	// a random normalized vector-point
	float t;	// a single precision real t uniformly in [0,w)	

public:
	// default constructor, randomly chooses v,t
	h_hash();
	// overload of () operator, so that each h_hash object can be used as a "function"
	int operator()(const Object& p) const;	
	// print method for debugging
	void print() const;
};

#endif