#include <stdio.h>
#include <omp.h>

double f(double x)
{
    return x * x;
}

int main()
{
    int i, n, n_threads;

    printf("Enter number of trapezoids: ");
    scanf("%d", &n);

    double a, b;
    printf("Enter a and b: ");
    scanf("%lf %lf", &a, &b);

    printf("Enter number of threads: ");
    scanf("%d", &n_threads);

    double h, integral = 0.0;
    h = (b - a) / n;

    double thread_sum[n_threads];

    for (i = 0; i < n_threads; i++) {
        thread_sum[i] = 0.0;
    }

    omp_set_num_threads(n_threads);

    #pragma omp parallel for reduction(+:integral)
    for (i = 0; i < n; i++) {
        int tid = omp_get_thread_num();

        double x_i = a + i * h;
        double x_next = a + (i + 1) * h;

        double local_area = (h / 2.0) * (f(x_i) + f(x_next));

        integral += local_area;
        thread_sum[tid] += local_area;
    }

    printf("Approximate integral = %f\n", integral);

    return 0;
}
