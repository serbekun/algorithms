import re
from fractions import Fraction

def parse_number(s):
    if not s:
        return Fraction(0)
    if s.startswith('/'):
        return Fraction(1, int(s[1:]))
    try:
        if '/' in s:
            numerator, denominator = s.split('/')
            return Fraction(int(numerator), int(denominator))
        return Fraction(s)
    except:
        return Fraction(float(s))

def expand(expr):
    def replace(m):
        multiplier = m.group(1)
        inner = m.group(2)
        if multiplier in ["", "+", None]:
            multiplier = Fraction(1)
        elif multiplier == "-":
            multiplier = Fraction(-1)
        else:
            multiplier = parse_number(multiplier)

        expanded = ""
        inner = re.sub(r'(?<=.)(-)', r'+-', inner)
        terms = inner.split("+")
        for term in terms:
            if term.strip() == "":
                continue
            match = re.fullmatch(r'([+-]?[\d./]*)([xy]?)', term.strip())
            if match:
                coef, var = match.groups()
                if coef in ["", "+"]:
                    coef = "1"
                elif coef == "-":
                    coef = "-1"
                result = multiplier * parse_number(coef)
                if var:
                    expanded += f"{'+' if result >= 0 else ''}{result}{var}"
                else:
                    expanded += f"{'+' if result >= 0 else ''}{result}"
        return expanded

    prev = ""
    while expr != prev:
        prev = expr
        expr = re.sub(r'([+-]?[\d./]*)\(([^()]+)\)', lambda m: replace(m), expr)
    return expr

def parse_expression(expr):
    expr = expand(expr.replace(" ", ""))
    a = b = c = Fraction(0)
    tokens = re.findall(r'([+-]?[\d./]*[xy]?)', expr)
    sign = 1  # текущий знак
    
    for token in tokens:
        if not token:
            continue

        if token.startswith('+'):
            sign = 1
            token = token[1:]
        elif token.startswith('-'):
            sign = -1
            token = token[1:]
        
        if '/' in token and ('x' in token or 'y' in token):
            parts = token.split('/')
            numerator = parts[0] or '1'
            denominator_part = parts[1]
            
            # Отделяем знаменатель от переменной
            var_match = re.search(r'([xy])', denominator_part)
            if var_match:
                var = var_match.group(1)
                denominator = denominator_part.replace(var, '') or '1'
                coef = sign * Fraction(int(numerator), int(denominator))
                if var == 'x':
                    a += coef
                else:
                    b += coef
            else:
                c += sign * Fraction(int(numerator), int(denominator_part))

        elif 'x' in token or 'y' in token:
            var_match = re.search(r'([xy])', token)
            var = var_match.group(1)
            coef_str = token.replace(var, '') or '1'
            coef = sign * parse_number(coef_str)
            if var == 'x':
                a += coef
            else:
                b += coef
        else:
            c += sign * parse_number(token or '0')

    return a, b, c

def parse_equation(eq):
    left, right = eq.replace(" ", "").split("=")
    a1, b1, c1 = parse_expression(left)
    a2, b2, c2 = parse_expression(right)
    return a1 - a2, b1 - b2, c2 - c1

def solve(eq1, eq2):
    a1, b1, c1 = parse_equation(eq1)
    a2, b2, c2 = parse_equation(eq2)

    D = a1 * b2 - a2 * b1
    if D == 0:
        print("no answer for this Simultaneous Equations")
        return

    Dx = c1 * b2 - c2 * b1
    Dy = a1 * c2 - a2 * c1

    x = Dx / D
    y = Dy / D

    print(f"x = {float(x)}")
    print(f"y = {float(y)}")

eq1 = input("input Simultaneous Equations: ")
eq2 = input("input Simultaneous Equations: ")

solve(eq1, eq2)