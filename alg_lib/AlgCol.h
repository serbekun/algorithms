#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point *mins;      
    Point *maxs;      
    size_t min_count; 
    size_t max_count; 
} ExtremaResult;

typedef struct {
    double *coefficients;
    int degree;
} Polynomial;

void SetArrayRandomValue(int *array, size_t array_size) 
{
    for (size_t i = 0; i < array_size; i++) 
    {
        *(array + i) = rand() % (100 -0 + 1) + 0;
    }
}

int GetArrayAvarage(int *array_collect_array_avarage,
    size_t size_array_collect_array_avarage) 
{
    int sum_array_collect_array_avarage = 0;
    int avarage_array_collect_array_avarage;

    for (int i = 0;i < size_array_collect_array_avarage;i++) 
    {
        sum_array_collect_array_avarage += *(array_collect_array_avarage + i);
    }

    avarage_array_collect_array_avarage = sum_array_collect_array_avarage / size_array_collect_array_avarage;

    return avarage_array_collect_array_avarage;
}

double BisectionMethod(double (*f)(double)) 
{
    double left = 0.0;
    double right = 10.0;
    double mid = 0.0;
    double eps = 0.000001;

    if (fabs(f(left)) < eps) {
        return left;
    }
    if (fabs(f(right)) < eps) {
        return right;
    }

    while ((right - left) > eps) {
        mid = (left + right) / 2.0;

        if (fabs(f(mid)) < eps) {
            break;
        } else if (f(mid) * f(left) < 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return mid;  // Added return statement
}  // Added closing brace

void cross_correlation(const double *x, int len_x, 
                      const double *y, int len_y, 
                      double *result) {
    int n = len_x + len_y - 1;
    
    for (int k = 0; k < n; k++) {
        double sum = 0.0;
        int shift = k - (len_y - 1); 
        
        for (int i = 0; i < len_x; i++) {
            int j = i - shift;

            if (j >= 0 && j < len_y) {
                sum += x[i] * y[j];
            }
        }
        result[k] = sum;
    }
}  // Function properly closed

/**
* Generates a periodic signal from the sum of sines.
*
* @param xx Array for storing x values (time or argument).
* @param fu Array for storing function (signal) values.
* @param size Size of xx and fu arrays.
* @param st Sampling step.
* @param per1 Period of the first sinusoid.
* @param per2 Period of the second sinusoid.
* @param per3 Period of the third sinusoid.
* @param per4 Period of the fourth sinusoid.
* @param a2 Amplitude of the third sinusoid (with minus).
* @param a4 Amplitude of the fourth sinusoid.
*/
void ComplexPeriodicSignalGenerator(
    double* xx,
    double* fu, 
    int size, 
    double step,
    double period1, 
    double period2, 
    double period3, 
    double period4, 
    double amplitude2, 
    double amplitude4
) 
{
    for (int i = 0; i < size; i++) {
        double x = i * step;
        xx[i] = x;
        fu[i] = sin(period1 * x) 
               + sin(period2 * x) 
               - amplitude2 * sin(period3 * x) 
               + amplitude4 * sin(period4 * x);
    }
}

int* ElementwiseAbsDifference(int a[], int b[], int c[], size_t arrays_size) 
{
    for (size_t i = 0; i < arrays_size; i++) 
    {
        if (a[i] > b[i])
        {
            c[i] = a[i] - b[i];
        }
        else 
        {
            c[i] = b[i] - a[i];
        }
    }
    return c;
}

/* Energy Calculate funks */

float divide(float x, float y) {
    if (fabs(y) < 1e-12) return NAN;
    return x / y;
}

float multiply(float x, float y) {
    return x * y;
}

float calculate_power(float voltage, float current) {
    return multiply(voltage, current);
}

float calculate_energy(float power, float time) {
    return multiply(power, time);
}

float calculate_current(float power, float voltage) {
    return divide(power, voltage);
}

float calculate_voltage(float power, float current) {
    return divide(power, current);
}

ExtremaResult FindExtrema(Point *points, size_t size) {
    ExtremaResult result;
    result.mins = malloc(size * sizeof(Point));
    result.maxs = malloc(size * sizeof(Point));
    result.min_count = 0;
    result.max_count = 0;

    for (size_t i = 1; i < size - 1; i++) {
        if (points[i - 1].y > points[i].y && points[i + 1].y > points[i].y) {
            result.mins[result.min_count++] = points[i];
        } else if (points[i - 1].y < points[i].y && points[i + 1].y < points[i].y) {
            result.maxs[result.max_count++] = points[i];
        }
    }

    return result;  // Removed premature free() calls
}

void DecomposerValue(float *array, int *table 
    , size_t array_size, size_t size_table) 
{
    int numbox;

    for (int i = 0; i < array_size; i++)
    {
        numbox = array[i] / 0.01;
        numbox--;
        
        if (numbox < 0)
            numbox = 0;

        if (numbox >= (int)size_table)
            numbox = (int)size_table - 1;

        table[numbox]++;
    }
}

Polynomial poly_mult(const Polynomial *p, const Polynomial *q) {
    int new_degree = p->degree + q->degree;
    Polynomial result;
    result.coefficients = (double *)calloc(new_degree + 1, sizeof(double));
    result.degree = new_degree;
    
    for (int i = 0; i <= p->degree; i++) {
        for (int j = 0; j <= q->degree; j++) {
            result.coefficients[i + j] += p->coefficients[i] * q->coefficients[j];
        }
    }
    return result;
}

void free_poly(Polynomial *p) {
    free(p->coefficients);
}

Polynomial get_lagrange_poly(const double *xi, const double *yi, int n) 
{
    Polynomial *basis_polys = (Polynomial *)malloc(n * sizeof(Polynomial));
    Polynomial L;
    L.coefficients = (double *)calloc(n, sizeof(double));
    L.degree = n - 1;

    for (int pl = 0; pl < n; pl++) {
        Polynomial poly;
        poly.coefficients = (double *)malloc(sizeof(double));
        poly.coefficients[0] = 1.0;
        poly.degree = 0;
        
        for (int i = 0; i < n; i++) {
            if (i == pl) continue;
            
            double denominator = xi[pl] - xi[i];
            Polynomial multiplier;
            multiplier.coefficients = (double *)malloc(2 * sizeof(double));
            multiplier.coefficients[0] = -xi[i] / denominator;
            multiplier.coefficients[1] = 1.0 / denominator;
            multiplier.degree = 1;

            Polynomial temp = poly_mult(&poly, &multiplier);
            free_poly(&poly);
            free_poly(&multiplier);
            poly = temp;
        }
        basis_polys[pl] = poly;
    }

    for (int pl = 0; pl < n; pl++) {
        for (int j = 0; j <= basis_polys[pl].degree; j++) {
            if (j <= L.degree) {
                L.coefficients[j] += yi[pl] * basis_polys[pl].coefficients[j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free_poly(&basis_polys[i]);
    }
    free(basis_polys);

    return L;
} 
