USE BDBisnitar;
GO

-- Istoricul retine versiunile aplicate. Versiunea 0 este cea initiala.
IF OBJECT_ID('dbo.IstoricVersiuni', 'U') IS NULL
BEGIN
    CREATE TABLE IstoricVersiuni (numar INT PRIMARY KEY);
    INSERT INTO IstoricVersiuni VALUES (0);
END;
GO

-- Fiecare versiune noua are o procedura pentru aplicare si una pentru anulare.
IF OBJECT_ID('dbo.PasiVersiune', 'U') IS NULL
BEGIN
    CREATE TABLE PasiVersiune
    (
        numar INT PRIMARY KEY,
        procedura_aplicare VARCHAR(100),
        procedura_anulare VARCHAR(100)
    );
END;
GO

DROP PROCEDURE IF EXISTS SchimbaVersiunea;
DROP PROCEDURE IF EXISTS VinVarchar;
DROP PROCEDURE IF EXISTS VinChar;
DROP PROCEDURE IF EXISTS AdaugaDefault;
DROP PROCEDURE IF EXISTS StergeDefault;
DROP PROCEDURE IF EXISTS CreeazaRevizii;
DROP PROCEDURE IF EXISTS StergeRevizii;
DROP PROCEDURE IF EXISTS AdaugaDataRevizie;
DROP PROCEDURE IF EXISTS StergeDataRevizie;
DROP PROCEDURE IF EXISTS AdaugaCheieStraina;
DROP PROCEDURE IF EXISTS StergeCheieStraina;
GO

-- 0 -> 1: modifica tipul unei coloane.
CREATE PROCEDURE VinVarchar
AS
BEGIN
    ALTER TABLE Bolizi ALTER COLUMN VIN VARCHAR(17) NULL;
    INSERT INTO IstoricVersiuni VALUES (1);
END;
GO

-- 1 -> 0: revine la tipul initial.
CREATE PROCEDURE VinChar
AS
BEGIN
    ALTER TABLE Bolizi ALTER COLUMN VIN CHAR(17) NULL;
    DELETE FROM IstoricVersiuni WHERE numar = 1;
END;
GO

-- 1 -> 2: adauga o valoare implicita.
CREATE PROCEDURE AdaugaDefault
AS
BEGIN
    ALTER TABLE Bolizi
    ADD CONSTRAINT DF_Bolizi_Kilometraj DEFAULT 0 FOR kilometraj;
    INSERT INTO IstoricVersiuni VALUES (2);
END;
GO

-- 2 -> 1: sterge valoarea implicita.
CREATE PROCEDURE StergeDefault
AS
BEGIN
    ALTER TABLE Bolizi DROP CONSTRAINT DF_Bolizi_Kilometraj;
    DELETE FROM IstoricVersiuni WHERE numar = 2;
END;
GO

-- 2 -> 3: creeaza o tabela.
CREATE PROCEDURE CreeazaRevizii
AS
BEGIN
    CREATE TABLE Revizii
    (
        id_revizie INT PRIMARY KEY IDENTITY(1,1),
        id_bolid INT
    );
    INSERT INTO IstoricVersiuni VALUES (3);
END;
GO

-- 3 -> 2: sterge tabela.
CREATE PROCEDURE StergeRevizii
AS
BEGIN
    DROP TABLE Revizii;
    DELETE FROM IstoricVersiuni WHERE numar = 3;
END;
GO

-- 3 -> 4: adauga un camp.
CREATE PROCEDURE AdaugaDataRevizie
AS
BEGIN
    ALTER TABLE Revizii ADD data_revizie DATE;
    INSERT INTO IstoricVersiuni VALUES (4);
END;
GO

-- 4 -> 3: sterge campul.
CREATE PROCEDURE StergeDataRevizie
AS
BEGIN
    ALTER TABLE Revizii DROP COLUMN data_revizie;
    DELETE FROM IstoricVersiuni WHERE numar = 4;
END;
GO

-- 4 -> 5: creeaza o cheie straina.
CREATE PROCEDURE AdaugaCheieStraina
AS
BEGIN
    ALTER TABLE Revizii
    ADD CONSTRAINT FK_Revizii_Bolizi
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid);
    INSERT INTO IstoricVersiuni VALUES (5);
END;
GO

-- 5 -> 4: sterge cheia straina.
CREATE PROCEDURE StergeCheieStraina
AS
BEGIN
    ALTER TABLE Revizii DROP CONSTRAINT FK_Revizii_Bolizi;
    DELETE FROM IstoricVersiuni WHERE numar = 5;
END;
GO

IF NOT EXISTS (SELECT 1 FROM PasiVersiune WHERE numar = 1)
    INSERT INTO PasiVersiune VALUES (1, 'VinVarchar', 'VinChar');
IF NOT EXISTS (SELECT 1 FROM PasiVersiune WHERE numar = 2)
    INSERT INTO PasiVersiune VALUES (2, 'AdaugaDefault', 'StergeDefault');
IF NOT EXISTS (SELECT 1 FROM PasiVersiune WHERE numar = 3)
    INSERT INTO PasiVersiune VALUES (3, 'CreeazaRevizii', 'StergeRevizii');
IF NOT EXISTS (SELECT 1 FROM PasiVersiune WHERE numar = 4)
    INSERT INTO PasiVersiune VALUES (4, 'AdaugaDataRevizie', 'StergeDataRevizie');
IF NOT EXISTS (SELECT 1 FROM PasiVersiune WHERE numar = 5)
    INSERT INTO PasiVersiune VALUES (5, 'AdaugaCheieStraina', 'StergeCheieStraina');
GO

-- Apeleaza procedurile necesare pana la versiunea ceruta.
CREATE PROCEDURE SchimbaVersiunea @versiune INT
AS
BEGIN
    IF @versiune IS NULL OR @versiune < 0 OR
       @versiune > (SELECT MAX(numar) FROM PasiVersiune)
    BEGIN
        RAISERROR('Versiune necunoscuta.', 16, 1);
        RETURN;
    END;

    DECLARE @curenta INT;
    DECLARE @procedura VARCHAR(100);
    SELECT @curenta = MAX(numar) FROM IstoricVersiuni;

    WHILE @curenta < @versiune
    BEGIN
        SET @procedura = (SELECT procedura_aplicare FROM PasiVersiune
                         WHERE numar = @curenta + 1);
        IF @procedura IS NULL
        BEGIN
            RAISERROR('Lipseste un pas de versiune.', 16, 1);
            RETURN;
        END;
        EXEC @procedura;
        SET @curenta = @curenta + 1;
    END;

    WHILE @curenta > @versiune
    BEGIN
        SET @procedura = (SELECT procedura_anulare FROM PasiVersiune
                         WHERE numar = @curenta);
        IF @procedura IS NULL
        BEGIN
            RAISERROR('Lipseste un pas de versiune.', 16, 1);
            RETURN;
        END;
        EXEC @procedura;
        SET @curenta = @curenta - 1;
    END;
END;
GO


