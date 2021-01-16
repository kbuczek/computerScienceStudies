import numpy as np

A1 = np.array([
[3, 1, 0.2, 0],
[1, 3, 1, 0.2],
[0.2, 1, 3, 1],
[0, 0.2, 1, 3]], dtype = float)



b = np.array([1, 2, 3, 4], dtype = float)

y1 = np.linalg.solve(A1, b)


print("\n")
print("y1 = ", y1)

