
#ifndef PAGE_ALLOCATOR
#define PAGE_ALLOCATOR

#include "bitarray.h"

struct page_allocator
{
    struct bitarray bitfield;
    void *page_buffer;
    unsigned long page_size;
};

/**
 * Initialize page allocator
 */
struct page_allocator *page_allocator_init(struct page_allocator *pa, void *page_buffer, unsigned long page_size, void *bit_buffer, unsigned long len);

/**
 * Get total page count
 */
long page_allocator_size(struct page_allocator *pa);

/**
 * Get page size
 */
long page_allocator_page_size(struct page_allocator *pa);

/**
 * Return a pointer pointing to the first bit in a page or
 * NULL is nothing is available
 */
void *page_allocator_allocate(struct page_allocator *pa);

/**
 * Return a previously allocated page to the allocator
 */
int page_allocator_free(struct page_allocator *pa, void *page);

#endif
