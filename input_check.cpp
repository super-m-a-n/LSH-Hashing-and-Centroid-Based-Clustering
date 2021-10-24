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

