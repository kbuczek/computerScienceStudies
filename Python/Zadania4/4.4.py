def fibonacci(n):
    a = 0; b = 1; temp = 0;
    for i in range(n):
        temp = b;
        b += a;
        a = temp;
    return b

print(fibonacci(6))