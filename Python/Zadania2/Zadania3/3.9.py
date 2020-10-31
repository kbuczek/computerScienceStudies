L = [[],[4],(1,2),[3,4],(5,6,7)]
L2 = []

for i in L:
    suma = 0
    for j in i:
        suma += j
    L2.append(suma)
    
print(L2)