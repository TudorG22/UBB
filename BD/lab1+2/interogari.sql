use bdbisnitar;
go

----------- interogari cu where

-- bolizi disponibili pentru vanzare
select b.id_bolid, m.nume as marca, mo.nume as model,
       b.an_fabricatie, b.kilometraj, b.vin
from bolizi b
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
where not exists (
    select 1
    from vanzari v
    where v.id_bolid = b.id_bolid
);

-- bolizi fabricati dupa 2020 cu kilometraj redus
select b.id_bolid, b.an_fabricatie, b.kilometraj, b.vin
from bolizi b
where b.an_fabricatie >= 2020
  and b.kilometraj < 100000;

-- negocieri cu oferta sub pretul cerut
select n.id_negociere, c.nume as client, n.pret_cerut,
       n.oferta_primita, n.data_negociere
from negocieri n
join clienti c on c.id_client = n.id_client
where n.oferta_primita < n.pret_cerut;

-- investitii costisitoare dupa 2024
select i.id_investitie, ti.nume as tip_investitie,
       i.detalii, i.cost, i.data_investitie
from investitii i
join tipuriinvestitii ti on ti.id_tip_investitie = i.id_tip_investitie
where i.cost > 1000
  and i.data_investitie >= '2024-01-01';

-- achizitii efectuate in 2024
select a.id_achizitie, s.nume as samsar, a.id_bolid,
       a.pret, a.data_achizitie
from achizitii a
join samsari s on s.id_samsar = a.id_samsar
where a.data_achizitie between '2024-01-01' and '2024-12-31';


----------- interogari cu group by

-- vanzari pentru fiecare luna
select year(data_vanzare) as an, month(data_vanzare) as luna,
       count(*) as numar_vanzari, sum(pret) as valoare_totala
from vanzari
group by year(data_vanzare), month(data_vanzare)
order by an, luna;

-- costul investitiilor dupa tip
select ti.nume as tip_investitie, count(*) as numar_investitii,
       sum(i.cost) as cost_total, avg(i.cost) as cost_mediu
from investitii i
join tipuriinvestitii ti on ti.id_tip_investitie = i.id_tip_investitie
group by ti.nume;

-- cheltuiala fiecarui client
select c.id_client, c.nume as client, count(v.id_vanzare) as numar_bolizi,
       sum(v.pret) as suma_cheltuita
from clienti c
join vanzari v on v.id_client = c.id_client
group by c.id_client, c.nume;


----------- interogari cu distinct

-- marci cu bolizi vanduti
select distinct m.nume as marca
from marci m
join modele mo on mo.id_marca = m.id_marca
join bolizi b on b.id_model = mo.id_model
join vanzari v on v.id_bolid = b.id_bolid
order by marca;

-- dotari ale bolizilor disponibili
select distinct d.nume as dotare
from dotari d
join bolizidotari bd on bd.id_dotare = d.id_dotare
join bolizi b on b.id_bolid = bd.id_bolid
where not exists (
    select 1 from vanzari v where v.id_bolid = b.id_bolid
)
order by dotare;


----------- interogari cu having

-- clienti care au cumparat mai multi bolizi
select c.id_client, c.nume as client, count(v.id_vanzare) as numar_bolizi,
       sum(v.pret) as suma_cheltuita
from clienti c
join vanzari v on v.id_client = c.id_client
group by c.id_client, c.nume
having count(v.id_vanzare) > 1;

-- tipuri de investitii cu cost mediu mare
select ti.nume as tip_investitie, avg(i.cost) as cost_mediu
from tipuriinvestitii ti
join investitii i on i.id_tip_investitie = ti.id_tip_investitie
group by ti.nume
having avg(i.cost) > 500;


----------- interogari cu mai mult de doua tabele

-- detalii despre bolizii vanduti si cumparatori
select v.id_vanzare, m.nume as marca, mo.nume as model,
       b.an_fabricatie, b.kilometraj, c.nume as client,
       v.pret as pret_vanzare, v.data_vanzare
from vanzari v
join bolizi b on b.id_bolid = v.id_bolid
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
join clienti c on c.id_client = v.id_client;

-- profitul estimat pentru fiecare bolid vandut
select b.id_bolid, m.nume as marca, mo.nume as model,
       a.pret as pret_achizitie, v.pret as pret_vanzare,
       isnull(inv.cost_total, 0) as cost_investitii,
       v.pret - a.pret - isnull(inv.cost_total, 0) as profit_estimat
from bolizi b
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
join achizitii a on a.id_bolid = b.id_bolid
join vanzari v on v.id_bolid = b.id_bolid
left join (
    select id_bolid, sum(cost) as cost_total
    from investitii
    group by id_bolid
) inv on inv.id_bolid = b.id_bolid;

-- istoricul negocierilor
select n.id_negociere, c.nume as client, m.nume as marca,
       mo.nume as model, b.vin, n.pret_cerut,
       n.oferta_primita, n.pret_final, n.data_negociere
from negocieri n
join clienti c on c.id_client = n.id_client
join bolizi b on b.id_bolid = n.id_bolid
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca;

-- dotarile bolizilor disponibili
select b.id_bolid, m.nume as marca, mo.nume as model, d.nume as dotare
from bolizi b
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
join bolizidotari bd on bd.id_bolid = b.id_bolid
join dotari d on d.id_dotare = bd.id_dotare
where not exists (
    select 1 from vanzari v where v.id_bolid = b.id_bolid
)
order by b.id_bolid, d.nume;

-- numarul de dotari pentru fiecare bolid
select b.id_bolid, m.nume as marca, mo.nume as model,
       count(bd.id_dotare) as numar_dotari
from bolizi b
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
left join bolizidotari bd on bd.id_bolid = b.id_bolid
group by b.id_bolid, m.nume, mo.nume
order by numar_dotari desc;

-- negocieri finalizate
select c.nume as client, m.nume as marca, mo.nume as model,
       n.pret_final, n.data_negociere
from clienti c
join negocieri n on n.id_client = c.id_client
join bolizi b on b.id_bolid = n.id_bolid
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca
where n.pret_final is not null;

-- provenienta bolizilor
select a.id_achizitie, s.nume as samsar, m.nume as marca,
       mo.nume as model, b.vin, a.pret as pret_achizitie,
       a.data_achizitie
from achizitii a
join samsari s on s.id_samsar = a.id_samsar
join bolizi b on b.id_bolid = a.id_bolid
join modele mo on mo.id_model = b.id_model
join marci m on m.id_marca = mo.id_marca;
