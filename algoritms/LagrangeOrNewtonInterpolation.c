#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double *coefficients;
    int degree;
} Polynomial;

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

Polynomial get_lagrange_poly(const double *xi, const double *yi, int n) {
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

int main() {

    double xi[] = {-1.5, -0.75, 0, 0.75, 1.5};
    double yi[] = {-14.1014, -0.931596, 0, 0.931596, 14.1014};
    int n = sizeof(xi) / sizeof(xi[0]);

    Polynomial L = get_lagrange_poly(xi, yi, n);

    printf("Coefficients of the interpolation polynomial (from lowest to highest degree):\n");
    for (int i = 0; i <= L.degree; i++) {
        printf("x^%d: %f\n", i, L.coefficients[i]);
    }

    free_poly(&L);

    return 0;
}