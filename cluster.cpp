//file:cluster.cpp//
#include <iostream>
#include <string>
#include "input_check.hpp"
#include "dataset.hpp"
#include "params.hpp"
#include "cluster_info.hpp"

// global program parameters
int k, L, d = 0, d1, w, n = 0, probes, M, K;

int main(int argc, char const *argv[])
{
	// variables for program input files
	std::string input_file, config_file, output_file;
	// if complete is true, output will be verbose
	bool complete;
	// method for assignment part of clustering
	std::string method;	// method is either Classic for classic lloyd's or LSH or Hypercube

	// check for input args and initialize them
	if (!check_init_args(argc, argv, input_file, config_file, output_file, complete, method))
		return EXIT_FAILURE;
	
	// check for config file args and initialize them
	if (!check_init_config_args(config_file, K, L, k, M, d1, probes))
		return EXIT_FAILURE;

	// read input file and initialize arguments n and d
	if (!read_input_file(input_file, n, d))
	{
		std::cerr << "\nGiven input file path/name could not be found (invalid file path)\n\n";
		return EXIT_FAILURE;
	}

	// create a dataset object that will hold all the input objects-points
	Dataset dataset(n, input_file);
	// create a cluster object that will hold info necessary for clustering
	Cluster_info cluster_info;
	// executes clustering using given method and metric, and outputs results into output file
	if (!cluster_info.execute(dataset, output_file, method, complete, euclidean))
	{
		std::cerr << "\nError occured while opening given output file\n\n";
		return EXIT_FAILURE;
	}

	
	return EXIT_SUCCESS;
}