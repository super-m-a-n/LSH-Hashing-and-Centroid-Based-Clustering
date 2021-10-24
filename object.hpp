//file:object.hpp//
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include <iostream>
#include <cstdint>
#include "params.hpp"

// class Object holds the data of the input objects-points of the dataset
// i.e. the coordinates in a d-vector and the object id 

class Object 
{
private:
	float * vector;			// the coordinates of the d-dimensional point-object in an array
	uint32_t id;			// the id of the point-object

public:
	// default constructor creates a random normalized d-dimensional point-object, each coordinate follows normal(0,1) distribution 
	Object();
	// constructor through another d-dimensional input array
	Object(float input_vector[]);
	~Object();
	// id setter
	void set_id(uint32_t object_id);
	// calculates the inner-product of calling object with given object p (both d-dimensional)
	float inner_prod(const Object& p) const;
	// print method for debugging
	void print() const;
};

#endif
