CREATE DATABASE BDBisnitar;
GO

USE BDBisnitar;
GO

CREATE TABLE Marci
(
    id_marca INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(50)  
);

CREATE TABLE Modele
(
    id_model INT PRIMARY KEY IDENTITY(1,1),
    id_marca INT,
    nume VARCHAR(50),
    FOREIGN KEY (id_marca) REFERENCES Marci(id_marca)
);

CREATE TABLE Bolizi
(
    id_bolid INT PRIMARY KEY IDENTITY(1,1),
    id_model INT,
    an_fabricatie SMALLINT,
    kilometraj INT,
    VIN CHAR(17),
    FOREIGN KEY (id_model) REFERENCES Modele(id_model)
);

CREATE TABLE Clienti
(
    id_client INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100),
    telefon VARCHAR(30),
    email VARCHAR(100)
);

CREATE TABLE Samsari
(
    id_samsar INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100),
    telefon VARCHAR(30),
    email VARCHAR(100)
);

CREATE TABLE Achizitii
(
    id_achizitie INT PRIMARY KEY IDENTITY(1,1),
    id_bolid INT,
    id_samsar INT,
    pret DECIMAL(12,2),
    data_achizitie DATE,
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid),
    FOREIGN KEY (id_samsar) REFERENCES Samsari(id_samsar)
);

CREATE TABLE Vanzari
(
    id_vanzare INT PRIMARY KEY IDENTITY(1,1),
    id_bolid INT,
    id_client INT,
    pret DECIMAL(12,2),
    data_vanzare DATE,
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid),
    FOREIGN KEY (id_client) REFERENCES Clienti(id_client)
);

CREATE TABLE Negocieri
(
    id_negociere INT PRIMARY KEY IDENTITY(1,1),
    id_bolid INT,
    id_client INT,
    pret_cerut DECIMAL(12,2),
    oferta_primita DECIMAL(12,2),
    pret_final DECIMAL(12,2),
    data_negociere DATE,
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid),
    FOREIGN KEY (id_client) REFERENCES Clienti(id_client)
);

CREATE TABLE TipuriInvestitii
(
    id_tip_investitie INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(50)  
);

CREATE TABLE Investitii
(
    id_investitie INT PRIMARY KEY IDENTITY(1,1),
    id_bolid INT,
    id_tip_investitie INT,
    detalii VARCHAR(300),
    cost DECIMAL(12,2),
    data_investitie DATE,
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid),
    FOREIGN KEY (id_tip_investitie) REFERENCES TipuriInvestitii(id_tip_investitie)
);

CREATE TABLE Dotari
(
    id_dotare INT PRIMARY KEY IDENTITY(1,1),
    nume VARCHAR(100)  
);

CREATE TABLE BoliziDotari
(
    id_bolid INT,
    id_dotare INT,
    PRIMARY KEY (id_bolid, id_dotare),
    FOREIGN KEY (id_bolid) REFERENCES Bolizi(id_bolid),
    FOREIGN KEY (id_dotare) REFERENCES Dotari(id_dotare)
);
GO

