#include "bitarray.h"

// Cannot rely on standard libraries in OS code
#define NULL (void*)0
const long cell_size = sizeof(char);
const long bits_per_cell = cell_size*8;
const long all_bits_set = (1 << bits_per_cell) - 1;

struct bitarray* bitarray_init(struct bitarray *barray, void *buffer, unsigned long len)
{
    if (!barray || !buffer || !len)
    {
        return (struct bitarray*)NULL;
    }
    char *tmp = (char *)buffer;
    // It's bits_per_cell because there are bits_per_cell
    // bits in each element buffer
    for (unsigned long i = 0; i < len; i += bits_per_cell)
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

long bitarray_first_reset(struct bitarray *ba)
{
    if (!ba || !ba->buffer || !ba->len)
    {
        return -1L;
    }
    for (unsigned long i = 0; i < ba->len; i += bits_per_cell)
    {
        const unsigned char test = ba->buffer[pos_to_cell(i)];
        if (test != all_bits_set)
        {
            unsigned long j = 0;
            for (; j != bits_per_cell; ++j)
            {
                if (!(test & (1L << j)))
                {
                    // found 0 bit!
                    // check if we are in the array
                    if (i + j < ba->len)
                    {
                        // in the array
                        return i + j;
                    }
                    else
                    {
                        // out of bounds
                        return -1L;
                    }
                }
            }
        }
    }
    return -1L;
}

void bitarray_clear(struct bitarray *ba)
{
    // bitarray status
    if (!ba || !ba->buffer || !ba->len)
    {
        return;
    }
    char *tmp = (char *)ba->buffer;
    // It's bits_per_cell because there are bits_per_cell
    // bits in each element buffer
    for (unsigned long i = 0; i < ba->len; i += bits_per_cell)
    {
        *(tmp++) = 0;
    }
}
