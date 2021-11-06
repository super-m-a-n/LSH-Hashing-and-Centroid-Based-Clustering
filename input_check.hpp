/* file : input_check.hpp */
#ifndef _INPUT_CHECK_HPP_
#define _INPUT_CHECK_HPP_
#include <iostream>
#include <string>

// checks for correct input args from terminal and initializes program parameters if so (for lsh)
bool check_init_args(int argc, const char ** argv, std::string & input_file, std::string & query_file, int & k, int & L, std::string & output_file, int & N, int & R);

// checks for correct input args from terminal and initializes program parameters if so (for clustering)
bool check_init_args(int argc, const char ** argv, std::string & input_file, std::string & config_file, std::string & output_file, bool & complete, std::string & method);
// checks for correct input args from config file and initializes program parameters if so (for clustering for the config file)
bool check_init_config_args(std::string & config_file, int & K, int & L, int & k, int & M, int & d1, int & probes);
// opens and reads given config file and initializes program parameters K,L,k,M,d1,probes 
bool read_config_file(std::string & config_file, int & K, int & L, int & k, int & M, int & d1, int & probes);

// checks if given string encodes a proper integer (string of digits)
bool is_integer(const char * string);
// opens and reads given input file and initializes number of points n, and dimension of points d
bool read_input_file(std::string & input_file, int & n, int & d);

#endif