from math import sqrt
from matplotlib import pyplot as plt
dev1_x = []
dev1_y = []
dev2_y = []

# wektory do zapamietania macierzy
d = []; u1 = []; u2 = []; l1 = []; l2 = []; b = []
x = []; y = []; z  = []; norma = 0

N = int(input("Podaj wymiar macierzy N: "))
I = int(input("Podaj ilosc iteracji: "))

for i in range(0, N):
    b.append(i+1)
    d.append(3)
    x.append(0)
    y.append(0)
    z.append(0)
    if i < N-1:
        u1.append(1)
        l1.append(1)
    if i < N-2:
        u2.append(0.2)
        l2.append(0.2)

# rozwiazanie dokladne x* z 30 iteracjami zapisane w wektorze z
for i in range(0, 30):
    z[0] = (b[0] - (u1[0] * z[1]) - (u2[0] * z[2]))/d[0]
    z[1] = (b[1] - (l1[0] * z[0]) - (u1[1] * z[2]) - (u2[1] * z[3]))/d[1]

    for j in range(2, N-2):
        z[j] = (b[j] - (l1[j-2] * z[j-2]) - (l2[j-1] * z[j-1]) - (u1[j] * z[j+1]) - (u2[j] * z[j+2]))/d[j]

    z[N-2] = (b[N-2] - (l2[N-4] * z[N-4]) - (l1[N-3] * z[N-3]) - (u1[N-2] * z[N-1]))/d[N-2]
    z[N-1] = (b[N-1] - (l2[N-3] * z[N-3]) - (l1[N-2] * z[N-2]))/d[N-1]

#metoda Jacobiego
for i in range(0, I):
    y[0] = (b[0] - (u1[0] * x[1]) - (u2[0] * x[2]))/d[0]
    y[1] = (b[1] - (l1[0] * x[0]) - (u1[1] * x[2]) - (u2[1] * x[3]))/d[1]

    for j in range(2, N-2):
        y[j] = (b[j] - (l1[j-2] * x[j-2]) - (l2[j-1] * x[j-1]) - (u1[j] * x[j+1]) - (u2[j] * x[j+2]))/d[j]

    y[N-2] = (b[N-2] - (l2[N-4] * x[N-4]) - (l1[N-3] * x[N-3]) - (u1[N-2] * x[N-1]))/d[N-2]
    y[N-1] = (b[N-1] - (l2[N-3] * x[N-3]) - (l1[N-2] * x[N-2]))/d[N-1]
    x = y

    dev1_x.append(i)
    for k in range(0, N):
        norma += (x[k] - z[k])**2

    dev1_y.append(sqrt(norma))
    norma = 0
    
print("Wynik metody Jacobiego:")
print(x)

for i in range(0, N):
    x[i] = 0

#metoda Gaussa-Seidela
for i in range(0, I):
    x[0] = (b[0] - (u1[0] * x[1]) - (u2[0] * x[2]))/d[0]
    x[1] = (b[1] - (l1[0] * x[0]) - (u1[1] * x[2]) - (u2[1] * x[3]))/d[1]

    for j in range(2, N-2):
        x[j] = (b[j] - (l1[j-2] * x[j-2]) - (l2[j-1] * x[j-1]) - (u1[j] * x[j+1]) - (u2[j] * x[j+2]))/d[j]

    x[N-2] = (b[N-2] - (l2[N-4] * x[N-4]) - (l1[N-3] * x[N-3]) - (u1[N-2] * x[N-1]))/d[N-2]
    x[N-1] = (b[N-1] - (l2[N-3] * x[N-3]) - (l1[N-2] * x[N-2]))/d[N-1]

    for k in range(0, N):
        norma += (x[k] - z[k])**2
        
    dev2_y.append(sqrt(norma))
    norma = 0

print("Wynik metody Gaussa-Seidla:")
print(x)

# plt.yscale('log')
plt.plot(dev1_x, dev1_y)
plt.plot(dev1_x, dev2_y)
plt.show()

