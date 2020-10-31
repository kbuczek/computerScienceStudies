try:
    wysokosc = int(input("Podaj wysokość: "))
    szerokosc = int(input("Podaj szerokość: "))
except ValueError:
    print("To nie jest liczba typu int!")

if wysokosc > 100 or szerokosc > 100:
    print("Za duża liczba!")
    exit()

string = ""

for i in range(wysokosc):
    string += "+"
    for i in range(1, szerokosc+1):
        string += "---+"
    string += "\n|"
    for i in range(1, szerokosc+1):
        string += "   |"
    string += "\n"

string += "+"
for i in range(1, szerokosc+1):
    string += "---+"

print(string)

