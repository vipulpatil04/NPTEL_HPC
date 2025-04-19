//Use OPENMP for to divide the loop among thread.

#include <omp.h>
#include <stdio.h>

#define arr_size 100000000
int a[arr_size];

int main(int argc, char *argv)
{
    int i, sum = 0;
    double t1,t2;
    for(i=0; i<arr_size; i++)
    {
        a[i] = 1;
    }
    omp_set_num_threads(4);
    t1 = omp_get_wtime();
    #pragma omp parallel
    {
        int psum = 0; // private sum per thread

        #pragma omp for // OpenMP automatically splits the following loop across threads.
        for (i = 0; i < arr_size; i++) {
            psum += a[i];
        }

        // Safely add private sum to global sum
        #pragma omp critical
        sum += psum;
    }
        t2=omp_get_wtime();
        printf("Sum ofthe array elements = %d. Time= %gsec\n", sum, t2-t1);
        return 0;

}
//Result : Sum ofthe array elements = 100000000. Time= 0.138059sec

//This code can be shortened using: 
// #pragma omp parallel for reduction(+:sum)
// It eliminates the need for manual private sums and critical section.