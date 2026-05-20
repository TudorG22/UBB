#pragma once

#include <iostream>
#include <string>

using std::string;

class Carte {
    private:
        int isbn;
        string titlu;
        string autor;
        string gen;
        int pret;
        int stoc;

    public:
        Carte() = default;

        /* Construieste o carte
        Input: isbn, titlu, autor, gen, pret, stoc
        Output: -
        Pre conditii: valorile primite pot descrie corect o carte
        Post conditii: obiectul carte este initializat
        */
        Carte(int isbn, const string& titlu, const string& autor, const string& gen, int pret, int stoc);

        /* Creeaza o copie a unei carti
        Input: alta carte
        Output: -
        Pre conditii: carte initializata
        Post conditii: carte copiata
        
        Carte(const Carte& other);

        Carte(Carte&& other) noexcept = default;
        Carte& operator=(const Carte& other) = default;
        Carte& operator=(Carte&& other) noexcept = default;*/

        /* Ofera isbn-ul cartii
        Input: -
        Output: isbn-ul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        int getIsbn() const;
        /* Modifica isbn-ul cartii
        Input: isbnNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: isbn-ul este schimbat
        */
        void setIsbn(int isbnNou);

        /* Ofera titlul cartii
        Input: -
        Output: titlul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        const string& getTitlu() const;
        /* Modifica titlul cartii
        Input: titluNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: titlul este actualizat
        */
        void setTitlu(const string& titluNou);

        /* Ofera autorul cartii
        Input: -
        Output: autorul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        const string& getAutor() const;
        /* Modifica autorul cartii
        Input: autorNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: autorul este actualizat
        */
        void setAutor(const string& autorNou);

        /* Ofera genul cartii
        Input: -
        Output: genul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        const string& getGen() const;

        /* Modifica genul cartii
        Input: genNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: genul este actualizat
        */
        void setGen(const string& genNou);

        /* Ofera pretul cartii
        Input: -
        Output: pretul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        int getPret() const;
        /* Modifica pretul cartii
        Input: pretNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: pretul este actualizat
        */
        void setPret(int pretNou);

        /* Ofera stocul cartii
        Input: -
        Output: stocul cartii
        Pre conditii: obiectul carte exista
        Post conditii: -
        */
        int getStoc() const;
        /* Modifica stocul cartii
        Input: stocNou
        Output: -
        Pre conditii: obiectul carte exista
        Post conditii: stocul este actualizat
        */
        void setStoc(int stocNou);
};
