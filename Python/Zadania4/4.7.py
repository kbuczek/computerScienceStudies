lista = [1,(2,3),[],[4,(5,6,7)],8,[9]]
seq = []

def flatten(sequence):
    global seq
    for i in range(len(sequence)):
        if isinstance(sequence[i], (list, tuple)) == False:
            seq.append(sequence[i])
        else:
            flatten(sequence[i])

flatten(lista)
print(seq)