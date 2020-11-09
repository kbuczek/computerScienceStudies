def liniaLiczb(l):
    string = "|"
    for i in range(l):
        string += "....|"
    string += "\n0"
    for i in range(1, l+1):
        string += str("{: 5d}".format(i))
    return string

print(liniaLiczb(5))

def siatka(x, y):
    rzad1 = "---".join(["+"] * (x+1)) + "\n"
    rzad2 = "   ".join(["|"] * (x+1)) + "\n"
    return (rzad2.join([rzad1] * (y+1)))

print(siatka(5, 3))
