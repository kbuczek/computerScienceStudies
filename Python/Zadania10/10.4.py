import unittest

class Queue:

    def __init__(self):
        self.items = []

    def __str__(self):             # podglądanie kolejki
        return str(self.items)

    def is_empty(self):
        return not self.items

    def is_full(self):             # nigdy nie jest pełna
        return False

    def put(self, data):
        if self.is_full():
            raise ValueError("Kolejka jest przepełniona!")
        self.items.append(data)

    def get(self):
        if self.is_empty():
            raise ValueError("Kolejka jest pusta!")
        return self.items.pop(0)   # mało wydajne!
        

class TestQueue(unittest.TestCase):

    def setUp(self):
        self.queue = Queue()

    def test_put(self):
        for i in range(10):
            self.queue.put(i)
        self.queue.put(11) #nie da się przepełnić kolejki

    def test_get(self):
        self.queue.put(1)
        self.assertEqual(self.queue.get(), 1)
        with self.assertRaises(ValueError):
            self.queue.get()

    def test_str(self):
        self.assertEqual(str(self.queue), '[]')

    def test_is_empty(self):
        self.assertEqual(self.queue.is_empty(), True)

    def test_is_full(self):
        self.assertEqual(self.queue.is_full(), False)


if __name__ == '__main__':
    unittest.main()  # uruchamia wszystkie testy
