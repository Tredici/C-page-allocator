#include <iostream>
#include "../page_allocator.h"
#include <stdlib.h>

using namespace std;

constexpr size_t N = 100;

int main(int argc, char const *argv[])
{
    cout << "TEST: " << __FILE__ << endl;
    // initialize test variables
    bitarray my_ba; page_allocator pa;
    char buffer[N];
    int  numbers[N]  = {};
    int *pointers[N] = {};
    // init page allocator
    if (!page_allocator_init(&pa, numbers, sizeof(int), buffer, N))
    {
        cerr << "ERROR: page_allocator_init" << endl;
        return 1;
    }

    if (page_allocator_size(&pa) != N)
    {
        cerr << "ERROR: page_allocator_size" << endl;
        return 1;
    }

    if (page_allocator_page_size(&pa) != sizeof(int))
    {
        cerr << "ERROR: page_allocator_page_size" << endl;
        return 1;
    }

    cout << "ALLOCATE" << endl;
    for (int i{}; i!=N; ++i)
    {
        cout << i << ") " << (pointers[i] = (int*)page_allocator_allocate(&pa)) << endl;
    }
    cout << "FLIP" << endl;
    for (int i{}; i!=N; ++i)
    {
        if (page_allocator_free(&pa, pointers[i]))
        {
            cerr << "ERROR FREE: (" << i << ")" << pointers[i] << endl;
            exit(EXIT_FAILURE);
        }
        // always the first empty page is returned!
        if ((int*)page_allocator_allocate(&pa) != pointers[i])
        {
            cerr << "ERROR REALLOCATE: (" << i << ")" << endl;
        }
    }
    // free al memory!
    cout << "CLEAR!" << endl;
    for (int i{}; i!=N; ++i)
    {
        if (page_allocator_free(&pa, pointers[i]))
        {
            cerr << "ERROR FREE: (" << i << ")" << pointers[i] << endl;
            exit(EXIT_FAILURE);
        }
    }
    cout << "TEST PASSED!" << endl;

    return 0;
}
