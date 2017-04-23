#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wmmintrin.h>
#include <assert.h>

static int64_t cl_mul(int64_t a, int64_t b)
{
    int64_t r = 0;
    while (b != 0)
    {
        if ((a & 1) != 0)
            r ^= b;      // carryless addition is xor
        a >>= 1;
        b <<= 1;
    }
    return r;
}


static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}


int main(){
    srand(time(NULL));
    int64_t *temp = NULL;
    int64_t random_number[2];
    int64_t *src = (int64_t *) malloc(sizeof(int64_t) * 2); //128-bit
    int64_t *dst1 = (int64_t *) malloc(sizeof(int64_t) * 2); //128-bit
    int64_t *dst2 = (int64_t *) malloc(sizeof(int64_t) * 2); //128-bit
    int64_t *dst3 = (int64_t *) malloc(sizeof(int64_t) * 2); //128-bit
    int64_t *dst4 = (int64_t *) malloc(sizeof(int64_t) * 2); //128-bit

    for (int i = 0; i < 2; i++)
        random_number[i] = ( rand() % 922337203685477580 ) + 1;

    for (int i = 0; i < 2; i++)
        src[i] = random_number[i];



    __m128i I0 = _mm_loadu_si128((__m128i *)(src));

    __m128i result1 = _mm_clmulepi64_si128( I0, I0, 0x00 ); // [63:0] [63:0]
    __m128i result3 = _mm_clmulepi64_si128( I0, I0, 0xF2 ); // [63:0] [127:64]
    __m128i result2 = _mm_clmulepi64_si128( I0, I0, 0x01 ); // [127:64] [63:0]
    __m128i result4 = _mm_clmulepi64_si128( I0, I0, 0xFF ); // [127:64] [127:64]

    _mm_storeu_si128((__m128i *)(dst1), result1);
    _mm_storeu_si128((__m128i *)(dst2), result2);
    _mm_storeu_si128((__m128i *)(dst3), result3);
    _mm_storeu_si128((__m128i *)(dst4), result4);



        printf("%lld\n", dst1[0]);
        printf("%lld\n", dst2[0]);
        printf("%lld\n", dst3[0]);
        printf("%lld\n", dst4[0]);

        assert( cl_mul(random_number[0],random_number[0]) == dst1[0]);
        assert( cl_mul(random_number[1],random_number[0]) == dst2[0]);
        assert( cl_mul(random_number[0],random_number[1]) == dst3[0]);
        assert( cl_mul(random_number[1],random_number[1]) == dst4[0]);

}
