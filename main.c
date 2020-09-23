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

union uint128 {
    uint64_t qw[2];
    uint8_t b[16];
    uint32_t dw[4];
    uint16_t w[8];
} typedef uint128;

union uint512 {
    uint128 ow[4];
    uint64_t qw[8];
    uint16_t w[64];
    uint32_t dw[16];
    uint8_t b[64];
} typedef uint512;

//----------------------------------------------------------------------------------------------------------------
void X(const void *a, const void *b, void *c);

void S(unsigned char *a);

void L(unsigned char *a);

void P(unsigned char *a);

void KeyTable(unsigned char *K, int i);
//----------------------------------------------------------------------------------------------------------------

void X(const void *a, const void *b, void *c) {
    int i = 0;
    const uint512 *A = a, *B = b;
    uint512 *C = c;

    C->qw[0] = A->qw[0] ^ B->qw[0];
    C->qw[1] = A->qw[1] ^ B->qw[1];
    C->qw[2] = A->qw[2] ^ B->qw[2];
    C->qw[3] = A->qw[3] ^ B->qw[3];
    C->qw[4] = A->qw[4] ^ B->qw[4];
    C->qw[5] = A->qw[5] ^ B->qw[5];
    C->qw[6] = A->qw[6] ^ B->qw[6];
    C->qw[7] = A->qw[7] ^ B->qw[7];
}

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
    memcpy(a, tmp, 64);
}

void KeyTable(unsigned char *K, int i) {
    X(K, C[i], K);
    S(K);
    P(K);
    L(K);
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
