#include <wmmintrin.h>
#include <stdio.h>

/** 
    This is an example !
*/


int main()
{
    __m128i a;
    __m128i b;

    a[1] = 2;
    a[0] = -1284;
    b[1] = 25;
    b[0] = 65535;

    // _mm_clmulepi64_si128 only looks at the least significant bit of each

    int expect1 = a[1] * b[1];
    int expect2 = a[0] * b[0];
    int expect3 = a[0] * b[1];

    __m128i result1 = _mm_clmulepi64_si128( a, b, 0x11 );
    __m128i result2 = _mm_clmulepi64_si128( a, b, 0x00 );
    __m128i result3 = _mm_clmulepi64_si128( a, b, 0xF2 );

    printf("%I64d times %I64d without a carry bit: %I64d\n",
        a[1], b[1], result1[0]);
    printf("%I64d times %I64d without a carry bit: %I64d\n",
        a[0], b[0], result2[0]);
    printf("%I64d times %I64d without a carry bit: %I64d\n",
        a[0], b[1], result3[0]);
    return 0;
}