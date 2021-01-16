import random

def create_random_list(n, k):
    L = []
    for i in range(n):
        L.append(random.randint(0, k - 1))
    L.sort()
    return L

def binarne_rek(L, left, right, y):
    """Wyszukiwanie binarne w wersji rekurencyjnej."""
    if left <= right:
        k = (left+right) // 2
        if y == L[k]:
            return k
        if y < L[k]:
            return binarne_rek(L, left, k-1, y)
        else:
            return binarne_rek(L, k+1, right, y)
    return None

def main():
    myList = create_random_list(100, 10)
    print("Lista losowych numerów:", myList)

    find_number = myList[random.randint(0, len(myList) - 1)] # wybieram losowy number z listy
    print('Szukany numer:', find_number)

    print('Znaleziony indeks dowolnej szukanej liczby w liście: ', binarne_rek(myList, 0, len(myList)-1, find_number))

if __name__ == "__main__":
    main()
