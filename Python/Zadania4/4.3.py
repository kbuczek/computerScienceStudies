def factorial(n):
    x = 1
    if n < 2:
        return n;
    else:
        for i in range(1, n+1):
            x *= i
        return x

print(factorial(4))