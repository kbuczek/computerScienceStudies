class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next

    def __str__(self):
        return str(self.data)


class SingleList:
    def __init__(self):
        self.length = 0
        self.head = None
        self.tail = None

    def is_empty(self):
        #return self.length == 0
        return self.head is None

    def count(self):
        return self.length

    def insert_head(self, node):
        if self.head:   # dajemy na koniec listy
            node.next = self.head
            self.head = node
        else:   # pusta lista
            self.head = self.tail = node
        self.length += 1

    def insert_tail(self, node):   # klasy O(N)
        if self.head:   # dajemy na koniec listy
            self.tail.next = node
            self.tail = node
        else:   # pusta lista
            self.head = self.tail = node
        node.next = None
        self.length += 1

    def remove_head(self):          # klasy O(1)
        if self.is_empty():
            raise ValueError("pusta lista")
        node = self.head
        if self.head == self.tail:   # self.length == 1
            self.head = self.tail = None
        else:
            self.head = self.head.next
        node.next = None   # czyszczenie łącza
        self.length -= 1
        return node   # zwracamy usuwany node


    def remove_tail(self):  # klasy O(N)
        if self.is_empty():
            raise ValueError("pusta lista")
        node = self.tail
        temp_node = self.head
        if self.length == 1:
            self.tail = self.head = None
        else:
            while temp_node.next != self.tail:
                temp_node = temp_node.next
            temp_node.next = None
        self.length -= 1
        return node


    def merge(self, other):   # klasy O(1)
        while not other.is_empty():
            node = other.remove_head()
            self.insert_tail(node)


    def clear(self):     # czyszczenie listy
        while not self.is_empty():
            node = self.remove_head()
            del node

    def print(self):
        if self.is_empty():
            print("Lista pusta")
        node = self.head
        while node:
            print(node.data, end=' ')
            node = node.next
        print()


alist = SingleList()

alist.insert_head(Node(11))         # [11]
alist.insert_head(Node(22))         # [22, 11]
alist.insert_tail(Node(33))        # [22, 11, 33]
alist.print()

alist2 = SingleList()
alist2.insert_head(Node(44))
alist2.insert_head(Node(55))
alist2.insert_head(Node(66))
alist2.print()


alist.merge(alist2)
alist.print()
alist2.print()

alist2.insert_head(Node(44))
alist2.insert_head(Node(55))
alist2.insert_head(Node(66))
alist2.remove_tail()
# alist2.print()

alist2.insert_head(Node(66))
alist2.clear()
# alist2.print()
