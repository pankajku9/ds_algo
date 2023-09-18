#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <strings.h>

//#define CHAR_BIT 8

bool check_neg(int num)
{
    return num < 0; 
    // The far left bit is 1 when the value is negative and 0 otherwise
    // return (num >> (sizeof(int) * CHAR_BIT -1)) == 1;
}

void count_bit_set(int v)
{
    //unsigned int v; // count the number of bits set in v
    unsigned int c; // c accumulates the total bits set in v
    while(v) {
        printf("%x ffs:%d clz:%d ctz:%d popcnt:%d parity:%d\n", v, __builtin_ffs(v), __builtin_clz(v), __builtin_ctz(v), __builtin_popcount(v), __builtin_parity(v));
        v &= v - 1; // clear the least significant bit set
        c++;
    }

}

#define set_bit(x, n)  (x | (1 << n))
#define clear_bit(x, n)  (x & ~(1 << n))


int main()
{
    assert(check_neg(-5) == true);
    count_bit_set(1023);
}































