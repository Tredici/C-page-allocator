
#include "page_allocator.h"
#include "bitarray.h"

// Cannot rely on prexisting libraries is OS code
#define NULL (void*)0

struct page_allocator *page_allocator_init(struct page_allocator *pa, void *page_buffer, unsigned long page_size, void *bit_buffer, unsigned long len)
{
    if (!pa || !bit_buffer || !page_size || !page_buffer || !len)
    {
        return (struct page_allocator*)NULL;
    }
    // enforce page alignment and
    if ((unsigned long)page_buffer % page_size)
    {
        return (struct page_allocator*)NULL;
    }

    *pa = (struct page_allocator){}; //zero everything
    // init bitarray to track managed pages
    if (!bitarray_init(&pa->bitfield, bit_buffer, len))
    {
        return (struct page_allocator*)NULL;
    }
    // zero pages
    char *tmp = (char *)page_buffer;
    for (unsigned long i = 0; i != len*page_size; ++i)
    {
        *(tmp++) = 0;
    }
    pa->page_size = page_size;
    pa->page_buffer = page_buffer;
    return pa;
}

long page_allocator_size(struct page_allocator *pa)
{
    if (!pa)
    {
        return -1;
    }
    return bitarray_size(&pa->bitfield);
}

long page_allocator_page_size(struct page_allocator *pa)
{
    if (!pa)
    {
        return -1;
    }
    return pa->page_size;
}

void *page_allocator_allocate(struct page_allocator *pa)
{
    // check arguments
    if (!pa || !pa->page_buffer)
    {
        return NULL;
    }
    // find available page
    long page = bitarray_first_reset(&pa->bitfield);
    // no page available
    if (page < 0)
    {
        return NULL;
    }
    bitarray_set(&pa->bitfield, page);
    return (char*)pa->page_buffer + pa->page_size*page;
}

int page_allocator_free(struct page_allocator *pa, void *page)
{
    // check arguments
    if (!pa || !pa->page_buffer || !page)
    {
        return -1;
    }
    // check page address
    const long offset = (char*)page - (char*)pa->page_buffer;
    // check page alignment
    if (offset < 0 || offset % pa->page_size)
    {
        return -1;
    }
    const long page_num = offset / pa->page_size;
    // page was borrowed?
    if (!bitarray_get(&pa->bitfield, page_num))
    {
        return -1;
    }
    // zero page
    char *cell = (char *)page;
    for (unsigned long i = 0; i != pa->page_size; ++i)
    {
        *cell++ = 0;
    }
    // return page
    bitarray_reset(&pa->bitfield, page_num);

    return 0;
}
