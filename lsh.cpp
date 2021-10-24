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
	// variables for program input files
	std::string input_file, query_file, output_file;

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
	
	// read input file and initialize arguments n and d
	if (!read_input_file(input_file, n, d))
	{
		std::cerr << "\nGiven input file path/name could not be found (invalid file path)\n\n";
		exit(EXIT_FAILURE);
	}

	// create a dataset object that will hold all the input objects-points
	Dataset dataset(n, input_file);

	//dataset.print();
	
	w = 4;		// experimental value (testing required)

	int numBuckets = n/1000;		// experimental value (testing required)
	// create entire structure for lsh algorithm
	lsh_struct lsh(numBuckets);

	
	return EXIT_SUCCESS;

}