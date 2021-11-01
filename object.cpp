//file:object.cpp//
#include "object.hpp"
#include "params.hpp"
#include <iostream>
#include <string>
#include <random>
#include <cmath>

Object::Object()
{
	vector = new float[d];									// d-dimensional point object

	float norm_squared = 0.0;

	for (int i = 0; i < d; ++i)
	{
		std::random_device rd;
		std::mt19937 generator(rd());
		std::normal_distribution<float> distr(0, 1);		// each coordinate follows normal(0,1) distribution

		vector[i] = distr(generator);

		norm_squared += vector[i] * vector[i];
	}

	for (int i = 0; i < d; ++i)
		vector[i] = vector[i] / sqrt(norm_squared);			// divide each coordinate by norm, to normalize point-object
}

Object::Object(float input_vector[], std::string & object_name) : identifier(object_name)
{
	vector = new float[d];

	for (int i = 0; i < d; ++i)
		vector[i] = input_vector[i];
}

Object::~Object()
{
	delete[] vector;
}

const std::string & Object::get_name() const
{
	return this->identifier;
}

float Object::inner_prod(const Object& p) const
{
	float inner_prod = 0.0;

	for (int i = 0; i < d; ++i)
		inner_prod += this->vector[i] * p.vector[i];

	return inner_prod;
}

double Object::euclidean_distance(const Object& p) const
{
	double dist_squared = 0.0;

	for (int i = 0; i < d; ++i)
		dist_squared += (double) (this->vector[i] - p.vector[i]) * (double) (this->vector[i] - p.vector[i]);

	return sqrt(dist_squared);
}

void Object::print() const
{
	std::cout << "Object " << this->identifier << "--> (";
	for (int i = 0; i < d; ++i)
		std::cout << this->vector[i] << ",";
	std::cout << ")\n";
}