#include "bitarray.h"

// Cannot rely on standard libraries in OS code
#define NULL (void*)0
const long cell_size = sizeof(char);
const long bits_per_cell = cell_size*8;

struct bitarray* bitarray_init(struct bitarray *barray, void *buffer, unsigned long len)
{
    if (!barray || !buffer || !len)
    {
        return (struct bitarray*)NULL;
    }
    char *tmp = (char *)buffer;
    for (unsigned long i = 0; i < len; ++i)
    {
        *(tmp++) = 0;
    }
    *barray = (struct bitarray){}; //zero everything
    barray->len = len;
    barray->buffer = (char *)buffer;
    return barray;
}

static inline unsigned long pos_to_cell(unsigned long pos)
{
    return pos/bits_per_cell;
}

static inline char pos_to_bit(unsigned long pos)
{
    return 1 << (pos%bits_per_cell);
}

void bitarray_set(struct bitarray *ba, unsigned long pos)
{
    if (pos >= ba->len)
    {
        return;
    }
    ba->buffer[pos_to_cell(pos)] |= pos_to_bit(pos);
}

void bitarray_flip(struct bitarray *ba, unsigned long pos)
{
    if (pos >= ba->len)
    {
        return;
    }
    ba->buffer[pos_to_cell(pos)] ^= pos_to_bit(pos);
}

void bitarray_reset(struct bitarray *ba, unsigned long pos)
{
    if (pos >= ba->len)
    {
        return;
    }
    ba->buffer[pos_to_cell(pos)] &= ~pos_to_bit(pos);
}

int bitarray_get(struct bitarray *ba, unsigned long pos)
{
    return (pos >= ba->len) ? 0
        : !!(ba->buffer[pos_to_cell(pos)] & pos_to_bit(pos));
}
