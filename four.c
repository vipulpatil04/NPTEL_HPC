//Introduced psum private variable and pragma omp critical.
#include<omp.h>
#include<stdio.h>

#define arr_size 100000000
int a[arr_size];
int main(int argc, char *argv)
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
    {
        int from, to;
        int psum=0;//introducing private variable for each thread
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();

        from = (arr_size / numt ) * tid;
        to = (arr_size / numt ) * (tid + 1) - 1;
        if(tid == numt-1)
          to = arr_size - 1;
        
          printf("Hello from %d of %d, my range is from=%d to=%d\n",tid, numt, from, to);
          for(i = from; i<= to;i++)
          {
            psum += a[i];
          }
          #pragma omp critical
          sum += psum;

    }
        t2 = omp_get_wtime();
        printf("Sum of the array elements = %d. Time=%g\n", sum, t2-t1);
        return 0;
    }

    // Result :
// Sum of the array elements = 100000000. Time=0.141926
// Explanation:
// 1) Introduced a private variable `psum` for each thread to store partial sum, eliminating race conditions on 'sum'.
// 2) Used `#pragma omp critical` to safely update the shared 'sum' variable after each thread finishes.
// Alternative: Instead of using `#pragma omp critical`, we could use a reduction clause, which is more efficient for this type of operation.
// Shortest way:  `#pragma omp parallel for reduction(+:sum)`