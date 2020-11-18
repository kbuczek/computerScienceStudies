import unittest

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
        i += 1
    if frac1[1] == frac2[1]:
        i += 1
    return i

def frac2float(frac):
    return frac[0]/frac[1]


class TestFractions(unittest.TestCase):

    def setUp(self):
        self.zero = [0, 1]

    def test_add_frac(self):
        self.assertEqual(add_frac([1, 2], [1, 3]), [5, 6])
        self.assertEqual(add_frac([-1, 2], [-3, 2]), [-2, 1])

    def test_sub_frac(self):
        self.assertEqual(sub_frac([7, 4], [3, 2]), [1, 4])
        
    def test_mul_frac(self):
        self.assertEqual(mul_frac([5, 1], [1, 2]), [5, 2])

    def test_div_frac(self):
        self.assertEqual(div_frac([50, 5], [-1, 2]), [-20, 1])

    def test_is_positive(self):
        self.assertTrue(is_positive([1, 2]))
        self.assertTrue(is_positive([-1, -2]))
        self.assertFalse(is_positive([0, 2]))
        self.assertFalse(is_positive([-5, 2]))
        self.assertFalse(is_positive([5, -2]))

    def test_is_zero(self):
        self.assertTrue(is_zero([0, 5]))
        self.assertTrue(is_zero([0, 1]))
        self.assertFalse(is_zero([3, 3]))
        self.assertFalse(is_zero([-1, 2]))

    def test_cmp_frac(self):
        self.assertEqual(cmp_frac([1, 2], [1, 2]), 1)
        self.assertEqual(cmp_frac([2, 5], [2, 7]), 0)
        self.assertEqual(cmp_frac([3, 9], [-2, 7]), -1)

    def test_frac2float(self):
        self.assertEqual(frac2float([0, 2]), 0)
        self.assertEqual(frac2float([2, 4]), 0.5)
        self.assertEqual(frac2float([-6, 3]), -2.0)


if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy