//file:input_check.cpp//
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "input_check.hpp"

bool check_init_args(int argc, const char ** argv, std::string & input_file, std::string & query_file, int & k, int & L, std::string & output_file, int & N, int & R)
{
	// set default values for the parameters, in case no specific value was given through terminal (all cmd parameters are optional)
	input_file = "";
	query_file = "";
	output_file = "";
	k = 4;
	L = 5;
	N = 1;
	R = 10000;

	// cmd input should have an odd number of args (an even number due to ("-x", value) pairs , plus the argv[0])
	if (argc % 2 == 0)
		return false;
	int i = 2;
	// cmd input should have "-x" at odd positions (x is in {i,q,o,k,L,N,R}) and actual parameter values at even positions
	while (i < argc)
	{
		if (!strcmp(argv[i-1], "-i"))
		{
			input_file = argv[i];
		}
		else if (!strcmp(argv[i-1], "-q"))
		{
			query_file = argv[i];
		}
		else if (!strcmp(argv[i-1], "-o"))
		{
			output_file = argv[i];
		}
		else if (!strcmp(argv[i-1], "-k"))
		{
			if (!is_integer(argv[i]) || !atoi(argv[i]))
				return false;
			k = atoi(argv[i]);
		}
		else if (!strcmp(argv[i-1], "-L"))
		{
			if (!is_integer(argv[i]) || !atoi(argv[i]))
				return false;
			L = atoi(argv[i]);
		}
		else if (!strcmp(argv[i-1], "-N"))
		{
			if (!is_integer(argv[i]) || !atoi(argv[i]))
				return false;
			N = atoi(argv[i]);
		}
		else if (!strcmp(argv[i-1], "-R"))
		{
			if (!is_integer(argv[i]) || !atoi(argv[i]))
				return false;
			R = atoi(argv[i]);
		}
		else
			return false;

		i+=2;
	}

	return true;
}

bool check_init_args(int argc, const char ** argv, std::string & input_file, std::string & config_file, std::string & output_file, bool & complete, std::string & method)
{
	// all cmd parameters here are mandatory (for clustering)
	if (argc != 10 && argc != 9)
	{
		std::cerr << "\nWrong command line input. Use : ./cluster -i <input_file> -c <config_file> -o <output_file> -complete <optional> -m <method>\n";
		std::cerr << "-complete is optional, <method> is Classic or LSH or Hypercube\n\n";
		return false;
	}

	if (strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-c") != 0 || strcmp(argv[5], "-o") != 0)
	{
		std::cerr << "\nError: one or more wrong input parameters" << std::endl << "Use : -i -c -o -complete <optional> -m\n\n";
		return false;
	}

	//initialize files
	input_file = argv[2];
	config_file = argv[4];
	output_file = argv[6];

	// check if -complete is given
	if (!strcmp(argv[7], "-complete"))
	{
		complete = true;

		if (!strcmp(argv[8], "-m"))		// check for -m
		{
			// check if <method> is either Classic or LSH or Hypercube
			if (strcmp(argv[9], "Classic") != 0 && strcmp(argv[9], "LSH") != 0 && strcmp(argv[9], "Hypercube") != 0)
			{
				std::cerr << "Error: invalid input parameter <method>" << std::endl << "Use : <method> --> Classic or LSH or Hypercube\n\n";
				return false;
			}
			
			method = argv[9];

		}
		else
		{
			std::cerr << "\nError: one or more wrong input parameters" << std::endl << "Use : -i -c -o -complete <optional> -m\n\n";
			return false;
		}
	}
	else if (!strcmp(argv[7], "-m"))
	{
		complete = false;

		// check if <method> is either Classic or LSH or Hypercube
		if (strcmp(argv[8], "Classic") != 0 && strcmp(argv[8], "LSH") != 0 && strcmp(argv[8], "Hypercube") != 0)
		{
			std::cerr << "Error: invalid input parameter <method>" << std::endl << "Use : <method> --> Classic or LSH or Hypercube\n\n";
			return false;
		}
		
		method = argv[8];

	}
	else
	{
		std::cerr << "\nError: one or more wrong input parameters" << std::endl << "Use : -i -c -o -complete <optional> -m\n\n";
		return false;
	}

	
	return true;
}

bool check_init_config_args(std::string & config_file, int & K, int & L, int & k, int & M, int & d1, int & probes)
{
	return read_config_file(config_file, K, L, k, M, d1, probes);
}

bool read_config_file(std::string & config_file, int & K, int & L, int & k, int & M, int & d1, int & probes)
{
	char * line = NULL;
	char * file_name = &config_file[0];
    size_t length = 0;

    FILE *file_ptr;
	file_ptr = fopen(file_name, "r");  /*open config file , in read mode*/
	
	if (file_ptr == NULL)
	{
		std::cerr << "\nGiven config file path/name could not be found (invalid file path)\n\n";
	    return false;				// file not found
	}

	else    /*following block of code reads from the file and initializes the parameters */
	{
		// set default values for the optional parameters, in case no specific value was given in config file
		L = 3;
		k = 4;
		M = 10;
		d1 = 3;
		probes = 2;

		int line_number = 0;

	  	while(getline(&line, &length, file_ptr) != -1)
	    {
	    	line_number++;
	    	line[strlen(line)-1] = '\0';		// remove newline character from line read from file
	    	if (line[strlen(line)-1] == '\r')	// remove potential \r character from line read from file
	    		line[strlen(line)-1] = '\0';

	    	char * str = strtok(line, " ");
	    	std::string desc;	// description of line
	    	int value;
		    int i = 0;

		    while(str != NULL)
		    {
		    	if (line_number == 1 && i == 0 && strcmp(str, "number_of_clusters:") != 0)
		    	{
		    		std::cerr << "Error: invalid config file" << std::endl << "First line of file should be : number_of_clusters: <int>\n\n";
		    		free(line);
		    		fclose(file_ptr);
		    		return false;	 
		    	}
		    	
		      	if (i == 0)
		      		desc = str;			// save description
		      	else if (i == 1)
		      	{
		      		if (!is_integer(str) || !atoi(str))	// each line's second argument should be a valid integer
		      		{
		      			std::cerr << "Error: invalid config file" << std::endl << "Each line of file should be of the form : description: <int>\n\n";
		      			free(line);
		    			fclose(file_ptr);
						return false;
		      		}
					else
						value = atoi(str);	// save value
		      	}

		      	i++;
		        str = strtok(NULL, " ");
		    }

		    if (i != 2)
		    {
		    	std::cerr << "Error: invalid config file" << std::endl << "Each line of file should be of the form : description: <int>\n\n";
		    	free(line);
		    	fclose(file_ptr);
		    	return false;
		    }

		    // check which description was read, and assign value to corresponding parameter
		    if (desc == "number_of_clusters:")
		    	K = value;
		    else if (desc == "number_of_vector_hash_tables:")
		    	L = value;
		    else if (desc == "number_of_vector_hash_functions:")
		    	k = value;
		    else if (desc == "max_number_M_hypercube:")
		    	M = value;
		    else if (desc == "number_of_hypercube_dimensions:")
		    	d1 = value;
		    else if (desc == "number_of_probes:")
		    	probes = value;
		    else
		    {
		    	std::cerr << "Error: invalid config file" << std::endl << "description" << desc << "not valid\n\n";
		    	free(line);
		    	fclose(file_ptr);
		    	return false;
		    }
	    }

	   	free(line);
	}

	// close file
	fclose(file_ptr);

	return true;
}

bool is_integer(const char * string)
{
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		if (string[i] < '0' || string[i] > '9')
			return false;
	}

	return true;
}

bool read_input_file(std::string & input_file, int & n, int & d)
{
	// we use C code to read file because its faster than C++ and given input files are massive
	char * line = NULL;
	char * file_name = &input_file[0];
    size_t length = 0;

    FILE *file_ptr;
	file_ptr = fopen(file_name, "r");  /*open input file , in read mode*/
	
	if (file_ptr == NULL)
	    return false;				// file not found

	else    /*following block of code reads from the file and finds the number of points n and the dimension of the points d */
	{
	  	while(getline(&line, &length, file_ptr) != -1)
	    {
	    	n++;			// one point-object is in each line of file
	    	if (n == 1)		// find dimension d of all point-objects just once (at first point)
	    	{
	    		line[strlen(line)-1] = '\0';		// remove newline character from line read from file
	    		if (line[strlen(line)-1] == '\r')	// remove potential \r character from line read from file
	    			line[strlen(line)-1] = '\0';

	    		char *str = strtok(line, " ");
		      	int i = 0;
		      	while(str != NULL)
		      	{
		      		i++;
		         	str = strtok(NULL, " ");
		      	}

		      	d = i - 1;
	    	}
	     
	     }

	    free(line);
	}

	// rewind to the start of the file
	rewind(file_ptr);
	// close file
	fclose(file_ptr);

	return true;
}

