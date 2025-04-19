
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10000000      // Number of data points
#define ALPHA 0.01   // Learning rate
#define ITERATIONS 10000  // Number of gradient descent steps

// Generate synthetic data: y = 2x + 3 + noise
void generate_data(double *X, double *Y) {
    for (int i = 0; i < N; i++) {
        X[i] = (double)i / N;  // X values from 0 to 1000
        Y[i] = 2 * X[i] + 3 ;
    }
}

// Perform Parallel Linear Regression using OpenMP
void parallel_linear_regression(double *X, double *Y, double *w, double *b, int thread_count) {
    for (int iter = 0; iter < ITERATIONS; iter++) {
        double dw = 0, db = 0;

        // Parallel computation of gradient sums
        #pragma omp parallel num_threads(thread_count)
        {
            double dw_private = 0, db_private = 0;

            #pragma omp for nowait
            for (int i = 0; i < N; i++) {
                double y_pred = (*w) * X[i] + (*b);
                double error = Y[i] - y_pred;
dw_private += (-2.0 * X[i] * error) / N;
db_private += (-2.0 * error) / N;
            }

            // Reduce thread-local results into global variables
            #pragma omp critical
            {
                dw += dw_private;
                db += db_private;
            }          
        }

        // Update parameters
        *w -= ALPHA * dw;
        *b -= ALPHA * db;
    }
}

int main() {

    // Allocate memory
    double *X = (double *)malloc(N * sizeof(double));
    double *Y = (double *)malloc(N * sizeof(double));

    // Generate dataset
    generate_data(X, Y);

    // Initialize weights
    double w_seq = 0.0, b_seq = 0.0;
    double w_par = 0.0, b_par = 0.0;

    // Measure execution time for sequential version
    clock_t start_seq = clock();
    parallel_linear_regression(X, Y, &w_seq, &b_seq, 1); // Using the same function, but single-threaded
    clock_t end_seq = clock();
    double time_seq = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

    // Measure execution time for parallel version
    double start_par = omp_get_wtime();
    parallel_linear_regression(X, Y, &w_par, &b_par, 4);
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    // Output results
    printf("\nSequential Model Results:\n");
    printf("w = %f, b = %f\n", w_seq, b_seq);
    printf("Execution Time: %f seconds\n", time_seq);

    printf("\nParallel Model Results:\n");
    printf("w = %f, b = %f\n", w_par, b_par);
    printf("Execution Time: %f seconds\n", time_par);

    printf("\nSpeedup: %f times\n", time_seq / time_par);

    // Free memory
    free(X);
    free(Y);

    return 0;
}
