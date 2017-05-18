#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *output = fopen("output.txt", "w");
    int i ;

    
    FILE *fp = fopen("Instrinics.txt", "r");

    double orig_sum_a = 0.0, orig_a;
    for (i = 0; i < 100; i++) {
        fscanf(fp, "%lf\n",&orig_a);
        orig_sum_a += orig_a;
    }
    fclose(fp);

    fp = fopen("Function.txt", "r");

    double orig_sum_b = 0.0, orig_b;
    for (i = 0; i < 100; i++) {
        fscanf(fp, "%lf\n",&orig_b);
        orig_sum_b += orig_b;
    }
    fclose(fp);

    fprintf(output, "%lf %lf\n",orig_sum_a / 100.0, orig_sum_b / 100.0);
    fclose(output);
    return 0;
}
