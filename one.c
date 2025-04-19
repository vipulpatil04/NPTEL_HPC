//sequential code to compute sum of array.
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define arr_size 100000000   //10 crores.
int a[arr_size];             
int main(int *argc, char *argv)
{

    int i, sum =0;
    double t1,t2;
    for(i=0; i<arr_size; i++)
    {
        a[i] = 1;
    }
    t1 = omp_get_wtime();// to note start time at this point
    for(i=0; i<arr_size;i++)
    {
        sum += a[i];
    }
    t2 = omp_get_wtime();// to note end time at this point
    printf("Sum of the array elements = %d. Time= %gsec\n", sum, t2-t1);
    return 0;
}

//to compile c code and link omp library to it, we use flag -fopenmp.

//result : Sum of the array elements = 100000000. Time= 0.236836