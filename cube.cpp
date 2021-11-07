//file:lsh.cpp//
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <cstdlib>
#include "input_check.hpp"
#include "dataset.hpp"
#include "params.hpp"
#include "hypercube_class.hpp"
#include "assist_functions.hpp"

// global program parameters
int k, L, N, R, d = 0, d1, w, n = 0, probes, M;

//./cube –i <input file> –q <query file> –k <int> -M <int> -probes <int> -ο
// <output file> -Ν <number of nearest> -R <radius>

int main(int argc, char const *argv[])
{
	// variables for program input files
	std::string input_file, query_file, output_file;

	srand(time(NULL));

	// check for input args and initialize them
	if (!check_init_args(Hypercube, argc, argv, input_file, query_file, k, M, probes, L, output_file, N, R))
	{
		std::cerr << "\nWrong command line input. Use : ./cube –i <input file> –q <query file> –k <int> -M <int> -probes <int>\
                        -ο <output file> -Ν <number of nearest> -R <radius>\n";
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
	
	w = 747;		// experimental value (testing required)

	//If the user did not give an input for the dimension of the hypercube then initialise it to floor(log_2(n)) -1
	if (d1 < 0){
		d1 = get_lg(n) - 2;            // d1 = floor(log_2(n)) - 1
	}
    
	// create entire structure for hypercube algorithm
	hypercube cube;

	// import dataset into lsh struct
	cube.import_data(dataset);

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

		// create a dataset object that will hold all the query objects-points
		Dataset query_dataset(nq, query_file);

		if (output_file.empty())
		{
			std::cout << "\nPlease give an output file path ->  ";
			std::getline(std::cin, output_file);
			std::cout << std::endl;
		}

		// execute kNN, range search nearest neighbors algorithms using euclidean metric
		if (!cube.execute(dataset, query_dataset, output_file, N, R, euclidean))
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