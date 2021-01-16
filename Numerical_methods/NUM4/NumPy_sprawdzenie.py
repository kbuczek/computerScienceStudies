import numpy as np

A1 = np.array([
[10, 8, 1, 1],
[1, 10, 8, 1],
[1, 1, 10, 8],
[1, 1, 1, 10]], dtype = float)



b = np.array([5, 5, 5, 5], dtype = float)

y1 = np.linalg.solve(A1, b)


print("\n")
print("y1 = ", y1)

