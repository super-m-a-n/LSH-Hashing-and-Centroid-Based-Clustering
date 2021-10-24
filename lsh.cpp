//file:lsh.cpp//
#include <iostream>
#include <string>
#include "input_check.hpp"
#include "dataset.hpp"
#include "params.hpp"
#include "lsh_struct.hpp"

// global program parameters
int k, L, N, R, d = 0, w, n = 0;

int main(int argc, char const *argv[])
{
	// program parameters
	std::string input_file, query_file, output_file;
	
	// 2-dim array for the input dataset
	float ** input_dataset = nullptr;
	// string identifiers for the input point-objects
	std::string * point_identifier = nullptr;

	// check for input args and initialize them
	if (!check_init_args(argc, argv, input_file, query_file, k, L, output_file, N, R))
	{
		std::cerr << "\nWrong command line input. Use : ./lsh -i <input_file> -q <query_file> -k <int> -L <int> -o <output_file> -N <int> -R <radius>\n";
		std::cerr << "Each -x <value> pair is optional\n\n";
		exit(EXIT_FAILURE);
	}
	
	//ask for input path, if not given through command line
	if (input_file.empty())
	{
		std::cout << "\nPlease give an input file path ->  ";
		std::getline(std::cin, input_file);
		std::cout << std::endl;
	}
	
	// read input file and initialize arguments
	if (!read_input_file(input_file, n, d, &input_dataset, &point_identifier))
	{
		std::cerr << "\nGiven input file path/name could not be found (invalid file path)\n\n";
		exit(EXIT_FAILURE);
	}

	// create a dataset object that will hold all the input objects-points
	Dataset dataset(n, input_dataset);

	//dataset.print();
	w = 4;

	// cleanup of temporary structs
	for (int i = 0; i < n; ++i)
		delete[] input_dataset[i];
	delete[] input_dataset;
	delete[] point_identifier;

	int numBuckets = n/8;		// experimental value
	// create entire structure for lsh algorithm
	lsh_struct lsh(numBuckets);

	
	return EXIT_SUCCESS;

}