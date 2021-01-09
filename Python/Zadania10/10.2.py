import unittest

class Stack:

    def __init__(self, size=10):
        self.items = size * [None]      # utworzenie tablicy
        self.n = 0                      # liczba elementów na stosie
        self.size = size

    def is_empty(self):
        return self.n == 0

    def is_full(self):
        return self.size == self.n

    def push(self, data):
        if self.is_full():
            raise ValueError("Stos jest pełny!")
        self.items[self.n] = data
        self.n += 1

    def pop(self):
        if self.is_empty():
            raise ValueError("Stos jest pusty!")
        self.n -= 1
        data = self.items[self.n]
        self.items[self.n] = None    # usuwam referencję
        return data

class TestStack(unittest.TestCase):

    def setUp(self):
        self.stack = Stack()

    def test_push(self):
        for i in range(10):
            self.stack.push(i)
        with self.assertRaises(ValueError):
            self.stack.push(11)

    def test_pop(self):
        self.stack.push(1)
        self.assertEqual(self.stack.pop(), 1)
        with self.assertRaises(ValueError):
            self.stack.pop()

    def test_is_empty(self):
        self.assertEqual(self.stack.is_empty(), True)
        self.stack.push(1)
        self.assertEqual(self.stack.is_empty(), False)

    def test_is_full(self):
        self.assertEqual(self.stack.is_full(), False)
        for i in range(10):
            self.stack.push(i)
        self.assertEqual(self.stack.is_full(), True)

if __name__ == '__main__':
    unittest.main()  # uruchamia wszystkie testy
