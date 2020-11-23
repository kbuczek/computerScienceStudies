import math

class Point:
    """Klasa reprezentująca punkty na płaszczyźnie."""

    def __init__(self, x, y):  # konstuktor
        self.x = x
        self.y = y

    def __str__(self):
        return "({}, {})".format(self.x, self.y)

    def __repr__(self):
        return "Point({}, {})".format(self.x, self.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return not self == other

    # Punkty jako wektory 2D.
    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        return Point(self.x * other.x, self.y * other.y)

    def cross(self, other):         # v1 x v2, iloczyn wektorowy 2D
        return self.x * other.y - self.y * other.x

    def length(self):
        return math.sqrt((self.x)**2 + (self.y)**2)

print()

# Kod testujący moduł.
import unittest

class TestTime(unittest.TestCase):

    def setUp(self): pass

    def test_print(self):       # test str() i repr()
        self.assertTrue(Point(3, 6).__str__() == '(3, 6)')
        self.assertTrue(Point(-1, 2).__repr__() == 'Point(-1, 2)')

    def test_cmp(self):
        self.assertTrue(Point(2, 1) == Point(2, 1))
        self.assertFalse(Point(2, 1) == Point(7, 4))
        self.assertTrue(Point(2, 1) != Point(3, 1))
        self.assertFalse(Point(4, 5) != Point(4, 5))

    def test_add(self):
        self.assertTrue(Point(2, 1) + Point(3, 1) == Point(5, 2))

    def test_sub(self):
        self.assertTrue(Point(2, 1) - Point(3, 1) == Point(-1, 0))

    def test_mul(self):
        self.assertTrue(Point(2, 1) * Point(3, 1) == Point(6, 1))

    def test_cross(self):
        self.assertTrue(Point(2, 1).cross(Point(3, 1)) == -1)
        
    def test_length(self):
        self.assertTrue(Point(2, 1).length() == math.sqrt(5))

    def tearDown(self): pass

if __name__ == "__main__":
    unittest.main()     # wszystkie testy