number = 4234123408134080008241430034140023420
string = str(number)

def findCharNum(s, ch):
 suma = 0
 for i in string:
  if(i == ch):
   suma += 1
 return suma

print(findCharNum(string, '0'))