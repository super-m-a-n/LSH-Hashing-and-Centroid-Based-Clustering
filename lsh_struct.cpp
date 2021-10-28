//file:lsh_struct.cpp//
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <chrono>
#include <queue>
#include <utility>
#include <vector>
#include "params.hpp"
#include "lsh_struct.hpp"
#include "hash.hpp"
#include "dataset.hpp"
#include "object.hpp"

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

void lsh_struct::import_data(Dataset & dataset)
{
	int num_of_Objects = dataset.get_num_of_Objects();

	for (int i = 0; i < L; ++i)						// for each of the L hash-tables
	{
		for (int j = 0; j < num_of_Objects; ++j)	// for each of the point-Objects
		{
			(this->lsh_hash_struct[i])->insert(dataset.get_ith_object(j)); // insert object into hash-table
		}
	}

}

bool lsh_struct::execute(const Dataset & dataset, Dataset & query_dataset, const std::string & output_file, const int & N, const int & R, double (*metric)(const Object &, const Object &))
{

	std::ofstream file (output_file, std::ios::out);		// open output file for output operations
	
	if (!file.is_open())			// check if file was opened properly
	    return false;				// error occured

	int num_of_Objects = query_dataset.get_num_of_Objects();

	for (int i = 0; i < num_of_Objects; i++)		// run for each of the query Objects
	{
		file << "Query: query Object " << (query_dataset.get_ith_object(i)).get_name() << "\n\n";
		// run approximate and exact nearest neighbors and write results into file
		this->nearest_neighbors(dataset, query_dataset.get_ith_object(i), file, N, metric);
		// run approximate range search and write results into file
		this->range_search(query_dataset.get_ith_object(i), file, R, metric);
	}

	return true;
}

void lsh_struct::nearest_neighbors(const Dataset & dataset, Object & query_object, std::ofstream & file, const int & N, double (*metric)(const Object &, const Object &))
{

	// run approximate kNN

	// initialize an empty set of strings-object names, that will serve as a visited set, so that we check each object at most once
	std::set <std::string> visited_set;
	// initialize a min heap priority queue, that will store the Object identifier string name and the distance of Object from query object
	std::priority_queue <std::pair <double, std::string>, std::vector<std::pair <double, std::string> >, std::greater<std::pair <double, std::string> > > min_heap;

	//start timer
	auto t_lsh_start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < L; ++i)
	{
		// get bucket index in i-th hash table, for given query object
		int bucket = (this->lsh_hash_struct[i])->get_bucket_index(query_object);

		// iterate the bucket of hash table that the bucket index indicates
		for (auto const& object : (this->lsh_hash_struct[i])->get_ith_bucket(bucket))
		{
			// if given object has not been visited yet and has same locality ID with query object
			if (visited_set.count(object->get_name()) == 0 && object->get_id() == query_object.get_id())
			{
				// add object's name (unique identifier) into visited set
				visited_set.insert(object->get_name());
				double dist = (*metric)(query_object, *object);
				min_heap.push(std::make_pair(dist, object->get_name()));
			}
		}
	}

	// if Objects with same locality ID, are fewer than N
	//if (min_heap.size() < N)
	//{
		// TODO : run again perhaps
	//}

	// end timer
	auto t_lsh_end = std::chrono::high_resolution_clock::now();

	// run brute force exact kNN
	int num_of_Objects = dataset.get_num_of_Objects();

	// initialize a min heap priority queue, that will store the distances of Objects from query object
	std::priority_queue <double, std::vector<double>, std::greater<double> > brute_force_min_heap;

	// start timer
	auto t_true_start = std::chrono::high_resolution_clock::now();

	// check each of the dataset objects by brute force
	for (int i = 0; i < num_of_Objects; ++i)
	{
		// find its distance from query object
		double dist = (*metric)(query_object, dataset.get_ith_object(i));
		// and insert it into min heap (memory inefficient but faster than keeping an array sorted through iterations, further testing required)
		brute_force_min_heap.push(dist);
	}

	// end timer
	auto t_true_end = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < N; ++i)
	{
		if (!min_heap.empty())		// neighbors found maybe less than N
		{
			std::string object_name = std::get<1>(min_heap.top());
			double dist = std::get<0>(min_heap.top());
			min_heap.pop();

			file << "Nearest neighbor-" << i+1 << " : Point-Object " << object_name << '\n';
			file << "distanceLSH : " << dist << '\n';
		}

		if (!brute_force_min_heap.empty())
		{
			double dist = brute_force_min_heap.top();
			brute_force_min_heap.pop();
			file << "distanceTrue : " << dist << "\n\n";
		}
	}

	// get execution for LSH in milliseconds 
    std::chrono::duration <double, std::milli> tLSH = t_lsh_end - t_lsh_start;
    // get execution for brute force in milliseconds
    std::chrono::duration <double, std::milli> tTrue = t_true_end - t_true_start;
    // write times of execution in file
    file << "tLSH : " << tLSH.count() << "ms\n";
    file << "tTrue : " << tTrue.count() << "ms\n\n";
}


void lsh_struct::range_search(Object & query_object, std::ofstream & file, const int & R, double (*metric)(const Object &, const Object &))
{
	file << "R-near neighbors: (R = " << R << ")" << '\n';

	// initialize an empty set of strings-object names, that will serve as a visited set, so that we check each object at most once
	std::set <std::string> visited_set;

	for (int i = 0; i < L; ++i)
	{
		// get bucket index in i-th hash table, for given query object
		int bucket = (this->lsh_hash_struct[i])->get_bucket_index(query_object);

		// iterate the bucket of hash table that the bucket index indicates
		for (auto const& object : (this->lsh_hash_struct[i])->get_ith_bucket(bucket))
		{
			// if current object has not been visited yet, and is within range
			if (visited_set.count(object->get_name()) == 0 && (*metric)(query_object, *object) < R )
			{
				// add object's name (unique identifier) into visited set
				visited_set.insert(object->get_name());
				// object is within range, so write it into file
				file << "Point-Object " << object->get_name() << '\n';
			}
		}
	}

	file << "\n\n";
}

double euclidean(const Object & p, const Object & q)
{
	return p.euclidean_distance(q);
}
