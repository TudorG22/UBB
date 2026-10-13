CREATE DATABASE parcDistractii
GO

USE parcDistractii

CREATE TABLE categoriiVizitatori (
    id_categorie INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(50)
);

CREATE TABLE vizitatori (
    id_vizitator INT PRIMARY KEY IDENTITY(1,1),
    id_categorie INT NOT NULL,
    nume VARCHAR(100),
    email varchar(100),
    FOREIGN KEY (id_categorie) REFERENCES categoriiVizitatori(id_categorie)
);

CREATE TABLE sectiuni (
    id_sectiune INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100),
    descriere VARCHAR(300)
);

CREATE TABLE atractii (
    id_atractie INT PRIMARY KEY IDENTITY(1,1),
    id_sectiune INT NOT NULL,
    nume VARCHAR(100),
    descriere VARCHAR(300),
    varsta_minima_recomandata INT,
    FOREIGN KEY (id_sectiune) REFERENCES sectiuni(id_sectiune)
);

CREATE TABLE atractiiVizitate (
    id_vizitator INT,
    id_atractie INT,
    nota DECIMAL(3,1),
    CONSTRAINT CK_nota CHECK (nota BETWEEN 0 AND 10),
    PRIMARY KEY (id_vizitator, id_atractie),
    FOREIGN KEY (id_vizitator) REFERENCES vizitatori(id_vizitator),
    FOREIGN KEY (id_atractie) REFERENCES atractii(id_atractie)
);