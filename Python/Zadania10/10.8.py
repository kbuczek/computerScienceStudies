import random

class RandomQueue:

    def __init__(self):
        self.items = []

    def __str__(self):
        return str(self.items)

    def __len__(self):
        return len(self.items)

    def insert(self, item):
        self.items.append(item)

    def remove(self):   # zwraca losowy element
        if self.is_empty():
            raise ValueError("Kolejka jest pusta!")
        i = random.randint(0, len(self.items) - 1)
        temp = self.items[i]
        self.items[i] = self.items[-1]
        self.items[-1] = temp
        return self.items.pop()

    def is_empty(self):
        return not self.items

    def is_full(self):
        return False

    def clear(self):     # czyszczenie listy
        self.items.clear()

randomQueue = RandomQueue()
for i in range(5):
    randomQueue.insert(i)
print(randomQueue)

for i in range(len(randomQueue)):     
    randomQueue.remove()
    print(randomQueue)

