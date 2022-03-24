#include "bitarray.h"


struct bitarray bitarray_init(void *buffer, unsigned long len)
{
    char *tmp = (char *)buffer;
    int i;
    for (i = 0; i < len; i += 8)
    {
        *(tmp++) = 0;
    }
    return (struct bitarray){
        .len = len,
        .buffer = (char *)buffer
    };
}

static inline unsigned long pos_to_cell(unsigned long pos)
{
    return pos/8L;
}

static inline char pos_to_bit(unsigned long pos)
{
    return 1 << (pos%8L);
}

void bitarray_set(struct bitarray ba, unsigned long pos)
{
    if (pos >= ba.len)
    {
        return;
    }
    ba.buffer[pos_to_cell(pos)] |= pos_to_bit(pos);
}

void bitarray_unset(struct bitarray ba, unsigned long pos)
{
    if (pos >= ba.len)
    {
        return;
    }
    ba.buffer[pos_to_cell(pos)] &= ~pos_to_bit(pos);
}

int bitarray_get(struct bitarray ba, unsigned long pos)
{
    return (pos >= ba.len) ? 0
        : !!(ba.buffer[pos_to_cell(pos)] & pos_to_bit(pos));
}
