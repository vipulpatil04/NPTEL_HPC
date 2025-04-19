//parallel code attempt to compute sum of array.
#include<omp.h>
#include<stdio.h>

#define arr_size 100000000
int a[arr_size];
int main(int *argc, char *argv)
{
    int i, tid, numt, sum=0;
    double t1,t2;

    for(i=0; i<arr_size; i++)
    {
        a[i] = 1;
    }
    omp_set_num_threads(4);
    t1 = omp_get_wtime();
    #pragma omp parallel default(shared) private(i,tid)
    //all variables are shared by default unless specified otherwise.
    //private(i,tid) variables i and tid will be separate for each thread(each thread gets it own copy)
    {
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        for(i=0; i< arr_size; i++)
        {
            sum += a[i];
        }

    }
        t2 = omp_get_wtime();
        printf("Sum of the array elements = %d. Time=%gsec\n", sum, t2-t1);
        return 0;
    }

    //Sum of the array elements = 211957714. Time=1.32086sec 
// Time increases due to cache coherency overhead.
// Sum is incorrect due to race condition — all threads update the shared 'sum' simultaneously.

// Issues:
// 1) All 4 threads process the entire array, leading to inefficient parallelization.
// 2) A race condition on the shared 'sum' variable results in incorrect output.
// Solution: Divide the array into four parts so each thread works on a separate segment.(in three.c)





