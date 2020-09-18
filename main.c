#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "stribog_data.h"

#define BLOCK_SIZE      64
#define BLOCK_BIT_SIZE  (BLOCK_SIZE * 8)

#define OUTPUT_SIZE_512 64
#define OUTPUT_SIZE_256 32

#define HASH256         0
#define HASH512         1


void S(unsigned char *a) {
    int i = 0;
    for (i; i < 64; ++i) {
        a[i] = pi[a[i]];
    }
}

void L(unsigned char *a) {
    unsigned long long v = 0;
    int i = 0, j = 0, k = 0;

    for (i = 0; i < 8; i++) {
        v = 0;
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 8; j++) {
                if ((a[i * 8 + k] & (1 << (7 - j))) != 0)
                    v ^= A[k * 8 + j];
            }
        }
        for (k = 0; k < 8; k++) {
            a[i * 8 + k] = (v & ((unsigned long long) 0xFF << (7 - k) * 8)) >> (7 - k) * 8;
        }
    }
}

void P(unsigned char *a) {
    int i = 0;
    unsigned char tmp[64] = {};

    for (i = 0; i < 64; i++) {
        tmp[i] = a[Tau[i]];
    }
    memcpy(a,tmp,64);
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
