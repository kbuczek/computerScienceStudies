lista1 = [1, 2, [5, 8], 4, "ab", 6]
lista2 = [1, 2, [5, 8], 4, "ab", 6]

#iteracyjna
def odwracanie_ite(L, left, right):
    length = (right - left)
    ite = int(length/2)
    for i in range(ite+1):
        temp = L[right]
        L[right] = L[left]
        L[left] = temp
        right -= 1
        left += 1

#rekurencyjna
def odwracanie_rek(L, left, right):
    if left < right:
        temp = L[left]
        L[left] = L[right]
        L[right] = temp
        right -= 1
        left += 1
        odwracanie_rek(L, left, right)

odwracanie_ite(lista1, 1, 4)
odwracanie_rek(lista2, 1, 4)
print(lista1)
print(lista2)