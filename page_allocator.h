
#ifndef PAGE_ALLOCATOR
#define PAGE_ALLOCATOR

#include "bitarray.h"

struct page_allocator
{
    struct bitarray bitfield;
    void *page_buffer;
    unsigned long page_size;
};


#endif
