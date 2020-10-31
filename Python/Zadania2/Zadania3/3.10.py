#1 sposob tworzenia slownika
D1 = {}
D1['I'] = 1
D1['V'] = 5
D1['X'] = 10
D1['L'] = 50
D1['C'] = 100
D1['D'] = 500
D1['M'] = 1000

#2 sposob tworzenia slownika
D2 = dict(I=1, V=5, X=10, L=50, C=100, D=500, M=1000)

#3 sposob tworzenia slownika
D3 = { 'I':1, 'V':5, 'X':10, 'L':50, 'C':100, 'D':500, 'M':1000}

liczba1 = "CDXXII" #422
liczba2 = "MCCLII" #1252
liczba3 = "MMMCDLVI" #3456

def roman2int(liczba):
    suma = 0
    for i in range(len(liczba)):
        cyfra1 = D1.get(liczba[i])
        if(i != len(liczba)-1):
            cyfra2 = D1.get(liczba[i+1])
        if cyfra1 >= cyfra2:
            suma += cyfra1
        else:
            suma -= cyfra1
    print(suma)

roman2int(liczba1)
roman2int(liczba2)
roman2int(liczba3)
