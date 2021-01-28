create database sklep_papierniczy;
use sklep_papierniczy;

create table produkty ( 
    lp int not null auto_increment, 
    nazwa varchar(100) not null, 
    typ int not null, 
    rok_produkcji int not null,
    producent varchar(50) not null,
    primary key(lp) 
); 

create table typy_produktow ( 
    lp int not null auto_increment, 
    typ varchar(50) not null, 
    rodzaj varchar(50) not null, 
    rozmiar varchar(100),
    ilosc_kartek int,
    okladka varchar(50), 
    primary key(lp) 
);

create table stan_magazynu ( 
    lp int not null auto_increment, 
    produkt int not null, 
    ilosc int not null, 
    sektor int not null,
    miejsce int not null,
    cena_za_sztuke decimal not null, 
    primary key(lp) 
);

create table dokumenty_zakupu ( 
    lp int not null auto_increment, 
    klient int not null, 
    data_zakupu date not null, 
    data_zaplaty date not null,
    kwota_brutto decimal not null,
    faktura int not null,
    numer_dokumentu varchar(100) not null,
    primary key(lp) 
); 

create table pozycje_dokumentow_zakupu ( 
    lp int not null auto_increment, 
    dokument_zakupu int not null, 
    produkt int not null, 
    cena decimal not null,
    ilosc int not null,

    primary key(lp) 
); 

create table dokumenty_sprzedazy ( 
    lp int not null auto_increment, 
    klient int not null, 
    data_wystawienia date not null, 
    data_zaplaty date not null,
    kwota_brutto decimal not null,
    faktura int not null,  
    numer_dokumentu varchar(100),
    primary key(lp) 
);

create table pozycje_dokumentow_sprzedazy ( 
    lp int not null auto_increment, 
    dokument_zakupu int not null, 
    produkt int not null, 
    cena decimal not null,
    ilosc int not null,
    primary key(lp) 
); 

create table klienci ( 
    lp int not null auto_increment, 
    NIP int not null, 
    nazwa varchar(200) not null,
    adres varchar(200) not null,
    primary key(lp) 
);

ALTER TABLE pozycje_dokumentow_zakupu ADD wartosc decimal not null;
ALTER TABLE pozycje_dokumentow_sprzedazy ADD wartosc decimal not null;

INSERT INTO typy_produktow (typ, rodzaj) VALUES ('pióro', 'praworęczny');
INSERT INTO typy_produktow (typ, rodzaj) VALUES ('długopis', 'praworęczny');
INSERT INTO typy_produktow (typ, rodzaj, rozmiar, ilosc_kartek, okladka) VALUES ('zeszyt', 'kratka', 'A5', 60, 'miękka');
INSERT INTO typy_produktow (typ, rodzaj) VALUES ('pióro', 'leworęczny');
INSERT INTO typy_produktow (typ, rodzaj, rozmiar) VALUES ('naboje', 'niebieskie', 'S');
INSERT INTO typy_produktow (typ, rodzaj, rozmiar, ilosc_kartek, okladka) VALUES ('zeszyt', 'linie', 'A4', 120, 'twarda');


INSERT INTO klienci (NIP, nazwa, adres) VALUES ('145233', 'Producent Produktów Papierniczych Mavex', 'ul. Łojasiewicza 34, 33-514, Krakow');
INSERT INTO dokumenty_zakupu (klient, data_zakupu, data_zaplaty, kwota_brutto, faktura, numer_dokumentu) VALUES (1, '2020-11-29', '2020-11-29', 478.3, 1, 'LU/001/10/2020');

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Pióro Schr a10', 1, 2020, 'Schr');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 1, 115, 1, 115);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (1, 1, 5, 36, 115);

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Długopis Martn vl30', 2, 2020, 'Martn');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 2, 130, 2, 260);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (2, 2, 4, 3, 130);

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Zeszyt Zet A5', 3, 2020, 'Zet Papier');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 3, 1.2, 5, 6);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (3, 5, 2, 15, 1.2);

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Pióro Schr a20', 4, 2020, 'Schr');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 4, 230, 1, 230);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (4, 1, 1, 1, 230);

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Naboje do piór Changl', 5, 2020, 'Changl');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 5, 0.10, 200, 20);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (5, 200, 2, 21, 0.10);

INSERT INTO produkty (nazwa, typ, rok_produkcji, producent) VALUES ('Zeszyt Martin A4', 6, 2020, 'Martin');
INSERT INTO pozycje_dokumentow_zakupu (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 6, 2, 40, 80);
INSERT INTO stan_magazynu (produkt, ilosc, sektor, miejsce, cena_za_sztuke) VALUES (6, 40, 4, 2, 2);


INSERT INTO klienci (NIP, nazwa, adres) VALUES ('572985', 'Abc', 'ul. Toporna 14, 40-501, Warszawa');
INSERT INTO dokumenty_sprzedazy (klient, data_wystawienia, data_zaplaty, kwota_brutto, faktura, numer_dokumentu) VALUES (2, '2020-11-30', '2020-11-30', 381, 1, '1/2020');

INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 1, 115, 1, 115);
INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 2, 130, 2, 260);
INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (1, 3, 1.2, 5, 6);


INSERT INTO klienci (NIP, nazwa, adres) VALUES ('135590', 'Papier', 'ul. Miłosiewicza 1, 50-521, Toruń');
INSERT INTO dokumenty_zakupu (klient, data_zakupu, data_zaplaty, kwota_brutto, faktura, numer_dokumentu) VALUES (3, '2020-11-30', '2020-11-30', 330, 1, '123/R/2020');

INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (2, 4, 230, 1, 230);
INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (2, 5, 0.10, 200, 20);
INSERT INTO pozycje_dokumentow_sprzedazy (dokument_zakupu, produkt, cena, ilosc, wartosc) VALUES (2, 6, 2, 40, 80);