import random

def create_random_list(n, k):
    L = []
    for i in range(n):
        L.append(random.randint(0, k - 1))
    return L

def linear_search(L, left, right, y):
    indexesFound = []
    i = left
    while i <= right:
        if y == L[i]:
            indexesFound.append(i)
        i += 1
    if len(indexesFound) != 0:
        return indexesFound
    else:
        return None

def main():
    myList = create_random_list(100, 10)
    print("Lista losowych numerów:", myList)

    find_number = myList[random.randint(0, len(myList) - 1)] #wybieram losowy number z listy
    print('Szukany numer:', find_number)

    print('Znalezione indeksy szukanego numeru w liście: ', linear_search(myList, 0, len(myList)-1, find_number))

if __name__ == "__main__":
    main()

