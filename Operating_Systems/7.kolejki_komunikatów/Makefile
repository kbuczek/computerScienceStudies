klient1: klient1.c kolejki_kom.c
	gcc klient1.c kolejki_kom.c -std=c11 -o klient1
	
klient2: klient2.c kolejki_kom.c
	gcc klient2.c kolejki_kom.c -std=c11 -o klient2

serwer: serwer.c kolejki_kom.c
	gcc serwer.c kolejki_kom.c -std=c11 -o serwer

all: klient1 klient2 serwer

