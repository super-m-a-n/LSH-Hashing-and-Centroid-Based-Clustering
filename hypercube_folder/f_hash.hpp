//File:f_hash_hpp//
#ifndef F_HASH_HPP
#define F_HASH_HPP

#include "h_hash.hpp"
#include "object.hpp"
#include <unordered_map>

// class f_hash are functions  which map integers randomly to {0,1} 

class f_hash{

private:
	std::unordered_map<int, uint8_t> value_map;  //Evety value given to f will be mapped to 0 or 1 randomly
                                            //But when a value is evaluated, it is store so that he value will remain the same
                                            // so that f will act like a function
public:
	// Just initialise the value_map
	f_hash();
	// overload of () operator, so that f_hash can be used as a "function" for integers
	uint8_t operator()(int p);	
	// print method for debugging
	//void print() const;

    ~f_hash();
};

#endif