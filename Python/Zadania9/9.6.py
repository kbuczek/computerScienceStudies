class Node:
    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.data)

    def insert(self, node):
        if node.data < self.data:   # mniejsze na lewo
            if self.left:
                self.left.insert(node)
            else:
                self.left = node
        else:   # większe lub równe na prawo
            if self.right:
                self.right.insert(node)
            else:
                self.right = node

    def count(self):
        counter = 1
        if self.left:
            counter += self.left.count()
        if self.right:
            counter += self.right.count()
        return counter

    def search(self, data):
        if self.data == data:
            return self
        if data < self.data:
            if self.left:
                return self.left.search(data)
        else:
            if self.right:
                return self.right.search(data)
        return None

    def remove(self, data):  # self na pewno istnieje
        # Są lepsze sposoby na usuwanie.
        if data < self.data:
            if self.left:
                self.left = self.left.remove(data)
        elif self.data < data:
            if self.right:
                self.right = self.right.remove(data)
        else:                # self.data == data
            if self.left is None:   # przeskakuje self
                return self.right
            else:     # self.left na pewno niepuste
                # Szukamy największego w lewym poddrzewie.
                node = self.left
                while node.right:   # schodzimy w dół
                    node = node.right
                node.right = self.right   # przyczepiamy
                return self.left
        return self

    def count_leafs(self): #liczy liście drzewa binarnego
        counter = 0
        if not self.right and not self.left:
            counter += 1
        else:
            if self.left:
                counter += self.left.count_leafs()
            if self.right:
                counter += self.right.count_leafs()
        return counter

    def count_total(self): #suma liczb przechowywanych w drzewie
        counter = 0
        counter += self.data
        if self.left:
            counter += self.left.count_total()
        if self.right:
            counter += self.right.count_total()
        return counter

    def print(self):
        if self is None:
            return
        print('left: ', self.left, 'data:', self.data, 'right: ', self.right)
        if self.left:
            self.left.print()
        if self.right:
            self.right.print()

        
binaryTree = Node(4)
binaryTree.insert(Node(2))
binaryTree.insert(Node(6))
binaryTree.insert(Node(8))
binaryTree.insert(Node(5))
binaryTree.insert(Node(3))
print(binaryTree.count_leafs()) #3
print(binaryTree.count_total()) #28
print()
binaryTree.print()