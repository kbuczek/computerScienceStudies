from matplotlib import pyplot as plt
import numpy as np
import math

n = int(input("Podaj n = "))

def przepisFunkcji(x):
    return (1 / (1 + (25 * (x**2))))

def przepisWezlowInterpol(x):
    return (math.cos(((2*x) + 1) / (2*(n+1)) * math.pi))

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


# b) niejednorodne wezly interpolacji z funkcja y
wezlyX_b = []
wezlyY_b = []

for i in range(n+1):
    wezlyX_b.append(przepisWezlowInterpol(i)) 
    wezlyY_b.append(przepisFunkcji(wezlyX_b[i]))

W = lagrange(wezlyX_b, wezlyY_b)
plot(W, wezlyX_b, wezlyY_b)

plt.show()
