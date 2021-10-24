//file:dataset.cpp//
#include <iostream>
#include "dataset.hpp"
#include "object.hpp"

Dataset::Dataset(int num_of_Points, float ** input_data) : num_of_Objects(num_of_Points)
{
	dataset = new Object*[num_of_Points];

	for (int i = 0; i < num_of_Objects; ++i)
	{
		dataset[i] = new Object(input_data[i]);
	}
}

Dataset::~Dataset()
{
	for (int i = 0; i < num_of_Objects; ++i)
	{
		delete dataset[i];
	}

	delete[] dataset;
}

void Dataset::print() const
{
	for (int i = 0; i < num_of_Objects; ++i)
	{
		std::cout << "Point" << i+1 << " ->  (";
		this->dataset[i]->print();
		std::cout << ")" << std::endl << std::endl;
	}
}