USE parcDistractii;
GO

DROP PROCEDURE IF EXISTS AdaugaConstrangereDefault;
DROP PROCEDURE IF EXISTS ReturneazaAtractiiCuVarstaMin;
GO

CREATE PROCEDURE AdaugaConstrangereDefault
AS
BEGIN
ALTER TABLE Atractii
ADD CONSTRAINT df_varsta_min DEFAULT 12 FOR varsta_minima_recomandata
END;
GO

CREATE PROCEDURE ReturneazaAtractiiCuVarstaMin @varsta_min INT 
AS
BEGIN
SELECT nume, descriere, varsta_minima_recomandata FROM atractii 
WHERE varsta_minima_recomandata=@varsta_min;
END;
GO

--------------------------------------------

EXEC AdaugaConstrangereDefault;
EXEC ReturneazaAtractiiCuVarstaMin 12;