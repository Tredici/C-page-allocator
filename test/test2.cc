#include <iostream>
#include "../bitarray.h"
#include <bitset>
#include <stdlib.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t attempt = N*5;

int main(int argc, char const *argv[])
{
    cout << "TEST: " << __FILE__ << endl;
    // initialize test variables
    bitarray my_ba;
    char buffer[N];
    if (!bitarray_init(&my_ba, buffer, N))
    {
        cerr << "ERROR: bitarray_init" << endl;
        return 1;
    }
    bitset<N> lib_ba;
    // init random generator
    srand(time(nullptr));
    // randomly set bits
    for (int i{}; i!=attempt; ++i)
    {
        // find bit position
        const size_t bit = rand()%N;
        // try to set or to flip
        // set bit on my object
        bitarray_flip(&my_ba, bit);
        // set bit on check
        lib_ba.flip(bit);
    }

    // check for equivalency
    for (int i{}; i!=N; ++i)
    {
        if (bitarray_get(&my_ba, i) != lib_ba.test(i))
        {
            cerr << "TEST FAILED!!!!" << endl;
            return 1;
        }
    }
    cout << "TEST PASSED!" << endl;

    /* code */
    return 0;
}
