#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <errno.h>

/**
 * Display data bit by bit.
 */
void print_bits(unsigned char* start_byte, size_t n_bytes, char delimiter);

/* ================================================================ */

/**
 * Decode the sieve. The sieve is an array that doesn't make sense by itself, or does it? Such a sieve starts counting from 2, omitting the first two numbers, which are neither prime nor composite.
 */
void print_primes(unsigned char* sieve, size_t limit);

/* ================================================================ */

int main(int argc, char** argv) {

    unsigned char* sieve;
    size_t limit;
    size_t size;

    if (argc > 1) {

        limit = strtol(argv[1], NULL, 10);
        size = sizeof(unsigned char) * ceil(limit / (double) CHAR_BIT);
    }
    else {
        return EXIT_FAILURE;
    }

    if ((sieve = malloc(size)) == NULL) {

        printf("error: %s\n", strerror(errno));

        return EXIT_FAILURE;
    }

    memset(sieve, 0, size);

    for (size_t i = 2; i < limit; i++) {

        if (((*(sieve + i / CHAR_BIT) >> i % CHAR_BIT) & 0x01) == 0) {

            for (size_t j = 2 * i; j < limit; j+= i) {
                *(sieve + j / CHAR_BIT) |= 0x01 << (j % CHAR_BIT);
            }
        }
    }

    print_primes(sieve, limit);

    free(sieve);

    return EXIT_SUCCESS;
}

/* ================================================================ */

void print_primes(unsigned char* sieve, size_t limit) {

    size_t i = 0;

    for (i = 2; i < limit; i++) {

        if (!((*(sieve + i / CHAR_BIT) >> i % CHAR_BIT) & 0x01)) {
            printf("%ld\n", i);
        }
    }

    return ;
}

/* ================================================================ */

void print_bits(unsigned char* start_byte, size_t n_bytes, char delimiter) {

    size_t i = 0;

    for (i = 0; i < n_bytes * CHAR_BIT; i++) {
        printf("%d", (*(start_byte + i / CHAR_BIT) >> i % CHAR_BIT) & 0x01);

        if ((i + 1) % CHAR_BIT == 0) {
            printf("%c", delimiter);
        } 
    }

    return ;
}
