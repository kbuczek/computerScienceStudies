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
    typ varchar(50) not null,
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

ALTER TABLE rodzaj_samolotow ADD cargo int not null;
ALTER TABLE rejsy ADD czas_lotu varchar(50);
ALTER TABLE rejsy ADD linia_lotnicza varchar(100) not null;
ALTER TABLE bilety ADD klasa varchar(50) not null;
ALTER TABLE bilety ADD pierwszenstwo int not null;
ALTER TABLE bilety ADD posredni int;

INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (1, 'SSY-1243-5423', '2010-10-10', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (2, 'ABB-6345-4251', '2020-11-13', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (2, 'ABB-6345-2441', '2020-05-03', 1);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (3, 'OKZ-5234-8903', '2020-11-14', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (4, 'HGY-234735-53', '2020-11-20', 0);
INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (5, 'HGY-789517-62', '2020-11-05', 0);

INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, cargo) VALUES ('wąskokadłubowy', 'Boeing', '737', 1979, 120, 200);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, cargo) VALUES ('szerokokadłubowy', 'Airbus', 'Dreamliner', 2019, 350, 300);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, cargo) VALUES ('szerokokadłubowy', 'Cessna', 'Avito 7', 2011, 200, 400);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, cargo) VALUES ('wąskokadłubowy', 'Boeing', '789', 2005, 100, 100);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, cargo) VALUES ('wąskokadłubowy', 'Militech', 'Destiny', 2020, 140, 250);

INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Anna', 'Nowak', '314234123', '340234831', 'annanowak@email.com');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Jan', 'Kowalski', '598123809', '123123809', 'jankowalski@outlook.com');
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES ('Piotr', 'Kwiatkowski', '231234144', '123123870', 'piotrkwiatkowski@wp.pl');

INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Arkadiusz', 'Maćkowski', 1, 0, 324232312);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Filip', 'Magnet', 0, 1, 1323451);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Zofia', 'Buzek', 1, 0, 847125351);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Halina', 'Zorzyk', 0, 1, 2358041);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Grzegorz', 'Malina', 0, 1, 1498823);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Maciej', 'Andrus', 1, 0, 1238034);
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES ('Błażej', 'Jok', 0, 1, 980248);

INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, czas_lotu, samolot, linia_lotnicza) VALUES ('Warszawa', 'Frankfurt', '2020-11-20', '15:00', '40min', 1, 'FlyWell Airlines');
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, czas_lotu, samolot, linia_lotnicza) VALUES ('Frankfurt', 'Seul', '2020-11-20', '17:00', '11godz', 2, 'FlyWell Airlines');
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, czas_lotu, samolot, linia_lotnicza) VALUES ('Kraków', 'Chicago', '2020-11-20', '01:00', '12godz', 4, 'GoodAirlines');
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, czas_lotu, samolot, linia_lotnicza) VALUES ('Rzeszów', 'Monachium', '2020-11-21', '06:00', '1godz', 5, 'NOtGoodAirlines');
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, czas_lotu, samolot, linia_lotnicza) VALUES ('Monachium', 'Lizbona', '2020-11-21', '08:00', '3godz', 6, 'NOtGoodAirlines');

INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (1, 1);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (1, 3);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (1, 2);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (2, 1);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (2, 1);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (2, 4);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (3, 3);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (3, 2);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (4, 3);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 1);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 2);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (4, 4);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (5, 6);
INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (5, 7);
INSERT INTO osoby_rejsu (rejs, pasazer) VALUES (5, 3);

INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie, klasa, pierwszenstwo, posredni) VALUES (1, 1, 601, '17A', 'pierwsza', 0, 2);
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie, klasa, pierwszenstwo) VALUES (1, 2, 1560, '11B', 'pierwsza', 0);
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie, klasa, pierwszenstwo) VALUES (2, 3, 140, '53B', 'ekonomiczna', 0);
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie, klasa, pierwszenstwo, posredni) VALUES (3, 4, 140, '63E', 'ekonomiczna', 1, 5);
INSERT INTO bilety (pasazer, rejs, cena_biletu, miejsce_w_samolocie, klasa, pierwszenstwo) VALUES (3, 5, 140, '52C', 'ekonomiczna', 1);

DELIMITER //
CREATE PROCEDURE procedura1(IN zmienna varchar(50))
language sql
not deterministic
sql security invoker
BEGIN
    SELECT * FROM pasazerowie WHERE nazwisko = zmienna;
END;//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE procedura2()
BEGIN
	SET @x := '2020-11-20';
    SELECT miejsce_odlotu, miejsce_przylotu FROM rejsy WHERE data_odlotu= @x;
END;//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE procedura3(IN j INT, OUT ilosc INT)
BEGIN
    SELECT COUNT(*) INTO ilosc FROM rodzaj_samolotow WHERE ilosc_miejsc > j;
END;//
DELIMITER ;

CALL procedura1('Nowak');
CALL procedura2();
CALL procedura3(150, @ilosc);
SELECT @ilosc;