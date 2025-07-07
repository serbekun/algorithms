#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> poly_mult(const vector<double>& p, const vector<double>& q) {
    int size_p = p.size();
    int size_q = q.size();
    vector<double> res(size_p + size_q - 1, 0.0);
    
    for (int i = 0; i < size_p; i++) {
        for (int j = 0; j < size_q; j++) {
            res[i + j] += p[i] * q[j];
        }
    }
    return res;
}

vector<double> get_lagrange_poly(const vector<double>& xi, const vector<double>& yi) {
    int n = xi.size();
    vector<vector<double>> basis_polys(n);

    for (int pl = 0; pl < n; pl++) {
        vector<double> poly = {1.0};
        
        for (int i = 0; i < n; i++) {
            if (i == pl) continue;
            
            double denominator = xi[pl] - xi[i];
            vector<double> multiplier = {
                -xi[i] / denominator, 
                1.0 / denominator     
            };

            poly = poly_mult(poly, multiplier);
        }
        basis_polys[pl] = poly;
    }

    vector<double> L(n, 0.0);
    for (int pl = 0; pl < n; pl++) {
        for (int j = 0; j < n; j++) {
            if (j < basis_polys[pl].size()) {
                L[j] += yi[pl] * basis_polys[pl][j];
            }
        }
    }

    return L;
}

int main() {

    vector<double> xi = {-1.5, -0.75, 0, 0.75, 1.5};
    vector<double> yi = {-14.1014, -0.931596, 0, 0.931596, 14.1014};

    vector<double> L = get_lagrange_poly(xi, yi);

    cout << "Coefficients of the interpolation polynomial (from lowest to highest degree):\n";
    for (size_t i = 0; i < L.size(); i++) {
        cout << "x^" << i << ": " << L[i] << endl;
    }

    return 0;
}