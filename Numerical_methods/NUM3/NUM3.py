# wektory do zapamietania macierzy
u0 = []; u1 = []; u2 = []; l1 = []; x = []
detA = 1

N = int(input("Podaj wymiar macierzy N: "))

for i in range(0, N):
    x.append(i+1)
    u0.append(1.2)
    if i < N-1:
        u1.append(0.1/(i+1))
        l1.append(0.2)
    if i < N-2:
        u2.append(0.4/((i+1)**2))

# inicjalizacja
l1[0] = l1[0]/u0[0]

#obliczam macierz LU
for i in range(1, N):
    u0[i] = u0[i] - l1[i-1] * u1[i-1]
    if i < N-1:
        l1[i] = l1[i]/u0[i]
        u1[i] = u1[i] - l1[i-1] * u2[i-1]

#obliczam wyznacznik macierzy A
for i in range(N):
    detA *= u0[i]
print("det A = ", detA)

#obliczam wektor y z rownania Lz = x
for i in range(1, N):
    x[i] = x[i] - (l1[i-1] * x[i-1])

#obliczam wektor z rownania Uy = z
x[N-1] = x[N-1]/u0[N-1]
x[N-2] = (x[N-2] - (u1[N-2] * x[N-1])) / u0[N-2]
for i in reversed(range(N-2)):
    x[i] = (x[i] - (u2[i] * x[i+2]) - (u1[i] * x[i+1])) / u0[i]

print("Wynik:")
print(x)

