import math

def solve2(a, b, c):
    if a == 0 and b == 0 and c == 0:
        print("x jest dowolny")
    else:
        if a != 0:
            delta = (b**2) - (4*a*c)
            if delta == 0:
                x0 = (-b)/(2*a)
                print("delta = 0, x0 = ", x1)
            elif delta > 0:
                x1 = (-b - math.sqrt(delta)) / (2*a)
                x2 = (-b + math.sqrt(delta)) / (2*a)
                print("delta > 0, x1 =", x1, ", x2 =", x2)
            elif delta < 0:
                print("delta < 0, brak pierwiastków")
        else:
            x = -c/b
            print("Wynik: ", x)

solve2(1, 7, 12)
