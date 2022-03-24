/**
 * A bit array is
 */
#ifndef BITARRAY
#define BITARRAY

struct bitarray
{
    char *const buffer;
    const unsigned long len;
};


/**
 * Assembla un bit array e ne restituisce la
 * struttura associata.
 */
struct bitarray bitarray_init(void *buffer, unsigned long len);
void bitarray_set(struct bitarray ba, unsigned long pos);
void bitarray_unset(struct bitarray ba, unsigned long pos);
int bitarray_get(struct bitarray ba, unsigned long pos);

#endif
