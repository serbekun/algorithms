#include <stdio.h>
#include <math.h>

double f(double x) {
    return 6 * x - 6;
}

int main() {
    double left = 0.0;
    double right = 10.0;
    double mid;
    double eps = 0.000001; 
    while ((right - left) > eps) {
        mid = (left + right) / 2.0;

        if (f(mid) == 0.0) {
            break;
        } else if (f(mid) * f(left) < 0) {
            right = mid;
        } else {
            left = mid;
        }
    }

    printf("x ≈ %.6lf\n", mid);

    return 0;
}
