/**
 * A bit array is
 */
#ifndef BITARRAY
#define BITARRAY

struct bitarray
{
    char * buffer;
    unsigned long len;
};


/**
 * Assembla un bit array e ne restituisce la
 * struttura associata.
 */
struct bitarray* bitarray_init(struct bitarray *barray, void *buffer, unsigned long len);
void bitarray_set(struct bitarray *ba, unsigned long pos);
void bitarray_flip(struct bitarray *ba, unsigned long pos);
void bitarray_reset(struct bitarray *ba, unsigned long pos);
int bitarray_get(struct bitarray *ba, unsigned long pos);

#endif
