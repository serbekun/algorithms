#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    long num;
    long den;
} Fraction;

long gcd(long a, long b) {
    a = labs(a);
    b = labs(b);
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction frac_normalize(Fraction f) {
    if (f.den == 0) {
        f.num = 0;
        f.den = 1;
        return f;
    }
    
    if (f.den < 0) {
        f.num = -f.num;
        f.den = -f.den;
    }
    
    long g = gcd(labs(f.num), labs(f.den));
    if (g != 0) {
        f.num /= g;
        f.den /= g;
    }
    return f;
}

Fraction frac(long num, long den) {
    Fraction f = {num, den};
    return frac_normalize(f);
}

Fraction frac_add(Fraction a, Fraction b) {
    Fraction result = {
        a.num * b.den + b.num * a.den,
        a.den * b.den
    };
    return frac_normalize(result);
}

Fraction frac_sub(Fraction a, Fraction b) {
    Fraction result = {
        a.num * b.den - b.num * a.den,
        a.den * b.den
    };
    return frac_normalize(result);
}

Fraction frac_mul(Fraction a, Fraction b) {
    Fraction result = {
        a.num * b.num,
        a.den * b.den
    };
    return frac_normalize(result);
}

Fraction frac_div(Fraction a, Fraction b) {
    Fraction result = {
        a.num * b.den,
        a.den * b.num
    };
    return frac_normalize(result);
}

Fraction parse_number(const char *s) {
    if (s == NULL || *s == '\0') {
        return frac(0, 1);
    }
    
    if (s[0] == '/') {
        char *endptr;
        long den = strtol(s + 1, &endptr, 10);
        if (endptr == s + 1) {
            return frac(1, 1);
        }
        return frac(1, den);
    }
    
    char *slash = strchr(s, '/');
    if (slash != NULL) {
        char num_str[32];
        char den_str[32];
        strncpy(num_str, s, slash - s);
        num_str[slash - s] = '\0';
        strcpy(den_str, slash + 1);
        
        char *endptr;
        long num = strtol(num_str, &endptr, 10);
        if (endptr != num_str + strlen(num_str)) {
            double d = strtod(s, &endptr);
            return frac((long)(d * 1000000), 1000000);
        }
        
        long den = strtol(den_str, &endptr, 10);
        if (endptr != den_str + strlen(den_str)) {
            double d = strtod(s, &endptr);
            return frac((long)(d * 1000000), 1000000);
        }
        
        return frac(num, den);
    }
    
    char *endptr;
    double d = strtod(s, &endptr);
    if (endptr != s) {
        return frac((long)(d * 1000000), 1000000);
    }
    
    return frac(0, 1);
}

char *expand(const char *expr);

void parse_expression(const char *expr, Fraction *a, Fraction *b, Fraction *c) {
    char *expanded = expand(expr);
    char *str = expanded;
    
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    char *buf_ptr = buffer;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ' ') {
            *buf_ptr++ = str[i];
        }
    }
    *buf_ptr = '\0';
    str = buffer;
    
    char *terms[100];
    int signs[100];
    int term_count = 0;
    
    char *start = str;
    while (*str) {
        if (*str == '+' || *str == '-') {
            if (str != start) {
                *str = '\0';
                terms[term_count] = start;
                signs[term_count] = 1;
                term_count++;
            }
            start = str + 1;
        }
        str++;
    }
    if (*start) {
        terms[term_count] = start;
        signs[term_count] = 1;
        term_count++;
    }
    
    for (int i = 0; i < term_count; i++) {
        char *term = terms[i];
        int sign = 1;
        
        if (term[0] == '-') {
            sign = -1;
            term++;
        } else if (term[0] == '+') {
            term++;
        }
        
        char *ptr = term;
        while (*ptr && *ptr != 'x' && *ptr != 'y') {
            ptr++;
        }
        
        char var = *ptr;
        if (ptr != term) {
            *ptr = '\0';
        }
        
        Fraction coef = parse_number(term);
        if (var == 'x') {
            *a = frac_add(*a, frac_mul(frac(sign, 1), coef));
        } else if (var == 'y') {
            *b = frac_add(*b, frac_mul(frac(sign, 1), coef));
        } else {
            *c = frac_add(*c, frac_mul(frac(sign, 1), coef));
        }
    }
    
    free(buffer);
    free(expanded);
}

void parse_equation(const char *eq, Fraction *a, Fraction *b, Fraction *c) {
    const char *equal = strchr(eq, '=');
    if (equal == NULL) {
        parse_expression(eq, a, b, c);
        *c = frac_mul(*c, frac(-1, 1));
        return;
    }
    
    char *left = malloc(equal - eq + 1);
    strncpy(left, eq, equal - eq);
    left[equal - eq] = '\0';
    
    char *right = strdup(equal + 1);
    
    Fraction a_left = {0, 1}, b_left = {0, 1}, c_left = {0, 1};
    Fraction a_right = {0, 1}, b_right = {0, 1}, c_right = {0, 1};
    
    parse_expression(left, &a_left, &b_left, &c_left);
    parse_expression(right, &a_right, &b_right, &c_right);
    
    *a = frac_sub(a_left, a_right);
    *b = frac_sub(b_left, b_right);
    *c = frac_sub(c_right, c_left);
    
    free(left);
    free(right);
}

char *expand(const char *expr) {
    char *str = strdup(expr);
    size_t len = strlen(str);
    int changed;
    
    do {
        changed = 0;
        char *open = strchr(str, '(');
        if (open == NULL) {
            break;
        }
        
        char *close = strchr(open, ')');
        if (close == NULL) {
            break;
        }
        
        char *mult_start = open;
        while (mult_start > str && !strchr("+-", *(mult_start - 1)) {
            mult_start--;
        }
        
        char mult_str[32];
        size_t mult_len = open - mult_start;
        if (mult_len > 0) {
            strncpy(mult_str, mult_start, mult_len);
            mult_str[mult_len] = '\0';
        } else {
            strcpy(mult_str, "1");
        }
        
        Fraction multiplier = parse_number(mult_str);
        if (multiplier.den == 0) {
            multiplier = frac(1, 1);
        }
        
        char inner[256];
        size_t inner_len = close - open - 1;
        strncpy(inner, open + 1, inner_len);
        inner[inner_len] = '\0';
        
        char *terms[100];
        int signs[100];
        int term_count = 0;
        
        char *inner_ptr = inner;
        char *start = inner;
        while (*inner_ptr) {
            if (*inner_ptr == '+' || *inner_ptr == '-') {
                if (inner_ptr != start) {
                    *inner_ptr = '\0';
                    terms[term_count] = start;
                    signs[term_count] = 1;
                    term_count++;
                    start = inner_ptr + 1;
                }
            }
            inner_ptr++;
        }
        if (*start) {
            terms[term_count] = start;
            signs[term_count] = 1;
            term_count++;
        }
        
        char expanded[1024] = {0};
        for (int i = 0; i < term_count; i++) {
            char *term = terms[i];
            int sign = signs[i];
            
            if (term[0] == '-') {
                sign *= -1;
                term++;
            } else if (term[0] == '+') {
                term++;
            }
            
            char *var_ptr = term;
            while (*var_ptr && *var_ptr != 'x' && *var_ptr != 'y') {
                var_ptr++;
            }
            
            char var = *var_ptr;
            if (var_ptr != term) {
                *var_ptr = '\0';
            }
            
            Fraction coef = parse_number(term);
            coef = frac_mul(coef, multiplier);
            coef = frac_mul(coef, frac(sign, 1));
            
            char term_buf[64];
            if (var == 'x' || var == 'y') {
                if (coef.num == 1 && coef.den == 1) {
                    sprintf(term_buf, "+%c", var);
                } else if (coef.num == -1 && coef.den == 1) {
                    sprintf(term_buf, "-%c", var);
                } else {
                    if (coef.den == 1) {
                        sprintf(term_buf, "%+ld%c", coef.num, var);
                    } else {
                        sprintf(term_buf, "%+ld/%ld%c", coef.num, coef.den, var);
                    }
                }
            } else {
                if (coef.den == 1) {
                    sprintf(term_buf, "%+ld", coef.num);
                } else {
                    sprintf(term_buf, "%+ld/%ld", coef.num, coef.den);
                }
            }
            
            strcat(expanded, term_buf);
        }
        
        size_t prefix_len = mult_start - str;
        size_t suffix_len = strlen(close + 1);
        size_t new_len = prefix_len + strlen(expanded) + suffix_len;
        
        char *new_str = malloc(new_len + 1);
        strncpy(new_str, str, prefix_len);
        new_str[prefix_len] = '\0';
        strcat(new_str, expanded);
        strcat(new_str, close + 1);
        
        free(str);
        str = new_str;
        changed = 1;
    } while (changed);
    
    return str;
}

void solve(Fraction a1, Fraction b1, Fraction c1, Fraction a2, Fraction b2, Fraction c2) {
    Fraction D = frac_sub(frac_mul(a1, b2), frac_mul(a2, b1));
    if (D.num == 0) {
        printf("no answer for this Simultaneous Equations\n");
        return;
    }
    
    Fraction Dx = frac_sub(frac_mul(c1, b2), frac_mul(c2, b1));
    Fraction Dy = frac_sub(frac_mul(a1, c2), frac_mul(a2, c1));
    
    Fraction x = frac_div(Dx, D);
    Fraction y = frac_div(Dy, D);
    
    double x_val = (double)x.num / x.den;
    double y_val = (double)y.num / y.den;
    
    printf("x = %.6f\n", x_val);
    printf("y = %.6f\n", y_val);
}

int main() {
    char eq1[256], eq2[256];
    
    printf("input Simultaneous Equations: ");
    fgets(eq1, sizeof(eq1), stdin);
    eq1[strcspn(eq1, "\n")] = '\0';
    
    printf("input Simultaneous Equations: ");
    fgets(eq2, sizeof(eq2), stdin);
    eq2[strcspn(eq2, "\n")] = '\0';
    
    Fraction a1 = {0, 1}, b1 = {0, 1}, c1 = {0, 1};
    Fraction a2 = {0, 1}, b2 = {0, 1}, c2 = {0, 1};
    
    parse_equation(eq1, &a1, &b1, &c1);
    parse_equation(eq2, &a2, &b2, &c2);
    
    solve(a1, b1, c1, a2, b2, c2);
    
    return 0;
}
