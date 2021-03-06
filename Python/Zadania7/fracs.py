import unittest

class Frac:
    """Klasa reprezentująca ułamek."""

    def __init__(self, x=0, y=1):
        try:
            if y == 0:
                raise ValueError;
        except ValueError:
            print("Mianownik nie może być zerem")
        else:
            nwd = Frac.gcd(x, y)
            self.x = x // nwd
            self.y = y // nwd

    def __str__(self):
        return "{}/{}".format(self.x, self.y)

    def __repr__(self):
        return "Frac({}, {})".format(self.x, self.y)

    # Python 2.7 i Python 3
    def __eq__(self, other):
        other = self.normalize(other)
        return (self.x * other.y) == (self.y * other.x)

    def __ne__(self, other):
        other = self.normalize(other)
        return (self.x * other.y) != (self.y * other.y)

    def __lt__(self, other):
        other = self.normalize(other)
        return (self.x * other.y) < (self.y * other.x)

    def __le__(self, other):
        other = self.normalize(other)
        return (self.x * other.y) <= (self.y * other.x)

    def __add__(self, other):
        other = self.normalize(other)
        return Frac(self.x * other.y + self.y * other.x, self.y * other.y)

    __radd__ = __add__

    def __sub__(self, other):
        other = self.normalize(other)
        return Frac(self.x * other.y - self.y * other.x, self.y * other.y)

    def __rsub__(self, other):
        other = self.normalize(other)
        return Frac(self.y * other - self.x, self.y)

    def __mul__(self, other):
        other = self.normalize(other)
        return Frac(self.x * other.x, self.y * other.y)

    __rmul__ = __mul__

    def __div__(self, other):
        other = self.normalize(other)
        return Frac(self.x * other.y, self.y * other.x)

    def __floordiv__(self, other):
        other = self.normalize(other)
        a = self.x * other.y
        b = other.x * self.y
        return Frac(a // b)

    def __truediv__(self, other):
        other = self.normalize(other)
        return float(self) / float(other)
    # operatory jednoargumentowe
    def __pos__(self):  # +frac = (+1)*frac
        return self

    def __neg__(self):  # -frac = (-1)*frac
        return Frac(-self.x, self.y)

    def __invert__(self):  # odwrotnosc: ~frac
        return Frac(self.y, self.x)

    def __float__(self):        # float(frac)
        return float(self.x/self.y)

    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def normalize(self, other):
        if isinstance(other, int):
                other = Frac(other)
        elif isinstance(other, float):
            a, b = other.as_integer_ratio()
            other = Frac(a, b)
        return other


class TestFractions(unittest.TestCase):

    def setUp(self):
        self.zero = [0, 1]

    def test_cmp(self):
        self.assertTrue(Frac(2, 1) == Frac(2, 1))
        self.assertFalse(Frac(2, 1) == Frac(3, 1))
        self.assertTrue(Frac(2, 1) != Frac(3, 1))
        self.assertTrue(Frac(2, 1) < Frac(3, 1))
        self.assertFalse(Frac(4, 1) < Frac(3, 1))
        self.assertTrue(Frac(2, 1) <= Frac(3, 1))
        self.assertFalse(Frac(4, 1) <= Frac(3, 1))
        self.assertTrue(Frac(4, 1) > Frac(3, 1))
        self.assertFalse(Frac(2, 1) > Frac(3, 1))
        self.assertTrue(Frac(4, 1) >= Frac(3, 1))
        self.assertFalse(Frac(2, 1) >= Frac(3, 1))

    def test_add_frac(self):
        self.assertEqual(Frac(1, 2) + Frac(1, 3), Frac(5, 6))
        self.assertEqual(Frac(-1, 2) + Frac(-3, 2), Frac(-2, 1))
        self.assertEqual(Frac(7, 4) + 3, Frac(19, 4))

    def test_sub_frac(self):
        self.assertEqual(Frac(7, 4) - Frac(3, 2), Frac(1, 4))
        self.assertEqual(Frac(7, 4) - 3, Frac(-5, 4))
        
    def test_mul_frac(self):
        self.assertEqual(Frac(5, 1) * Frac(1, 2), Frac(5, 2))

    def test_div_frac(self):
        self.assertEqual(Frac(50, 5) / Frac(-1, 2), -20./1.)

    def test_frac2float(self):
        self.assertEqual(Frac(0, 2).__float__(), 0)
        self.assertEqual(Frac(2, 4).__float__(), 0.5)
        self.assertEqual(Frac(-6, 3).__float__(), -2.0)

    def test_print(self):
        self.assertTrue(Frac(1, 2).__str__(), "1/2")
        self.assertTrue(Frac(1, 2).__repr__(), "Frac(1, 2)")

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