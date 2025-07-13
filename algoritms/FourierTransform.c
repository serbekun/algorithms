#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define M_PI 3.14159265358979323846

void FourierTransformFFT(double complex *x, int n) {
    if (n <= 1) return;

    double complex *even = malloc(n/2 * sizeof(double complex));
    double complex *odd = malloc(n/2 * sizeof(double complex));
    for (int i = 0; i < n/2; i++) {
        even[i] = x[2*i];
        odd[i] = x[2*i + 1];
    }

    FourierTransformFFT(even, n/2);
    FourierTransformFFT(odd, n/2);

    for (int k = 0; k < n/2; k++) {
        double complex t = cexp(-2 * I * M_PI * k / n) * odd[k];
        x[k]     = even[k] + t;
        x[k+n/2] = even[k] - t;
    }

    free(even);
    free(odd);
}

void FourierTransformDFT(double complex *x, double complex *X, int n) {
    for (int k = 0; k < n; k++) {
        X[k] = 0;
        for (int i = 0; i < n; i++)
            X[k] += x[i] * cexp(-2 * I * M_PI * k * i / n);
    }
}

int main() {
    int n = 8;
    double complex x[] = {1, 1, 1, 1, 0, 0, 0, 0}; // example signal

    FourierTransformFFT(x, n);

    for (int i = 0; i < n; i++) 
        printf("X[%d] = %.2f + %.2fi\n", i, creal(x[i]), cimag(x[i]));

    return 0;

    int n2 = 4;
    double complex x2[] = {1, 1, 1, 1};
    double complex X[n];

    FourierTransformDFT(x2, X, n2);

    for (int k = 0; k < n; k++) {
        printf("X[%d] = %.2f + %.2fi\n", k, creal(X[k]), cimag(X[k]));
    }

}