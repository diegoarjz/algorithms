#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ReverseBit

#include <boost/test/unit_test.hpp>

#include <iostream>

#include "../ReverseBits.h"

template<int N>
void print_bits(const int &n){
    std::cout << ((n>>(N-1))&0x01);
    print_bits<N-1>(n);
}

template<>
void print_bits<1>(const int &n){
    std::cout << (n&0x01);
}


BOOST_AUTO_TEST_CASE(test_reverse_bits){
    for(auto i=0; i<100; ++i){
        BOOST_CHECK( i == ReverseBits(ReverseBits(i)) );
    }
}
