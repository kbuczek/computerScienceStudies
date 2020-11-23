import unittest

class Frac:
    """Klasa reprezentująca ułamek."""

    def __init__(self, x=0, y=1):
        self.x = x
        self.y = y

    def __str__(self):
        return "{}/{}".format(self.x, self.y)

    def __repr__(self):
        return "Frac({}, {})".format(self.x, self.y)

    # Python 2.7 i Python 3
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return self.x != other.x or self.y != other.y

    def __lt__(self, other):
        return float(self.x/self.y) < float(other.x/other.y)

    def __le__(self, other):
        return float(self.x/self.y) <= float(other.x/other.y)

    def __add__(self, other):
        return self.skroc(self.x * other.y + other.x * self.y, self.y * other.y)

    def __sub__(self, other):
        return self.skroc(self.x * other.y - other.x * self.y, self.y * other.y)

    def __mul__(self, other):
        return self.skroc(self.x * other.x, self.y * other.y)

    def __div__(self, other):
        return self.skroc(self.x * other.y, self.y * other.x)

    # operatory jednoargumentowe
    def __pos__(self):  # +frac = (+1)*frac
        return self

    def __neg__(self):  # -frac = (-1)*frac
        return Frac(-self.x, self.y)

    def __invert__(self):  # odwrotnosc: ~frac
        return Frac(self.y, self.x)

    def __float__(self):        # float(frac)
        return float(self.x/self.y)

    def gcd(self, a, b):
        while b:
            a, b = b, a%b
        return a

    def skroc(self, a, b):
        gcd_num = self.gcd(a, b)
        return int(a/gcd_num), int(b/gcd_num)

    def is_positive(self):
        if (self.x > 0 and self.y > 0) or (self.x < 0 and self.y < 0):
            return True
        else:
            return False

    def is_zero(self):
        if self.x == 0:
            return True
        else:
            return False

    def cmp_frac(self, other):
        frac = self.__sub__(other)
        frac2 = Frac(frac[0], frac[1])
        if frac2.is_zero():
            return 0
        elif frac2.is_positive():
            return 1
        else:
            return -1


class TestFractions(unittest.TestCase):

    def setUp(self):
        self.zero = [0, 1]

    def test_add_frac(self):
        self.assertEqual(Frac(1, 2).__add__(Frac(1, 3)), (5, 6))
        self.assertEqual(Frac(-1, 2).__add__(Frac(-3, 2)), (-2, 1))

    def test_sub_frac(self):
        self.assertEqual(Frac(7, 4).__sub__(Frac(3, 2)), (1, 4))
        
    def test_mul_frac(self):
        self.assertEqual(Frac(5, 1).__mul__(Frac(1, 2)), (5, 2))

    def test_div_frac(self):
        self.assertEqual(Frac(50, 5).__div__(Frac(-1, 2)), (-20, 1))

    def test_is_positive(self):
        self.assertTrue(Frac(1, 2).is_positive())
        self.assertTrue(Frac(-1, -2).is_positive())
        self.assertFalse(Frac(0, 2).is_positive())
        self.assertFalse(Frac(-5, 2).is_positive())
        self.assertFalse(Frac(5, -2).is_positive())
        

    def test_is_zero(self):
        self.assertTrue(Frac(0, 5).is_zero())
        self.assertTrue(Frac(0, 1).is_zero())
        self.assertFalse(Frac(3, 3).is_zero())
        self.assertFalse(Frac(-1, 2).is_zero())

    def test_cmp_frac(self):
        self.assertEqual(Frac(1, 2).cmp_frac(Frac(1, 4)), 1)
        self.assertEqual(Frac(2, 5).cmp_frac(Frac(2, 7)), 1)
        self.assertEqual(Frac(3, 9).cmp_frac(Frac(-2, 7)), 1)

    def test_frac2float(self):
        self.assertEqual(Frac(0, 2).__float__(), 0)
        self.assertEqual(Frac(2, 4).__float__(), 0.5)
        self.assertEqual(Frac(-6, 3).__float__(), -2.0)

    def test_print(self):
        self.assertTrue(Frac(1, 2).__str__(), "1/2")
        self.assertTrue(Frac(1, 2).__repr__(), "Frac(1, 2)")

    def test_cmp(self):
        self.assertTrue(Frac(2, 1) == Frac(2, 1))
        self.assertFalse(Frac(2, 1) == Frac(3, 1))
        self.assertTrue(Frac(2, 1) != Frac(3, 1))
        self.assertFalse(Frac(2, 1) != Frac(2, 1))
        self.assertTrue(Frac(2, 1) < Frac(3, 1))
        self.assertFalse(Frac(4, 1) < Frac(3, 1))
        self.assertTrue(Frac(2, 1) <= Frac(3, 1))
        self.assertFalse(Frac(4, 1) <= Frac(3, 1))
        self.assertTrue(Frac(4, 1) > Frac(3, 1))
        self.assertFalse(Frac(2, 1) > Frac(3, 1))
        self.assertTrue(Frac(4, 1) >= Frac(3, 1))
        self.assertFalse(Frac(2, 1) >= Frac(3, 1))

    def test_neg(self):
        self.assertEqual(Frac(4, 1).__neg__(), Frac(-4, 1))
        self.assertEqual(Frac(-4, 1).__neg__(), Frac(4, 1))

    def test_inv(self):
        self.assertEqual(Frac(1, 2).__invert__(), Frac(2, 1))

    def test_float(self):
        self.assertTrue(Frac(4, 1).__float__() == 4.0)
        self.assertTrue(Frac(4, -1).__float__() == -4.0)
        


if __name__ == '__main__':
    unittest.main()     # uruchamia wszystkie testy