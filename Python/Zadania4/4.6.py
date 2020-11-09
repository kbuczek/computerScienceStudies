lista = [1, 2, [5, 8], 4, (13, 18), 6, [17, [1, 3], 1], 8] #87
suma = 0

def sum_seq(sequence):
    global suma
    for i in range(len(sequence)):
        if isinstance(sequence[i], (list, tuple)) == False:
            suma += sequence[i]
        else:
            sum_seq(sequence[i])

sum_seq(lista)
print(suma)