line = "maslo chleb\tszynka\nser   \n pomidor"
longest = ""
list = line.split()

for x in list:
 if(len(x) > len(longest)):
  longest = x

print(longest, len(longest))