//file:lsh.cpp//
#include <iostream>
#include <string>
#include <cmath>
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
		return EXIT_FAILURE;
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
		return EXIT_FAILURE;
	}

	std::cout << "\nReading Input Dataset   --> ";
	// create a dataset object that will hold all the input objects-points
	Dataset dataset(n, input_file);
	std::cout << "Completed\n";


	w = 40;		// experimental value (testing required)

	int numBuckets = floor(n/16);		// experimental value (testing required)
	// create entire structure for lsh algorithm
	lsh_struct lsh(numBuckets);
	
	std::cout << "Importing Input Dataset --> ";
	// import dataset into lsh struct
	lsh.import_data(dataset);
	std::cout << "Completed\n";

	bool exit_val = false;

	while (exit_val == false)
	{
		if (query_file.empty())
		{
			std::cout << "\nPlease give a query file path ->  ";
			std::getline(std::cin, query_file);
			std::cout << std::endl;
		}

		int nq = 0, dq = 0;
		// read query file and initialize arguments nq and dq
		if (!read_input_file(query_file, nq, dq))
		{
			std::cerr << "\nGiven query file path/name could not be found (invalid file path)\n\n";
			return EXIT_FAILURE;
		}

		std::cout << "Creating Query Dataset  --> ";
		// create a dataset object that will hold all the query objects-points
		Dataset query_dataset(nq, query_file);
		std::cout << "Completed\n";

		if (output_file.empty())
		{
			std::cout << "\nPlease give an output file path ->  ";
			std::getline(std::cin, output_file);
			std::cout << std::endl;
		}

		std::cout << "Executing ...\n";
		// execute kNN, range search nearest neighbors algorithms using euclidean metric
		if (!lsh.execute(dataset, query_dataset, output_file, N, R, euclidean))
		{
			std::cerr << "\nError occured while opening given output file\n\n";
			return EXIT_FAILURE;
		}

		std::string answer;
		while (answer != "t" && answer != "r")	// user must type "t" to terminate or "r" to run again
		{
			std::cout << "\nTerminate (t) or run again for different query file (r) ? (t/r) : ";
			std::getline(std::cin, answer);
		}

		if (answer == "t")
			exit_val = true;
		else if (answer == "r")
		{
			query_file = "";
			output_file = "";
		}
	}
	
	return EXIT_SUCCESS;
}