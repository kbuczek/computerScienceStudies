from random import random
from math import sqrt

def calc_pi(n=1000):
    wnetrze = 0
    for i in range(0, n):
        x = random()
        y = random()
        if x*x + y*y <= 1:
            wnetrze += 1
    pi = 4 * wnetrze / n     # p_kw=4*r*r; p_ko=pi*r*r; p_ko/p_kw = pi/4
    print(pi)

calc_pi()
