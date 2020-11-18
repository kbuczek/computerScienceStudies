f1 = [-1, 2]                  # -1/2
f2 = [0, 1]                   # zero
f3 = [3, 1]                   # 3
f4 = [6, 2]                   # 3 (niejednoznaczność)
f5 = [0, 2]                   # zero (niejednoznaczność)

def gcd(a, b):
    while b:
        a, b = b, a%b
    return a

def skroc(frac):
    gcd_num = gcd(frac[0], frac[1])
    return [int(frac[0]/gcd_num), int(frac[1]/gcd_num)]

def add_frac(frac1, frac2):
    return skroc([frac1[0] * frac2[1] + frac2[0] * frac1[1], frac1[1] * frac2[1]])

def sub_frac(frac1, frac2):
    return skroc([frac1[0] * frac2[1] - frac2[0] * frac1[1], frac1[1] * frac2[1]])

def mul_frac(frac1, frac2):
    return skroc([frac1[0] * frac2[0], frac1[1] * frac2[1]])

def div_frac(frac1, frac2):
    return skroc([frac1[0] * frac2[1], frac1[1] * frac2[0]])

def is_positive(frac):
    if (frac[0] > 0 and frac[1] > 0) or (frac[0] < 0 and frac[1] < 0):
        return True
    else:
        return False

def is_zero(frac):
    if frac[0] == 0:
        return True
    else:
        return False

def cmp_frac(frac1, frac2):
    i = -1
    # frac1 = skroc(frac1)
    # frac2 = skroc(frac2)
    if frac1[0] == frac2[0]:
        i += 1;
    if frac1[1] == frac2[1]:
        i += 1;
    return i;

def frac2float(frac):
    return frac[0]/frac[1]