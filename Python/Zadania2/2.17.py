line = "maslo chleb\tszynka\nser    \n Pomidor"

L = line.split()
print(sorted(L, key=str.lower))
print(sorted(L, key=len))