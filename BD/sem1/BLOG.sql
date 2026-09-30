CREATE DATABASE Blog222;
GO
USE Blog222;

CREATE TABLE Utilizator
(cod_u INT PRIMARY KEY IDENTITY(1,1),
nume_utilizator VARCHAR(100),
email VARCHAR(100) UNIQUE,
parola NVARCHAR(100)
);

CREATE TABLE Articole
(cod_a INT PRIMARY KEY IDENTITY,
titlu VARCHAR(300) NOT NULL,
continut VARCHAR(MAX),
data_publicarii DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizator(cod_u)
);

CREATE TABLE Comentarii
(cod_c INT PRIMARY KEY IDENTITY,
continut VARCHAR(400),
data_comentariului DATETIME,
cod_u INT FOREIGN KEY REFERENCES Utilizator(cod_u),
cod_a INT FOREIGN KEY REFERENCES Articole(cod_a)
);

CREATE TABLE CuvinteCheie
(cod_cc INT PRIMARY KEY IDENTITY,
nume VARCHAR(50)
);

CREATE TABLE ArticoleCuvinteCheie
(cod_a INT FOREIGN KEY REFERENCES Articole(cod_a),
cod_cc INT FOREIGN KEY REFERENCES CuvinteCheie(cod_cc),
CONSTRAINT pk_ArticoleCuvinteCheie PRIMARY KEY (cod_a, cod_cc)
);
