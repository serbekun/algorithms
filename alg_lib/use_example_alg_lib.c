#include "AlgCol.h"
#include <stdio.h>

int main() {

    srand(time(NULL));

    int arr[10];
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    SetArrayRandomValue(arr, arr_size);
    printf("Array: ");
    for (size_t i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nAverage: %d\n\n", GetArrayAvarage(arr, arr_size));


    double root = BisectionMethod(sin);
    printf("Root of sin(x) found at: %f\n\n", root);

    double x[] = {1, 2, 3};
    double y[] = {1, 1, 1};
    double result[5];
    cross_correlation(x, 3, y, 3, result);
    printf("Cross-correlation: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", result[i]);
    }
    printf("\n\n");

    double xx[100], fu[100];
    ComplexPeriodicSignalGenerator(xx, fu, 100, 0.1, 1.0, 2.0, 3.0, 4.0, 0.5, 0.25);
    printf("Signal at x=1.0: %f\n\n", fu[10]);

    int a[] = {1, 3, 5};
    int b[] = {4, 2, 5};
    int c[3];
    ElementwiseAbsDifference(a, b, c, 3);
    printf("Elementwise differences: ");
    for (size_t i = 0; i < 3; i++) {
        printf("%d ", c[i]);
    }
    printf("\n\n");

    float power = calculate_power(10.0f, 2.0f);
    printf("Power: %.2f W\n", power);
    printf("Energy for 5 hours: %.2f J\n", calculate_energy(power, 5*3600));
    printf("\n");

    Point points[] = {{0,0}, {1,1}, {2,0}, {3,1}, {4,0}};
    ExtremaResult extrema = FindExtrema(points, 5);
    printf("Found %zu minima and %zu maxima\n", extrema.min_count, extrema.max_count);
    free(extrema.mins);
    free(extrema.maxs);
    printf("\n");

    float values[] = {0.005, 0.015, 0.025, 0.035};
    int table[10] = {0};
    DecomposerValue(values, table, 4, 10);
    printf("Distribution table:\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%.2f-%.2f: %d\n", i*0.01, (i+1)*0.01, table[i]);
    }
    printf("\n");

    Polynomial p = {.coefficients = (double[]){1, 2}, .degree = 1}; // 1 + 2x
    Polynomial q = {.coefficients = (double[]){3, 4}, .degree = 1}; // 3 + 4x
    Polynomial product = poly_mult(&p, &q); // (1+2x)(3+4x) = 3 + 10x + 8x²
    printf("Polynomial product: ");
    for (int i = 0; i <= product.degree; i++) {
        printf("%.1fx^%d ", product.coefficients[i], i);
    }
    printf("\n\n");

    double xi[] = {0, 1, 2};
    double yi[] = {0, 1, 4};
    Polynomial L = get_lagrange_poly(xi, yi, 3);
    printf("Lagrange polynomial: ");
    for (int i = 0; i <= L.degree; i++) {
        printf("%.1fx^%d ", L.coefficients[i], i);
    }
    free_poly(&L);
    printf("\n\n");

    double complex fft_input[] = {1, -1, 1, -1};
    FourierTransformFFT(fft_input, 4);
    printf("FFT result: ");
    for (int i = 0; i < 4; i++) {
        printf("%.1f%+.1fi ", creal(fft_input[i]), cimag(fft_input[i]));
    }
    printf("\n");

    double complex dft_input[] = {1, -1, 1, -1};
    double complex dft_output[4];
    FourierTransformDFT(dft_input, dft_output, 4);
    printf("DFT result: ");
    for (int i = 0; i < 4; i++) {
        printf("%.1f%+.1fi ", creal(dft_output[i]), cimag(dft_output[i]));
    }
    printf("\n");

    return 0;
}