sek1 = (1, 2, 8, 8, 5, 23, 2) 
sek2 = (7, 6, 80, 1, 123, 2)
A = []
B = []

for i in range(len(sek1)):
    for j in range(len(sek2)):
        if sek1[i] == sek2[j]:
            if A.count(sek1[i]) == 0:
                A.append(sek1[i])

print("(a): ", A)

for i in range(len(sek1)):
    if B.count(sek1[i]) == 0:
        B.append(sek1[i])

for i in range(len(sek2)):
    if B.count(sek2[i]) == 0:
        B.append(sek2[i])

print("(b): ", B)
