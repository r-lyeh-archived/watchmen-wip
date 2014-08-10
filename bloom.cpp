#include <iostream>
#include <vector>
#include <stdint.h>
#include <cassert>

int main() {
    std::vector< int > primes = {
          2,      3,      5,      7,     11,     13,     17,     19,     23,     29, 
         31,     37,     41,     43,     47,     53,     59,     61,     67,     71, 
         73,     79,     83,     89,     97,    101,    103,    107,    109,    113, 
        127,    131,    137,    139,    149,    151,    157,    163,    167,    173, 
        179,    181,    191,    193,    197,    199,    211,    223,    227,    229, 
        233,    239,    241,    251,    257,    263,    269,    271,    277,    281, 
        283,    293,    307,    311,    313,    317,    331,    337,    347,    349, 
        353,    359,    367,    373,    379,    383,    389,    397,    401,    409, 
        419,    421,    431,    433,    439,    443,    449,    457,    461,    463, 
        467,    479,    487,    491,    499,    503,    509,    521,    523,    541, 
        547,    557,    563,    569,    571,    577,    587,    593,    599,    601, 
        607,    613,    617,    619,    631,    641,    643,    647,    653,    659, 
        661,    673,    677,    683,    691,    701,    709,    719,    727,    733, 
        739,    743,    751,    757,    761,    769,    773,    787,    797,    809, 
        811,    821,    823,    827,    829,    839,    853,    857,    859,    863, 
        877,    881,    883,    887,    907,    911,    919,    929,    937,    941, 
        947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013
    };

    uint64_t max = 1;
    for( auto &prime : primes ) {
        if( max >= max * prime ) {
            std::cout << "longest 64bit prime found" << std::endl;
            break;
        } else {
            max *= prime;
            std::cout << prime << ") " << max << std::endl;
        }
    }

    struct bloom {
        // Computing a set:
        // Compute the product of all of the elemental primes in the set.
        // s = a * b * c
        // Testing for element membership:
        // Test the modulus of the set number.
        // (s % a) == 0
        // Adding to the set:
        // Multiply the existing set product by the new element’s prime number.
        // s *= d
        // Removing from the set:
        // Divide the existing set product by the element’s prime number.
        // s /= a
        uint64_t prime = 1;
        void include( int p ) {
            prime *= p;
        }
        void include( const std::vector<int> &vp ) {
            for( auto &p : vp ) {
                include( p );
            }
        }
        void exclude( int p ) {
            prime /= p;
        }
        bool maybe( int p ) {
            return ( prime % p ) == 0;
        };
    };

    bloom bl;
    bl.include( {2,3,5,7} );
    assert( bl.maybe(2) );
    assert( !bl.maybe(13) );
    assert( !bl.maybe(26) );
    assert( !bl.maybe(27) );

    bl.include( 13 );
    assert( bl.maybe(2) );
    assert( bl.maybe(13) );
    assert( bl.maybe(26) );
    assert( !bl.maybe(27) );

}
