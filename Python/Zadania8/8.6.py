D = {}

def dynamiczneP(i, j):
    global D
    # if D.get(i, j) != None:
    #     return D.get(i, j)

    D[(0, 0)] = 0.5
    for a in range(1, i+1):
        D[(a, 0)] = 0.0
    for a in range(1, j+1):
        D[(0, a)] = 1.0
    for a in range(1, i+1):
        for b in range(1, j+1):
            D[(a, b)] = 0.5 * (D[(a-1, b)] + D[(a, b-1)])
    return D.get((i, j))

def rekurencyjneP(i, j):
    if i == 0 and j == 0:
        return 0.5
    elif i > 0 and j == 0:
        return 0.0
    elif i == 0 and j > 0:
        return 1.0
    elif i > 0 and j > 0:
        return 0.5 * (rekurencyjneP(i-1, j) + rekurencyjneP(i, j-1))
    else:
        raise ValueError("i < 0 lub j < 0")

print(dynamiczneP(4, 5))
print(rekurencyjneP(4, 5))