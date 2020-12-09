import math

def heron(a, b, c):
    if(a + b > c and a + c > b and b + c > a):
        p = (a + b + c)/2
        S = math.sqrt(p *(p - a)*(p - b)*(p - c))
        print("Pole trójkąta (", a, ",", b, ",", c, ") = ", S)
    else:
        raise ValueError("Warunek stworzenia trojkata nie jest spelniony!")

heron(2, 2, 2)