line = "maslo chleb\tszynka\nser   \n pomidor"
line2 = ""
list = line.split()

for x in range(len(list)):
 print(list[x][:2], end='')
print()

for x in range(len(list)):
 print(list[x][-2:], end='')
print()