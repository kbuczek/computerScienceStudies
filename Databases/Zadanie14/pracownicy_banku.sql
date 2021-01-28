-- DROP database pracownicy_banku;-- 

create database pracownicy_banku;
use pracownicy_banku;

create table pracownicy ( 
    lp int not null auto_increment, 
    imie varchar(50) not null, 
    nazwisko varchar(100) not null, 
    pesel int not null,
    telefon int not null,
    email varchar(100) not null,
    primary key(lp) 
);

create table rodzaj_stanowisk ( 
    lp int not null auto_increment,
    nazwa varchar(50) not null,
    podstawowy_czas_pracy int not null,
    primary key(lp)
); 

create table stanowiska ( 
    lp int not null auto_increment, 
    pracownik int not null, 
	rodzaj_stanowiska int not null, 
	wysokosc_wynagrodzenia int not null,
    primary key(lp),
    foreign key(pracownik) references pracownicy(lp),
	foreign key(rodzaj_stanowiska) references rodzaj_stanowisk(lp)
);

create table historia_pracy ( 
    lp int not null auto_increment, 
	stanowisko int not null,
    miesiac varchar(50) not null,
	rok int not null,
    liczba_przepracowanych_godzin int,
    primary key(lp),
	foreign key(stanowisko) references stanowiska(lp)
); 

INSERT INTO pracownicy (imie, nazwisko, pesel, telefon, email) VALUES ('Maciej', 'Koczylas', 1244343241, 234324232, 'maciej.koczylas@email.com');
INSERT INTO pracownicy (imie, nazwisko, pesel, telefon, email) VALUES ('Anna', 'Nowak', 213839248, 12390343, 'annanowak@email.com');
INSERT INTO pracownicy (imie, nazwisko, pesel, telefon, email) VALUES ('Krzysztof', 'Buk', 89324820, 123034922, 'buk.krzysztof@email.com');
INSERT INTO pracownicy (imie, nazwisko, pesel, telefon, email) VALUES ('Andrzej', 'Giewont', 342342393, 321938933, 'andrzejgiewont@email.com');

INSERT INTO rodzaj_stanowisk (nazwa, podstawowy_czas_pracy) VALUES ('Kasjer', 160);
INSERT INTO rodzaj_stanowisk (nazwa, podstawowy_czas_pracy) VALUES ('Obsługa klienta', 120);
INSERT INTO rodzaj_stanowisk (nazwa, podstawowy_czas_pracy) VALUES ('Doradca Finansowy', 160);

INSERT INTO stanowiska (pracownik, rodzaj_stanowiska, wysokosc_wynagrodzenia) VALUES (1, 1, 1999);
INSERT INTO stanowiska (pracownik, rodzaj_stanowiska, wysokosc_wynagrodzenia) VALUES (2, 1, 1850);
INSERT INTO stanowiska (pracownik, rodzaj_stanowiska, wysokosc_wynagrodzenia) VALUES (3, 2, 1720);
INSERT INTO stanowiska (pracownik, rodzaj_stanowiska, wysokosc_wynagrodzenia) VALUES (4, 3, 9460);

INSERT INTO historia_pracy (stanowisko, miesiac, rok, liczba_przepracowanych_godzin) VALUES (1, 'grudzień', 2020, 161);
INSERT INTO historia_pracy (stanowisko, miesiac, rok, liczba_przepracowanych_godzin) VALUES (2, 'grudzień', 2020, 180);
INSERT INTO historia_pracy (stanowisko, miesiac, rok, liczba_przepracowanych_godzin) VALUES (3, 'grudzień', 2020, 132);
INSERT INTO historia_pracy (stanowisko, miesiac, rok, liczba_przepracowanych_godzin) VALUES (4, 'grudzień', 2020, 196);

DELIMITER //
CREATE PROCEDURE podnies_pensje(IN procenty DOUBLE, podwyzka INT)
BEGIN
	DECLARE i INT DEFAULT 1;
    SET @i = 1;
    SET @procent_godzin = (procenty + 100)/100;
	START TRANSACTION;
	petla: LOOP
        SET @wysokosc_wynagrodzenia = 0;
        SET @ilosc_przepracowanych_godzin = 0;
        SET @podstawowy_czas_pracy = 0;
        SELECT wysokosc_wynagrodzenia INTO @wysokosc_wynagrodzenia FROM stanowiska WHERE lp = @i;
		SELECT liczba_przepracowanych_godzin INTO @ilosc_przepracowanych_godzin FROM historia_pracy WHERE stanowisko = @i;
        SELECT podstawowy_czas_pracy INTO @podstawowy_czas_pracy FROM rodzaj_stanowisk WHERE lp = (SELECT rodzaj_stanowiska FROM stanowiska WHERE lp = @i);

        IF ((@ilosc_przepracowanych_godzin >= (@podstawowy_czas_pracy * @procent_godzin)) AND (@wysokosc_wynagrodzenia < 2000))
        THEN
			UPDATE stanowiska SET wysokosc_wynagrodzenia = wysokosc_wynagrodzenia + podwyzka WHERE lp = @i;
		END IF;
		SET @i = @i + 1;
		IF @i > (SELECT COUNT(*) FROM stanowiska) THEN LEAVE petla; END IF;
		END LOOP;
    COMMIT;
END;//
DELIMITER ;

CALL podnies_pensje(10, 50);