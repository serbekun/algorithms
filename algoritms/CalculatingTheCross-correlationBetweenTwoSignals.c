#include <stdio.h>
#include <stdlib.h>

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
}

int main() {

    double x[] = {1, 2, 3};
    double y[] = {1, 2};
    int len_x = sizeof(x) / sizeof(x[0]);
    int len_y = sizeof(y) / sizeof(y[0]);

    int result_len = len_x + len_y - 1;
    double *result = (double*)malloc(result_len * sizeof(double));

    cross_correlation(x, len_x, y, len_y, result);

    printf("cross_correlation:\n");
    for (int i = 0; i < result_len; i++) {
        printf("move %d: %.1f\n", i - (len_y - 1), result[i]);
    }
    
    free(result);
    return 0;
}