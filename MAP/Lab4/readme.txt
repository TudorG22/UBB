Alegeri pentru laboratorul 4

1. Fisiere: am pastrat Template Method. AbstractFileRepository se ocupa de citire si
scriere, iar UtilizatorFileRepository si PrietenieFileRepository definesc conversia
linie-entitate. Formatul fisierelor ramane acelasi.

2. Repository pastreaza contractul existent cu null pentru findOne, save, update
si delete. Optional este folosit in service pentru cautarea unui utilizator si
pentru rezultatele operatiilor pe stream. Astfel implementarile repository-ului
raman consecvente cu Javadoc-ul existent.
