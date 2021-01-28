create database linie_lotnicze;
use linie_lotnicze;

create table samoloty ( 
    lp int not null auto_increment, 
    rodzaj_samolotu int not null, 
    numer_seryjny varchar(100) not null, 
    data_przegladu date not null,
    czy_usuniety_z_floty int not null, 
    primary key(lp) 
); 

create table rodzaj_samolotow ( 
    lp int not null auto_increment, 
    firma varchar(50) not null, 
    model varchar(50) not null, 
    rok_produkcji int not null,
    ilosc_miejsc int not null, 
    primary key(lp) 
); 

create table pasazerowie ( 
    lp int not null auto_increment, 
    imie varchar(50) not null, 
    nazwisko varchar(100) not null, 
    nr_paszportu int not null,
    telefon int not null,
    email varchar(100) not null,
    primary key(lp) 
); 

create table zaloga ( 
    lp int not null auto_increment, 
    imie varchar(50) not null, 
    nazwisko varchar(100) not null, 
    pilot int not null,
    stewardessa int not null,
    nr_licencji int not null,
    primary key(lp) 
); 

create table rejsy ( 
    lp int not null auto_increment,
    miejsce_odlotu varchar(50) not null,
    miejsce_przylotu varchar(50) not null, 
    data_odlotu date not null,
    godzina_odlotu varchar(5) not null, 
    samolot int not null, 
    primary key(lp) 
);

create table osoby_rejsu (
    lp int not null auto_increment,
    rejs int not null,
    pasazer int,
    zaloga int,
    primary key(lp)
);

create table bilety (
    lp int not null auto_increment,
    pasazer int not null,
    rejs int not null,
    cena_biletu int not null,
    miejsce_w_samolocie varchar(50) not null,
    primary key(lp)
);

INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (1, 'SSY-1243-5423', '2010-10-10', 1);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (2, 'ABB-6345-4251', '2020-11-13', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (2, 'ABB-6345-2441', '2020-05-03', 1);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (3, 'OKZ-5234-8903', '2020-11-14', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (4, 'HGY-234735-53', '2020-11-20', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (4, 'HGY-789517-62', '2020-11-05', 0);

INSERT INTO rodzaj_samolotow (firma, model, rok_produkcji, ilosc_miejsc) VALUES ('Boeing', '737', 1979, 150);
INSERT INTO rodzaj_samolotow (firma, model, rok_produkcji, ilosc_miejsc) VALUES ('Airbus', 'Dreamliner', 2019, 200);
INSERT INTO rodzaj_samolotow (firma, model, rok_produkcji, ilosc_miejsc) VALUES ('Cessna', 'Avito 7', 2011, 40);
INSERT INTO rodzaj_samolotow (firma, model, rok_produkcji, ilosc_miejsc) VALUES ('Boeing', '789', 2005, 175);

INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Mariusz', 'Kowal', '314234123', '340234831', 'mariuszkowal@email.com');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Agnieszka', 'Franczyk', '598123809', '123123809', 'agnieszka123@outlook.com');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Arkadiusz', 'Boniecki', '231234144', '123123870', 'arkadbon@wp.pl');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Katarzyna', 'Hanicka', '213123989', '523480980', 'katarzyna.hanicka.1984@onet.pl');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Krzysztof', 'Ptak', '539381239', '348103284', 'ptakrzysztof@gmail.com');

INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Arkadiusz', 'Maćkowski', 1, 0, 324232312);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Filip', 'Magnet', 0, 1, 1323451);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Zofia', 'Buzek', 1, 0, 847125351);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Halina', 'Zorzyk', 0, 1, 2358041);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Grzegorz', 'Malina', 0, 1, 1498823);

INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, samolot) VALUES ('Krakow', 'Paryż', '2020-11-20', '15:00', 2);
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, samolot) VALUES ('Berlin', 'Nowy York', '2020-11-20', '19:30', 4);
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, samolot) VALUES ('Londyn', 'Tokyo', '2020-11-21', '8:00', 5);
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, samolot) VALUES ('Krakow', 'Paryż', '2020-11-22', '12:35', 6);

INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (1, 1);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (1, 3);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (1, 2);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (1, 2);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (2, 1);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (2, 3);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (2, 4);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (3, 3);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (3, 5);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (4, 4);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (4, 5);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 1);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 2);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 4);

INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie) VALUES (1, 2, 1560, '17A');
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie) VALUES (2, 1, 250, '43C');
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie) VALUES (3, 4, 2547, '13D');
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie) VALUES (4, 3, 3421, '31C');
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie) VALUES (5, 1, 271, '1A');

SELECT * FROM samoloty;
SELECT rodzaj_samolotu, numer_seryjny FROM samoloty;
SELECT model FROM rodzaj_samolotow WHERE ilosc_miejsc > 150;
SELECT imie, nazwisko, email FROM pasazerowie WHERE imie LIKE 'A%';
SELECT imie, nazwisko FROM zaloga WHERE pilot=1;
SELECT miejsce_odlotu, miejsce_przylotu FROM rejsy WHERE data_odlotu='2020-11-20';
SELECT rejs FROM osoby_rejsu WHERE pasazer=4;
SELECT rejs FROM bilety WHERE cena_biletu < 1000;
