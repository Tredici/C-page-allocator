/**
 * A bit array is
 */
#ifndef BITARRAY
#define BITARRAY

struct bitarray
{
    char * buffer;
    /**
     * It is the number of bits in the buffer,
     * NOT the buffer length!
     */
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
/**
 * Return index of the first set bit.
 * Return -1 if all bits are set.
 */
long bitarray_first_reset(struct bitarray *ba);

/**
 * Set all bits to 0
 */
void bitarray_clear(struct bitarray *ba);

#endif
