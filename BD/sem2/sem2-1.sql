USE parcDistractii
GO

INSERT INTO categoriiVizitatori (nume) VALUES
('Copii'),
('Adolescenti'),
('Adulti'),
('Seniori'),
('Familii'),
('Studenti'),
('Turisti');

INSERT INTO vizitatori (id_categorie, nume, email) VALUES
(1, 'Andrei Pop', 'andrei.pop@email.com'),
(2, 'Maria Ionescu', 'maria.ionescu@email.com'),
(3, 'Vlad Georgescu', 'vlad.georgescu@email.com'),
(4, 'Elena Stan', 'elena.stan@email.com'),
(5, 'Ioana Dumitru', 'ioana.dumitru@email.com'),
(6, 'Radu Marin', 'radu.marin@email.com'),
(7, 'Ana Pavel', 'ana.pavel@email.com');

INSERT INTO sectiuni (nume, descriere) VALUES
('Aventura', 'Atractii pentru iubitorii de aventura.'),
('Distractie', 'Atractii distractive pentru toate varstele.'),
('Apa', 'Atractii acvatice si piscine.'),
('Copii', 'Atractii potrivite pentru copii.'),
('Adrenalina', 'Atractii pentru cei curajosi.'),
('Jocuri', 'Jocuri si activitati interactive.'),
('Familie', 'Atractii potrivite pentru intreaga familie.');

INSERT INTO atractii (id_sectiune, nume, descriere, varsta_minima_recomandata) VALUES
(1, 'Caruselul aventurii', 'O calatorie plina de aventura.', 8),
(2, 'Roata panoramica', 'O priveliste frumoasa asupra parcului.', 6),
(3, 'Toboganul acvatic', 'Un tobogan rapid si distractiv.', 10),
(4, 'Trenuletul copiilor', 'O plimbare relaxanta pentru copii.', 3),
(5, 'Roller coaster', 'Un roller coaster pentru iubitorii de adrenalina.', 12),
(6, 'Masinute electrice', 'O activitate interactiva pentru vizitatori.', 8),
(7, 'Casa misterioasa', 'O atractie pentru intreaga familie.', 7);

INSERT INTO atractiiVizitate (id_vizitator, id_atractie, nota) VALUES
(1, 1, 9.0),
(2, 2, 8.5),
(3, 3, 10.0),
(4, 4, 7.5),
(5, 5, 9.5),
(6, 6, 8.0),
(7, 7, 9.0);
