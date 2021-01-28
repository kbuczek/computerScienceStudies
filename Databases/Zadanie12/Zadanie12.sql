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
    zasieg int not null,
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
    samolot int,
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
    primary key(lp)
);

ALTER TABLE rodzaj_samolotow ADD cargo int not null;
ALTER TABLE rejsy ADD czas_lotu varchar(50);
ALTER TABLE rejsy ADD linia_lotnicza varchar(100) not null;
ALTER TABLE rejsy ADD zasieg int not null;

INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, zasieg, cargo) VALUES ('wąskokadłubowy', 'Boeing', '737', 1979, 400, 10000, 10);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, zasieg, cargo) VALUES ('szerokokadłubowy', 'Airbus', 'Dreamliner', 2019, 350, 8000, 8);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, zasieg, cargo) VALUES ('szerokokadłubowy', 'Cessna', 'Avito 7', 2011, 200, 6000, 5);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, zasieg, cargo) VALUES ('wąskokadłubowy', 'Boeing', '789', 2005, 100, 1500, 2);
INSERT INTO rodzaj_samolotow (typ, firma, model, rok_produkcji, ilosc_miejsc, zasieg, cargo) VALUES ('wąskokadłubowy', 'Militech', 'Destiny', 2020, 140, 3000, 4);

DELIMITER //
CREATE PROCEDURE dodajSamolot( IN rodzajSamolotu INT, IN numerSeryjny varchar(100), IN dataPrzegladu date, IN CzyUsunietyZFloty INT)
BEGIN
	INSERT INTO samoloty (rodzaj_samolotu, numer_seryjny, data_przegladu, czy_usuniety_z_floty) VALUES (rodzajSamolotu, numerSeryjny, dataPrzegladu, CzyUsunietyZFloty);
END;//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE dodajPasazera( IN imiePasazera varchar(50), IN nazwiskoPasazera varchar(100), IN numerPaszportuPasazera INT, IN telefonPasazera INT, IN emailPasazera VARCHAR(100))
BEGIN
INSERT INTO pasazerowie (imie, nazwisko, nr_paszportu, telefon, email) VALUES (imiePasazera, nazwiskoPasazera, numerPaszportuPasazera, telefonPasazera, emailPasazera);
END;//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE dodajZaloge( IN imieZalogi varchar(50), IN nazwiskoZalogi varchar(100), IN pilotZaloga INT, IN stewardessaZaloga INT, IN nrLicencjiZaloga INT)
BEGIN
INSERT INTO zaloga (imie, nazwisko, pilot, stewardessa, nr_licencji) VALUES (imieZalogi, nazwiskoZalogi, pilotZaloga, stewardessaZaloga, nrLicencjiZaloga);
END;//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE dodajRejs( IN miejsceOdlotuRejsu varchar(50), IN miejscePrzylotuRejsu varchar(50), IN dataOdlotuRejsu date, IN godzinaOdlotuRejscu varchar(5), IN samolotRejsu INT, IN czasLotuRejsu varchar(50), IN liniaLotniczaRejsu varchar(100), IN zasiegRejsu INT)
BEGIN
INSERT INTO rejsy (miejsce_odlotu, miejsce_przylotu, data_odlotu, godzina_odlotu, samolot, czas_lotu, linia_lotnicza, zasieg) VALUES (miejsceOdlotuRejsu , miejscePrzylotuRejsu, dataOdlotuRejsu, godzinaOdlotuRejscu, samolotRejsu, czasLotuRejsu, liniaLotniczaRejsu, zasiegRejsu);
END;//
DELIMITER ;

CALL dodajSamolot(1, 'SSY-1243-5423', '2010-10-10', 0);
CALL dodajSamolot(2, 'ABB-6345-4251', '2020-11-13', 0);
CALL dodajSamolot(4, 'HGY-234735-53', '2020-11-20', 0);

CALL dodajPasazera('Anna', 'Nowak', 314234123, 340234831, 'annanowak@email.com');
CALL dodajPasazera('Jan', 'Kowalski', 598123809, 123123809, 'jankowalski@outlook.com');
CALL dodajPasazera('Piotr', 'Kwiatkowski', 231234144, 123123870, 'piotrkwiatkowski@wp.pl');
CALL dodajPasazera('Artur', 'Nowacki', 143532953, 558394234, 'arturnowacki@email.com');
CALL dodajPasazera('Agnieszka', 'Babek', 582104258, 14834112, 'agnieszkababek@email.com');
CALL dodajPasazera('Bartłomiej', 'Magala', 235041493, 509234234, 'bartekmagala@email.com');
CALL dodajPasazera('Chris', 'Hemlock', 21049343, 23139041, 'chrishemlock@email.com');
CALL dodajPasazera('Artur', 'Michałek', 294482183, 948214480, 'arturmichalek@email.com');
CALL dodajPasazera('Julia', 'Krawiec', 592910583, 391084385, 'juliakrawiec@email.com');
CALL dodajPasazera('Judy', 'Foster', 394132892, 138098122, 'judyfoster@email.com');
CALL dodajPasazera('Panam', 'Buzek', 491923813, 191482194, 'panambuzek@email.com');
CALL dodajPasazera('Johnny', 'Silverhand', 999812312, 082384161, 'johnnysilverhand@email.com');
CALL dodajPasazera('Master', 'Chief', 438423809, 123830583, 'masterchief@live.com');
CALL dodajPasazera('Trevor', 'Rockstar', 493953102, 534182798, 'trevor@rockstar.com');
CALL dodajPasazera('Angelika', 'Dżastin', 384193812, 592028182, 'andzelaaaaa@email.com');

CALL dodajZaloge('Arkadiusz', 'Maćkowski', 1, 0, 324232312);
CALL dodajZaloge('Filip', 'Magnet', 0, 1, 1323451);
CALL dodajZaloge('Zofia', 'Bober', 1, 0, 847125351);
CALL dodajZaloge('Halina', 'Zorzyk', 0, 1, 2358041);
CALL dodajZaloge('Maciej', 'Andrus', 1, 0, 1238034);
CALL dodajZaloge('Błażej', 'Jok', 0, 1, 1980248);
CALL dodajZaloge('Marcin', 'Golec', 1, 0, 123898433);
CALL dodajZaloge('Małgorzata', 'Ziele', 0, 1, 12344455);


CALL dodajRejs('Kraków', 'Chicago', '2020-11-20', '01:00', 0, '12godz', 'GoodAirlines', 8321);
CALL dodajRejs('Kostaryka', 'Melbourne', '2020-11-22', '11:00', 0, '10godz', 'FlyWell Airlines', 6913);
CALL dodajRejs('Warszawa', 'Frankfurt', '2020-11-20', '15:00', 0, '40min', 'FlyWell Airlines', 534);

DELIMITER //
CREATE PROCEDURE a(IN samolotA INT, IN rejsA INT)
BEGIN
	SET @zasiegSamolotu = (SELECT zasieg FROM rodzaj_samolotow WHERE lp = (SELECT rodzaj_samolotu FROM samoloty WHERE lp = samolotA));
	SET @zasiegRejsu = (SELECT zasieg FROM rejsy WHERE lp = rejsA);

	IF @zasiegSamolotu > @zasiegRejsu THEN
		UPDATE rejsy SET samolot = samolotA WHERE lp = rejsA;
		END IF;
    
    SELECT * FROM rejsy;
END; //
DELIMITER ;

CALL a(3, 1);
CALL a(1, 1);

-- DELIMITER //
-- CREATE PROCEDURE aSamolotyDoRejsow()
-- BEGIN
-- 	SET @i = (SELECT COUNT(*) FROM rejsy);
--     petla: LOOP
-- 		petlaPilotow: LOOP
-- 			IF (SELECT samolot FROM rejsy WHERE lp = @i) > 0 THEN 
-- 				CALL a(,@i);
-- 			END IF;
--         END LOOP;
-- 		IF @i < 1 THEN LEAVE petla; END IF;
--         SET @i = @i-1;
--     END LOOP;
--     SELECT * FROM rejsy;
-- END; //
-- DELIMITER ;


DELIMITER //
CREATE PROCEDURE b(IN rejsB INT, IN zalogaB INT)
BEGIN
	DECLARE i INT DEFAULT 0;  
	SET @zasiegRejsu = (SELECT zasieg FROM rejsy WHERE lp = rejsB);
	IF @zasiegRejsu > 5000 THEN
		REPEAT
			INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (rejsB, zalogaB);
			SET i = i + 1000;
            SET zalogaB = zalogaB + 1;
		UNTIL i > @zasiegRejsu END REPEAT;
	END IF;
    SELECT * FROM osoby_rejsu;
END; //
DELIMITER ;

CALL b(2, 1);

DELIMITER //
CREATE PROCEDURE c(IN rejsC INT, IN pilotC INT)
BEGIN
	SET @zasiegRejsu = (SELECT zasieg FROM rejsy WHERE lp = rejsC);
    SET @czyPilot = (SELECT pilot FROM zaloga WHERE lp = pilotC);

	IF @zasiegRejsu > 7000 AND @czyPilot = 1 THEN
		INSERT INTO osoby_rejsu (rejs, zaloga) VALUES (rejsC, pilotC);
		END IF;
    
    SELECT * FROM osoby_rejsu;
END; //
DELIMITER ;

CALL c(2, 1);
CALL c(1, 1);

DELIMITER //
CREATE PROCEDURE d()
BEGIN
    DECLARE i INT DEFAULT 1; 
	DECLARE j INT DEFAULT 1;
    DECLARE pasazerZmienna INT DEFAULT 1;
	SET @iloscRejsow = (SELECT COUNT(*) FROM rejsy);
    SET @iloscPasazerow = (SELECT COUNT(*) FROM pasazerowie);
	SET @iloscBiletow = (@iloscPasazerow / @iloscRejsow);
	REPEAT
		SET j = 1;
		REPEAT
			INSERT INTO bilety (pasazer, rejs) VALUES (pasazerZmienna, i);
			SET j = j + 1;
            SET pasazerZmienna = pasazerZmienna + 1;
        UNTIL j > @iloscBiletow END REPEAT;
		SET i = i + 1;
	UNTIL i > @iloscRejsow END REPEAT;
        
    SELECT pasazer, rejs FROM bilety;
END; //
DELIMITER ;

CALL d();
