try:
    liczba = int(input("Podaj liczbę: "))
except ValueError:
    print("To nie jest liczba typu int!")

if liczba > 99999:
    print("Za duża liczba!")
    quit()

string = "|"
for i in range(liczba):
    string += "....|"
string += "\n0"
for i in range(1, liczba+1):
    string += str("{: 5d}".format(i))

print(string)

