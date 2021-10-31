
#include "assist_functions.hpp"

//computes floor(log_2(n)) + 1
unsigned int get_lg(unsigned int n){
    int r = 0;

    while ( n > 0){
        n = n >> 1;
        r += 1;
    }

    return r;
}