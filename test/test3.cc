#include <iostream>
#include "../bitarray.h"
#include <stdlib.h>

using namespace std;

constexpr size_t N = 100;
constexpr size_t attempt = N*5;

void test(bitarray &my_ba)
{
    int max = rand()%(N+1);
    // clean bitarray
    bitarray_clear(&my_ba);
    // set first max bits
    for (int i{}; i<max; ++i)
    {
        bitarray_set(&my_ba, i);
    }
    long test = bitarray_first_reset(&my_ba);

    // ensure old method whorks!
    for (int i{}; i!=(test == -1 ? N : test); ++i)
    {
        if (!bitarray_get(&my_ba, i))
        {
            cerr << "NOOOOOO" << endl;
            exit(1);
        }
    }

    if (max == N)
    {
        if (test != -1L)
        {
            cerr << "TEST -1 failed" << endl;
            exit(1);
        }
        cout << "-";
    }
    else
    {
        if (test != max)
        {
            cerr << "TEST internal failed: (required:" << max << ",get:" << test << ")" << endl;
            exit(1);
        }
        cout << "+";
    }

}

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
    // init random generator
    srand(time(nullptr));
    // randomly set bits
    for (int i{}; i!=attempt; ++i)
    {
        cout << i << ") ";
        test(my_ba);
        cout << endl;
    }
    cout << "TEST PASSED!" << endl;

    /* code */
    return 0;
}
