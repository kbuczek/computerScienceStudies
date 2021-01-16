# wektory do zapamietania macierzy
u0 = []; u1 = []; b = []; v = []; y =[]
diag = 10
naddiag = 8

N = int(input("Podaj wymiar macierzy N: "))

for i in range(0, N):
    b.append(5)
    v.append(1)
    y.append(1)
    u0.append(diag-1)
    if i < N-1:
        u1.append(naddiag-1)

#obliczam wektor z rownania Az = b, za wektor b podstawiam z
b[N-1] = b[N-1]/u0[N-1]
for i in reversed(range(N-1)):
    b[i] = (b[i] - (u1[i] * b[i+1])) / u0[i]

#obliczam wektor z' rownania Az' = v, za wektor y podstawiam z'
y[N-1] = y[N-1]/u0[N-1]
for i in reversed(range(N-1)):
    y[i] = (y[i] - (u1[i] * y[i+1])) / u0[i]

#obliczam wektor koncowy ze wzoru Shemana-Morrisona, gdzie b = z, v = z'
vTz = 0; vTz_prim = 0;

for i in range(N):
    vTz += v[i] * b[i]
    vTz_prim += v[i] * y[i]

for i in range(N):
    y[i] = (y[i] * vTz) / (1 + vTz_prim)
    b[i] = b[i] - y[i]

print("Wynik:")
print(b)

