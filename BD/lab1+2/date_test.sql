USE BDBisnitar;
GO

-- date de test
INSERT INTO Marci (nume) VALUES
('BMW'), ('Audi'), ('Mercedes-Benz');

INSERT INTO Modele (id_marca, nume) VALUES
(1, 'Seria 3'), (1, 'X5'), (2, 'A4'), (3, 'C-Class');

INSERT INTO Bolizi (id_model, an_fabricatie, kilometraj, VIN) VALUES
(1, 2021, 65000, 'WBA8E9G50MNU12345'),
(2, 2019, 120000, 'WBAKS4C55K0D12345'),
(3, 2022, 45000, 'WAUZZZF42NA123456'),
(4, 2020, 85000, 'WDD2050401R123456'),
(1, 2023, 15000, 'WBA5R1C08PFT12345');

INSERT INTO Clienti (nume, telefon, email) VALUES
('Andrei Pop', '0711111111', 'andrei.pop@email.com'),
('Maria Ionescu', '0722222222', 'maria.ionescu@email.com'),
('Vlad Rusu', '0733333333', 'vlad.rusu@email.com');

INSERT INTO Samsari (nume, telefon, email) VALUES
('Auto Import SRL', '0744444444', 'contact@autoimport.ro'),
('Best Cars SRL', '0755555555', 'office@bestcars.ro');

INSERT INTO Achizitii (id_bolid, id_samsar, pret, data_achizitie) VALUES
(1, 1, 18000.00, '2024-03-12'),
(2, 2, 22000.00, '2024-06-20'),
(3, 1, 25000.00, '2025-02-10'),
(4, 2, 19500.00, '2024-09-05'),
(5, 1, 28000.00, '2025-05-18');

INSERT INTO Vanzari (id_bolid, id_client, pret, data_vanzare) VALUES
(1, 1, 22500.00, '2024-07-15'),
(2, 1, 27000.00, '2024-08-02'),
(4, 2, 24500.00, '2025-01-18');

INSERT INTO Negocieri (id_bolid, id_client, pret_cerut, oferta_primita, pret_final, data_negociere) VALUES
(1, 1, 23500.00, 22500.00, 22500.00, '2024-07-14'),
(2, 1, 28500.00, 27000.00, 27000.00, '2024-08-01'),
(3, 3, 31000.00, 28500.00, NULL, '2025-06-10'),
(4, 2, 25500.00, 24500.00, 24500.00, '2025-01-17');

INSERT INTO TipuriInvestitii (nume) VALUES
('Revizie'), ('Reparatie'), ('Detailing');

INSERT INTO Investitii (id_bolid, id_tip_investitie, detalii, cost, data_investitie) VALUES
(1, 1, 'Schimb ulei si filtre', 650.00, '2024-04-01'),
(2, 2, 'Inlocuire amortizoare', 1400.00, '2024-07-01'),
(3, 3, 'Polish exterior', 800.00, '2025-03-01'),
(4, 2, 'Reparatie cutie viteze', 2200.00, '2024-10-10'),
(5, 1, 'Revizie completa', 1200.00, '2025-06-01');

INSERT INTO Dotari (nume) VALUES
('Navigatie'), ('Piele'), ('Camera marsarier'), ('Scaune incalzite');

INSERT INTO BoliziDotari (id_bolid, id_dotare) VALUES
(1, 1), (1, 2), (2, 1), (2, 4), (3, 1), (3, 3), (3, 4), (4, 2), (5, 1), (5, 2), (5, 3);
GO
