//file:h_hash.cpp//
#include "h_hash.hpp"
#include "params.hpp"
#include "object.hpp"
#include <iostream>
#include <random>
#include <cmath>

h_hash::h_hash()
{
	// calls default constructor for point Object v, which makes v a random normalized vector-point
	// picks single precision real t uniformly in [0,w)
	const float lower_bound = 0.0;
	const int upper_bound = w;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distr(lower_bound, upper_bound);

	t = distr(generator);

}

int h_hash::operator()(const Object& p) const
{
	return floor(((this->v).inner_prod(p) + this->t) / w);		// definition of h hash function
}

void h_hash::print() const
{
	(this->v).print();
	std::cout << std::endl << this->t << std::endl;

}