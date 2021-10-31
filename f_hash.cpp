#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <time.h>
#include "f_hash.hpp"


f_hash::f_hash() : value_map(){}


	// overload of () operator, so that each h_hash object can be used as a "function"
uint8_t f_hash::operator()(int p){
    std::unordered_map<int,uint8_t>::const_iterator it = this->value_map.find(p);

    // int p has not be evaluated by f yet so choose randomlly fromm {0,1} and save that choice
    if ( it == this->value_map.end() ){
        return this->value_map[p] = rand() % 2;
    }    
    else{
        return it->second;
    }
}	
// print method for debugging
//void print();

//No need for a destructor, the unordered map has already a destructor
f_hash::~f_hash(){}