from points import Point

class Rectangle:
    """Klasa reprezentująca prostokąty na płaszczyźnie."""

    def __init__(self, x1, y1, x2, y2):
        try:
            if x1 >= x2 or y1 >= y2:
                raise ValueError
        except ValueError:
            print("x1 >= x2 or y1 >= y2")
        else:
            self.pt1 = Point(x1, y1)
            self.pt2 = Point(x2, y2)

    def __str__(self):        # "[(x1, y1), (x2, y2)]"
        return "[" + self.pt1.__str__() + ", " + self.pt2.__str__() + "]"

    def __repr__(self):       # "Rectangle(x1, y1, x2, y2)"
        return Rectangle.__name__ + "(" + str(self.pt1.x) + ", " + str(self.pt1.y) + ", " + str(self.pt2.x) + ", " + str(self.pt2.y) + ")"

    def __eq__(self, other):   # obsługa rect1 == rect2
        if(self.pt1 == other.pt1 and self.pt2 == other.pt2):
            return True
        else:
            return False

    def __ne__(self, other):        # obsługa rect1 != rect2
        return not self == other

    def center(self):           # zwraca środek prostokąta
        return Point(((self.pt2.x - self.pt1.x)/2), ((self.pt2.y - self.pt1.y)/2))

    def area(self):            # pole powierzchni
        return ((self.pt2.x - self.pt1.x) * (self.pt2.y - self.pt1.y))

    def move(self, x, y):       # przesunięcie o (x, y)
        return Rectangle(self.pt1.x + x, self.pt1.y + y, self.pt2.x + x, self.pt2.y + y)

    def intersection(self, other): # część wspólna prostokątów
        return Rectangle(max(self.pt1.x, other.pt1.x), max(self.pt1.y, other.pt1.y), min(self.pt2.x, other.pt2.x), min(self.pt2.y, other.pt2.y))

    def cover(self, other):     # prostąkąt nakrywający oba
        return Rectangle(min(self.pt1.x, other.pt1.x), min(self.pt1.y, other.pt1.y), max(self.pt2.x, other.pt2.x), max(self.pt2.y, other.pt2.y))

    def make4(self):           # zwraca krotkę czterech mniejszych
        srodek = self.center()
        lewyDolny = Rectangle(self.pt1.x, self.pt1.y, srodek.x, srodek.y)
        prawyDolny = Rectangle(srodek.x, self.pt1.y, self.pt2.x, srodek.y)
        prawyGorny = Rectangle(srodek.x, srodek.y, self.pt2.x, self.pt2.y)
        lewyGorny = Rectangle(self.pt1.x, srodek.y, srodek.x, self.pt2.y)
        return (lewyDolny, prawyDolny, prawyGorny, lewyGorny)


# Kod testujący moduł.
import unittest

class TestRectangle(unittest.TestCase):

    def setUp(self): pass

    def test_print(self):       # test str() i repr()
        self.assertTrue(Rectangle(3, 6, 7, 8).__str__() == '[(3, 6), (7, 8)]')
        self.assertTrue(Rectangle(3, 6, 7, 8).__repr__() == 'Rectangle(3, 6, 7, 8)')

    def test_cmp(self):
        self.assertTrue(Rectangle(2, 1, 5, 4) == Rectangle(2, 1, 5, 4))
        self.assertFalse(Rectangle(2, 1, 7, 4) == Rectangle(7, 3, 9, 4))
        self.assertTrue(Rectangle(2, 1, 5, 4) != Rectangle(1, 1, 5, 4))
        self.assertFalse(Rectangle(2, 1, 5, 4) != Rectangle(2, 1, 5, 4))

    def test_center(self):
        self.assertTrue(Rectangle(0, 0, 2, 2).center() == Point(1, 1))
        self.assertFalse(Rectangle(0, 0, 2, 2).center() == Point(2, 1))

    def test_area(self):
        self.assertTrue(Rectangle(0, 0, 2, 2).area() == 4)
        self.assertFalse(Rectangle(0, 0, 2, 2).area() == 2)

    def test_move(self):
        self.assertTrue(Rectangle(0, 0, 2, 2).move(1, 1) == Rectangle(1, 1, 3, 3))
        self.assertFalse(Rectangle(0, 0, 2, 2).move(-1, -1) == Rectangle(1, 1, 3, 3))

    def test_intersection(self):
        self.assertTrue(Rectangle(1, 1, 3, 3).intersection(Rectangle(2, 2, 4, 4)) == Rectangle(2, 2, 3, 3))

    def test_cover(self):
        self.assertTrue(Rectangle(1, 1, 3, 3).cover(Rectangle(2, 2, 4, 4)) == Rectangle(1, 1, 4, 4))

    # def test_make4(self):
        self.assertTrue(Rectangle(1, 1, 3, 3).make4() == (Rectangle(1, 1, 2, 2), Rectangle(2, 1, 3, 2), Rectangle(2, 2, 3, 3), Rectangle(1, 2, 2, 3)))

    def tearDown(self): pass

if __name__ == "__main__":
    unittest.main()     # wszystkie testy