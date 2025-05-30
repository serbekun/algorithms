import re
from fractions import Fraction

def parse_number(s):
    try:
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

    for match in re.finditer(r'([+-]?[\d./]*)([xy]?)', expr):
        num, var = match.groups()
        if num == "" and var != "":
            num = "1"
        elif num == "+":
            num = "1"
        elif num == "-":
            num = "-1"
        if num == "" and var == "":
            continue
        value = parse_number(num)
        if var == "x":
            a += value
        elif var == "y":
            b += value
        else:
            c += value
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
