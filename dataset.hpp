//file:dataset.hpp//
#ifndef _DATASET_HPP_
#define _DATASET_HPP_
#include <iostream>
#include "object.hpp"

// class Dataset is simply a collection of point-Objects
class Dataset
{
private:
	Object ** dataset; 		// an array of pointers to Objects
	int num_of_Objects;

public:
	// constructor uses a 2dim array input data to initialize the dataset
	Dataset(int num_of_Points, float ** input_data);
	~Dataset();
	// print method for debugging
	void print() const;
	
};

#endif