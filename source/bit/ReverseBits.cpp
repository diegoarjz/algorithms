#include "ReverseBits.h"

unsigned int ReverseBits(const unsigned int & inBits){
    auto result = inBits;
    
    // 0101 0101 etc
    // 1010 1010
    unsigned int u0 = 0x55555555;
    result = (((result >> 1) & u0) | ((result & u0) << 1));
    
    // 0011 0011 0011 0011 0011 etc
    // 1100 1100 1100 1100 1100
    unsigned int u1 = 0x33333333;
    result = (((result >> 2) & u1) | ((result & u1) << 2));
    
    // 0000 1111 0000 1111 etc
    // 1111 0000 1111 0000
    unsigned int u2 = 0x0f0f0f0f;
    result = (((result >> 4) & u2) | ((result & u2) << 4));
    
    // 0000 0000 1111 1111 0000 0000 1111 1111 etc
    // 1111 1111
    unsigned int u3 = 0x00ff00ff;
    result = (((result >> 8) & u3) | ((result & u3) << 8));
    
    result = (((result >> 16) | (result << 16)) %  0x100000000);
    
    return result;
}
