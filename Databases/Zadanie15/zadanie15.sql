create database gwiazdy_i_planety;
use gwiazdy_i_planety;

create table gwiazdy ( 
    lp int not null auto_increment, 
    nazwa varchar(100) not null, 
    promien int not null,
    klasa varchar(1) not null,
    data_wprowadzenia datetime,
    data_modyfikacji datetime,
    czy_usunieta int,
    primary key(lp) 
);

create table planety( 
    lp int not null auto_increment, 
	nazwa varchar(100) not null,
	promien int not null, 
	klasa varchar(1) not null,
    najblizsza_gwiazda int not null,
	data_wprowadzenia datetime,
    data_modyfikacji datetime,
    czy_usunieta int,
    primary key(lp),
    foreign key(najblizsza_gwiazda) references gwiazdy(lp)
);

DELIMITER //
CREATE TRIGGER data_wprowadzenia_gwiazdy
BEFORE INSERT ON gwiazdy
FOR EACH ROW
BEGIN
	SET NEW.data_wprowadzenia = now();
    SET NEW.data_modyfikacji = now(); 
END //
DELIMITER ;

DELIMITER //
CREATE TRIGGER data_wprowadzenia_planety
BEFORE INSERT ON planety
FOR EACH ROW
BEGIN
	SET NEW.data_wprowadzenia = now();
    SET NEW.data_modyfikacji = now(); 
END //
DELIMITER ;

INSERT INTO gwiazdy (nazwa, promien, klasa) VALUES ('A122', 20, 'A');
INSERT INTO gwiazdy (nazwa, promien, klasa) VALUES ('A122', 20, 'A');
INSERT INTO gwiazdy (nazwa, promien, klasa) VALUES ('C3-P0', 4000, 'C');
INSERT INTO planety (nazwa, promien, klasa, najblizsza_gwiazda) VALUES ('Pirx', 5, 'D', 1);
INSERT INTO planety (nazwa, promien, klasa, najblizsza_gwiazda) VALUES ('Centauri', 2, 'G', 2);

DELIMITER //
CREATE TRIGGER data_modyfikacji_gwiazdy
BEFORE UPDATE ON gwiazdy
FOR EACH ROW
BEGIN
    SET NEW.data_modyfikacji = now(); 
END //
DELIMITER ;

DELIMITER //
CREATE TRIGGER data_modyfikacji_planety
BEFORE UPDATE ON planety
FOR EACH ROW
BEGIN
    SET NEW.data_modyfikacji = now(); 
END //
DELIMITER ;

UPDATE gwiazdy SET nazwa = 'B212' WHERE lp = 1;
UPDATE planety SET nazwa = 'Zeus' WHERE lp = 2;

DELIMITER //
CREATE TRIGGER usuniecie_gwiazdy
INSTEAD OF DELETE ON gwiazdy
FOR EACH ROW
BEGIN
	UPDATE gwiazdy SET czy_usunieta = 1 WHERE lp = OLD.lp;
END //
DELIMITER ;

DELIMITER //
CREATE TRIGGER usuniecie_planety
INSTEAD OF DELETE ON planety
FOR EACH ROW
BEGIN
	UPDATE planety SET czy_usunieta = 1 WHERE lp = OLD.lp;
END //
DELIMITER ;

DELETE FROM planety WHERE lp = 1;
DELETE FROM gwiazdy WHERE lp = 3;
