from matplotlib import pyplot as plt
import numpy as np

def przepisFunkcji(x):
    return (1 / (1 + (25 * (x**2))))

def przepisWezlowInterpol(x):
    return (-1 + 2 *(x / n))

def obliczXi(wezlyX, wezlyY):
    # wektory do zapamietania macierzy
    u0 = []; u1 = []; l1 = []
    x = [] #prawa strona rownania
    h = wezlyX[1] - wezlyX[0]

    #dodaje pusty znak do kazdego wektora, bo chce miec indeksy od 1 (potrzebne dla xi[0])
    u0.append(''); u1.append(''); l1.append(''); x.append('')

    for i in range(1, n):
        x.append((6 / (h**2)) * (wezlyY[i-1] - 2*wezlyY[i] + wezlyY[i+1]))
        u0.append(4)
        if i < n-1:
            u1.append(1)
            l1.append(1)          

    # inicjalizacja
    l1[1] = l1[1]/u0[1]

    #obliczam macierz LU
    for i in range(2, n):
        u0[i] = u0[i] - l1[i-1] * u1[i-1]
        if i < n-1:
            l1[i] = l1[i]/u0[i]

    #obliczam wektor 'z' z rownania Lz = x forwardsubstitution
    for i in range(2, n):
        x[i] = x[i] - (l1[i-1] * x[i-1])

    #obliczam wektor 'y' rownania Uy = z backsubstitution
    x[n-1] = x[n-1]/u0[n-1]
    x[n-2] = (x[n-2] - (u1[n-2] * x[n-1])) / u0[n-2]
    for i in reversed(range(1, n-2)):
        x[i] = (x[i] - (u1[i] * x[i+1])) / u0[i]

    #wynik xi jest w wektorze 'x' + warunek naturalnego splajnu kubicznego
    x[0] = 0
    x.append(0)
    return x

def splajnyKubiczne(wezlyX, wezlyY, xi, wezelKoncaPrzedzialu):
    def S(x):
        A = (wezlyX[wezelKoncaPrzedzialu] - x) / (wezlyX[wezelKoncaPrzedzialu] - wezlyX[wezelKoncaPrzedzialu-1])
        B = (x - wezlyX[wezelKoncaPrzedzialu-1]) / (wezlyX[wezelKoncaPrzedzialu] - wezlyX[wezelKoncaPrzedzialu-1])
        C = 1/6 * ((A**3) - A) * ((wezlyX[wezelKoncaPrzedzialu] - wezlyX[wezelKoncaPrzedzialu-1])**2)
        D = 1/6 * ((B**3) - B) * ((wezlyX[wezelKoncaPrzedzialu] - wezlyX[wezelKoncaPrzedzialu-1])**2)
        wzorWielomianu = (A * wezlyY[wezelKoncaPrzedzialu-1]) + (B * wezlyY[wezelKoncaPrzedzialu]) + (C * xi[wezelKoncaPrzedzialu-1]) + (D * xi[wezelKoncaPrzedzialu])
        return wzorWielomianu
    return S

def plot(wezlyX, wezlyY, xi):
    x1 = np.arange(-1, 1, 0.01)
    funkcjaY = []
    for i in x1:
        funkcjaY.append(przepisFunkcji(i))
    
    plt.axis([-1.1,1.1,-0.5,1.1])
    plt.plot(x1, funkcjaY, color="orangered", linewidth=0.5)

    for i in range(1, n+1):
        S = splajnyKubiczne(wezlyX, wezlyY, xi, i)
        x = np.arange(wezlyX[i-1], wezlyX[i], 0.01)
        y = list(map(S, x))
        plt.plot(x, y, linewidth=2, color="tab:blue")

    plt.plot(wezlyX, wezlyY, 'ro')

def main():
    wezlyX = []
    wezlyY = []
    xi = []
    global n, h

    n = int(input("Podaj n = "))

    for i in range(n+1):
        wezlyX.append(przepisWezlowInterpol(i))
        wezlyY.append(przepisFunkcji(wezlyX[i]))

    xi = obliczXi(wezlyX, wezlyY)
    print(xi)
    plot(wezlyX, wezlyY, xi)

    plt.show()

if __name__ == "__main__":
    main()
