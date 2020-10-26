L = [23, 55, 1, 54, 123, 15, 435, 3]
string = ""

for i in L:
 string += str(i).zfill(3)

print(string)