
class Time:
    """Klasa reprezentująca odcinek czasu."""

    def __init__(self, s=0):
        """Zwraca instancję klasy Time."""
        self.s = int(s)

    def __str__(self):
        """Zwraca string 'hh:mm:ss'."""
        h = self.s // 3600
        sec = self.s - h * 3600
        m = sec // 60
        sec = sec - m * 60
        return "{0:02d}:{1:02d}:{2:02d}".format(h, m, sec)

    def __repr__(self):
        """Zwraca string 'Time(s)'."""
        return "Time({0})".format(self.s)

    def __add__(self, other):
        """Dodawanie odcinków czasu."""
        return Time(self.s + other.s)

    #def __cmp__(self, other): # Python 2, porównywanie, -1|0|+1
    #    """Porównywanie odcinków czasu."""
    #    return cmp(self.s, other.s)

    # Python 2.7 i Python 3, rich comparisons.
    def __eq__(self, other):
        return self.s == other.s

    def __ne__(self, other):
        return self.s != other.s

    def __lt__(self, other):
        return self.s < other.s

    def __le__(self, other):
        return self.s <= other.s

    def __int__(self):                  # int(time1)
        """Konwersja odcinka czasu do int."""
        return self.s

# Kod testujący moduł.
import unittest

class TestTime(unittest.TestCase):

    def setUp(self): pass

    def test_print(self):       # test str() i repr()
        self.assertTrue(Time(3661).__str__() == '01:01:01')
        self.assertTrue(Time(601).__str__() == '00:10:01')
        self.assertTrue(Time(2).__str__() == '00:00:02')
        self.assertTrue(Time(3661).__repr__() == 'Time(3661)')

    def test_cmp(self):
        # Trzeba sprawdzać ==, !=, >, >=, <, <=.
        self.assertTrue(Time(2) == Time(2))
        self.assertFalse(Time(2) == Time(3))
        self.assertTrue(Time(2) != Time(3))
        self.assertFalse(Time(2) != Time(2))
        self.assertTrue(Time(2) < Time(3))
        self.assertFalse(Time(4) < Time(3))
        self.assertTrue(Time(2) <= Time(3))
        self.assertFalse(Time(4) <= Time(3))
        self.assertTrue(Time(4) > Time(3))
        self.assertFalse(Time(2) > Time(3))
        self.assertTrue(Time(4) >= Time(3))
        self.assertFalse(Time(2) >= Time(3))

    def test_add(self):   # musi działać porównywanie
        self.assertEqual(Time(1) + Time(2), Time(3))
        self.assertEqual(Time(200) + Time(0), Time(200))

    def test_int(self):
        self.assertTrue(Time(1).__int__() == 1)
        self.assertFalse(Time(3661).__int__() == '3661')

    def tearDown(self): pass

if __name__ == "__main__":
    unittest.main()     # wszystkie testy