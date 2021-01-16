from matplotlib import pyplot as plt
import numpy as np

n = int(input("Podaj n = "))

def przepisFunkcji(x):
    return (1 / (1 + (25 * (x**2))))

def przepisWezlowInterpol(x):
    return (-1 + 2 *(x / (n + 1)))

def lagrange(wezlyX, wezlyY):
    def W(x):
        total = 0
        for i in range(len(wezlyX)):
            def theta(i):
                totalMul = 1
                for j in range(len(wezlyX)):
                    if i == j:
                        continue
                    totalMul *= (x - wezlyX[j]) / (wezlyX[i] - wezlyX[j])
                return totalMul
            total += theta(i) * wezlyY[i]
        return total
    return W

def plot(f, wezlyX, wezlyY):
    x = np.arange(-1.0, 1.0, 0.01)
    y = list(map(f, x))

    funkcjaY = []
    for i in x:
        funkcjaY.append(przepisFunkcji(i))
    
    plt.axis([-1.1,1.1,-0.5,1.1])
    plt.plot(x, funkcjaY, color="orangered")
    plt.plot(x, y)
    plt.plot(wezlyX, wezlyY, 'ro')


# a) jednorodne wezly interpolacji z funkcja y
wezlyX_a = []
wezlyY_a = []

for i in range(n+1):
    wezlyX_a.append(przepisWezlowInterpol(i))
    wezlyY_a.append(przepisFunkcji(wezlyX_a[i]))

W = lagrange(wezlyX_a, wezlyY_a)
plot(W, wezlyX_a, wezlyY_a)

plt.show()
