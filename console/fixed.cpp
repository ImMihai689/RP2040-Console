#include "fixed.hpp"

Fixed Fixed::map(Fixed val, Fixed min1, Fixed max1, Fixed min2, Fixed max2)
{
    return min2 + (val - min1) * (max2 - min2) / (max1 - min1);
}

Fixed Fixed::inverse_sqrt(Fixed number)
{
    float floating = (float)number.value / (float)262144;
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = floating * 0.5F;
    y  = floating;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return Fixed(y);
}