//Using reduction to eliminate the use of private sum.
//Using #pragma omp for to eleimate the manual dividing of sum.
#include<omp.h>
#include <stdio.h>

#define arr_size 100000000
int a[arr_size];

int main(int argc, char *argv[])
{
    int i,sum=0;
    double t1,t2;
    for(i=0;i<arr_size;i++)
    {
        a[i] = 1;
    }
    t1=omp_get_wtime();
    #pragma omp parallel for default(shared) reduction(+:sum) //Parallelize the loop with shared variables and safely sum results using reduction on 'sum'.
        for(i=0;i<arr_size;i++)
        {
            sum +=a[i];
        }
    t2=omp_get_wtime();
    printf("Sum of the array elements = %d. Time = %gsec\n",sum, t2-t1);
    return 0;

}
//Result : Sum of the array elements = 100000000. Time = 0.218856sec