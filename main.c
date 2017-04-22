#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <wmmintrin.h>

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

    int *temp = NULL;
    int *src1 = (int *) malloc(sizeof(int) * 4); //128-bit
    int *src2 = (int *) malloc(sizeof(int) * 4); //128-bit
    int *dst1 = (int *) malloc(sizeof(int) * 4); //128-bit
    int *dst2 = (int *) malloc(sizeof(int) * 4); //128-bit

    for (int i = 0; i < 4; i++) {
        src1[i] = i; // 0 1 2 3
        src2[i] = i; // 0 1 2 3
    } 
        // temp = src1 + ( i * sizeof(int) );
        // *temp = i;
        // Why doesn't it work?

    // for (int i = 0; i < 4; i++) {
        // int value = *(src1 + ( i * sizeof(int)));
        // printf("%d ",value);
    // }

    __m128i I0 = _mm_loadu_si128((__m128i *)(src1));
    __m128i I1 = _mm_loadu_si128((__m128i *)(src2));
    // // __m128i T2 = _mm_clmulepi64()
    _mm_storeu_si128((__m128i *)(dst1), I0);
    _mm_storeu_si128((__m128i *)(dst2), I1);

    for (int i = 0; i < 4; i++)
        printf("%d and ", dst1[i]);

}
