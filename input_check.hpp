/* file : input_check.hpp */
#ifndef _INPUT_CHECK_HPP_
#define _INPUT_CHECK_HPP_
#include <iostream>
#include <string>

// checks for correct input args from terminal and initializes program parameters if so
bool check_init_args(int argc, const char ** argv, std::string & input_file, std::string & query_file, int & k, int & L, std::string & output_file, int & N, int & R);
// checks if given string encodes a proper integer (string of digits)
bool is_integer(const char * string);
// opens and reads given input file and initializes n,d,dataset
bool read_input_file(std::string & input_file, int & n, int & d, float *** dataset, std::string ** point_identifier);

#endif